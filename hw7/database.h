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
    double getIDF(const string &word);
private:
    Trie trie;
    unordered_map<string, vector<int>> mp;
    int sentenceCount;
};

#endif
