#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include "database.h"
using namespace std;

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
    vector<int> allIds;
    vector<string> words;

    // insert corpus
    for (auto &p : corpus) {
        words.clear();
        
        int id = p.first;
        string content = p.second;

        removePunctuation(content);
        toLowerCase(content);
        splitStringBySpace(content, words);

        db.insertWords(words, id);
        allIds.push_back(id);
    }

    // run query
    vector<int> answer, ids;
    for (string &q : query) {
        words.clear();

        toLowerCase(q);
        splitStringBySpace(q, words);

        answer = allIds;
        
        for (const string &word : words) {
            ids = db.searchTotalMatchIds(word);
            answer = getIntersection(answer, ids);
            if (answer.empty()) break;
        }

        if (answer.empty()) {
            cout << -1 << '\n';
        } else {
            bool first = true;
            for (const int &id : answer) {
                if (first) first = false;
                else cout << ' ';

                cout << id;
            }
            cout << '\n';
        }
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
