#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
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
    int sentenceCount;
};

#endif
