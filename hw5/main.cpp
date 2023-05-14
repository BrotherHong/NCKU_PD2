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
set<int>& getIntersection(set<int> &origin, set<int> &s);

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    
    char *corpusFileName = argv[1];
    char *queryFileName = argv[2];

    vector<string> corpus;
    vector<string> query;

    ifstream stream;
    string line;

    // read corpus
    stream = openFileStream(corpusFileName);
    while (getline(stream, line)) {
        corpus.push_back(line);
    }

    // read query
    stream = openFileStream(queryFileName);
    while (getline(stream, line)) {
        query.push_back(line);
    }

    Database db;
    set<int> allIds;
    vector<string> words;

    // insert corpus
    for (string &str : corpus) {
        words.clear();
        
        int cutIdx = 0;
        while (str[cutIdx] != ',') cutIdx++;

        int id = stoi(str.substr(0, cutIdx));
        string content = str.substr(cutIdx+2);

        removePunctuation(content);
        toLowerCase(content);
        splitStringBySpace(content, words);

        db.insertWords(words, id);
        allIds.insert(id);
    }

    // run query
    set<int> answer, ids;
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

set<int>& getIntersection(set<int> &origin, set<int> &s) {
    set<int> tmp = origin;
    origin.clear();
    set_intersection(tmp.begin(), tmp.end(), s.begin(), s.end(), inserter(origin, origin.begin()));
    return origin;
}
