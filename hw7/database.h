#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <unordered_map>
#include "trie.h"
using namespace std;

class Database {
public:
    Database();
    void insertSentence(const vector<string> &words, int id);
    vector<int> searchTotalMatchIds(const string &word);
    bool hasWord(int id, const string &word);
    double getIDF(const string &word);
    double getTermFrequency(const string &word, int id);
private:
    Trie trie;
    unordered_map<int, unordered_map<string, int>> wordCount; // wordCount[id][str]
    unordered_map<int, int> totalWordCount; // the number of words in id's sentence
    unordered_map<string, vector<int>> mp;
    int sentenceCount;
};

#endif
