#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <set>
#include "trie.h"
using namespace std;

class Database {
public:
    void insertWords(const vector<string> &words, int id);
    set<int> searchTotalMatchIds(const string &word);
private:
    Trie trie;
};

#endif
