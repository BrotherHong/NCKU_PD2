#include "database.h"

void Database::insertWords(const vector<string> &words, int id) {
    for (const string &word : words) {
        trie.insert(word, id);
    }
}

vector<int> Database::searchTotalMatchIds(const string &word) {
    return trie.getTotalMatchIds(word);
}