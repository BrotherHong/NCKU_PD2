#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include "database.h"
using namespace std;

const double ERROR = 0.000001;

ifstream openFileStream(const char *fileName);

void toLowerCase(string &str);
void removePunctuation(string &str);
void splitStringBySpace(const string &str, vector<string> &arr);
vector<int> getIntersection(vector<int> &origin, vector<int> &s);
vector<int> getUnion(vector<int> &s1, vector<int> &s2);

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    
    char *corpusFileName = argv[1];
    char *queryFileName = argv[2];
    int k = atoi(argv[3]);

    vector<pair<int, string>> corpus;
    vector<string> query;

    ifstream stream;
    string line;

    // read corpus
    stream = openFileStream(corpusFileName);
    while (getline(stream, line)) {
        int cutIdx = 0;
        while (line[cutIdx] != ',') cutIdx++;

        int id = stoi(line.substr(0, cutIdx));
        string content = line.substr(cutIdx+2);

        corpus.push_back(make_pair(id, content));
    }
    sort(corpus.begin(), corpus.end());

    // read query
    stream = openFileStream(queryFileName);
    while (getline(stream, line)) {
        query.push_back(line);
    }

    Database db;
    vector<string> words;

    // insert corpus
    for (auto &p : corpus) {
        words.clear();
        
        int id = p.first;
        string content = p.second;

        removePunctuation(content);
        toLowerCase(content);
        splitStringBySpace(content, words);

        db.insertSentence(words, id);
    }

    // run query
    vector<pair<int, double>> answer; // [id, rank]
    vector<int> targetCorpus;
    for (string &q : query) {
        words.clear();
        answer.clear();
        targetCorpus.clear();

        toLowerCase(q);
        splitStringBySpace(q, words);

        // get target corpus id
        for (const string &word : words) {
            vector<int> idSet = db.searchTotalMatchIds(word);
            targetCorpus = getUnion(targetCorpus, idSet);
        }

        // calculate rank for each corpus id
        for (int id : targetCorpus) {

            // find top-3-idf keywords for this sentence
            // and calculate tf-value of each keywords
            vector<pair<double, double>> v; // [idf, tf]
            for (const string &qword : words) {
                if (!db.hasWord(id, qword)) {
                    continue;
                }
                double idf = db.getIDF(qword);
                double tf = db.getTermFrequency(qword, id);
                v.push_back(make_pair(idf, tf));
            }

            sort(v.begin(), v.end(), 
            [] (pair<double, double> &p1, pair<double, double> &p2) {
                double &idf1 = p1.first, &tf1 = p1.second;
                double &idf2 = p2.first, &tf2 = p2.second;
                if (abs(idf1-idf2) < ERROR) {
                    return idf1*tf1 > idf2*tf2;
                }
                return idf1 > idf2;
            });

            if (v.size() > 3) {
                v = vector<pair<double, double>>(v.begin(), v.begin()+3);
            }

            // calculate the rank of the sentence
            // rank = sum(tf*idf)
            double rank = 0;
            for (auto &[idf, tf] : v) {
                rank += idf * tf;
            }
            if (rank > 0) {
                answer.push_back(make_pair(id, rank));
            }
        }

        // sort answer
        sort(answer.begin(), answer.end(), 
        [] (const pair<int, double> &p1, const pair<int, double> &p2) {
            if (abs(p1.second-p2.second) < ERROR) {
                return p1.first < p2.first;
            }
            return p1.second > p2.second;
        });

        // output top k answer
        while (answer.size() < k) answer.push_back(make_pair(-1, 0));
        for (int i = 0;i < k;i++) {
            if (i > 0) cout << ' ';
            cout << answer[i].first;
        }
        cout << '\n';
        
    }

    return 0;
}

ifstream openFileStream(const char *fileName) {
    ifstream stream(fileName);

    if (!stream.is_open()) {
        cerr << "Fail to load file " << fileName << endl;
        exit(1); 
    }

    return stream;
}

void toLowerCase(string &str) {
    for (char &c : str) {
        c = tolower(c);
    }
}

void removePunctuation(string &str) {
    string tmp = str;
    str = "";
    for (char &c : tmp) {
        if (isalpha(c) || isspace(c)) {
            str += c;
        }
    }
}

void splitStringBySpace(const string &str, vector<string> &arr) {
    const char *delim = " ";
    char *token = strtok(const_cast<char*>(str.c_str()), delim);

    while (token != nullptr) {
        arr.push_back(string(token));
        token = strtok(nullptr, delim);
    }
}

vector<int> getIntersection(vector<int> &origin, vector<int> &s) {
    vector<int> result;
    set_intersection(origin.begin(), origin.end(), s.begin(), s.end(), back_inserter(result));
    return result;
}

vector<int> getUnion(vector<int> &s1, vector<int> &s2) {
    vector<int> result(s1.size()+s2.size());
    auto it = set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), result.begin());
    result.resize(it-result.begin());
    return result;
}
