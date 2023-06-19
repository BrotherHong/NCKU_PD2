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
    vector<pair<int, double>> answer;
    unordered_map<int, double> mp; // {id, idf_sum}
    for (string &q : query) {
        words.clear();
        answer.clear();
        mp.clear();

        toLowerCase(q);
        splitStringBySpace(q, words);

        // calculate idf_sum of each sentence
        for (const string &word : words) {
            double idf = db.getIDF(word);
            if (idf == 0) continue;
            
            for (int id : db.searchTotalMatchIds(word)) {
                mp[id] += idf;
            }
        }

        // move map element to vector
        auto it = mp.begin();
        for (;it != mp.end();++it) {
            answer.push_back(make_pair(it->first, it->second));
        }

        // sort the answer
        sort(answer.begin(), answer.end(), [] 
        (const pair<int, double> &p1, const pair<int, double> &p2) {
            if (abs(p1.second-p2.second) < ERROR) {
                return p1.first < p2.first;
            }
            return p1.second > p2.second;
        });

        // output top k
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
