#include "database.h"
#include <cmath>

Database::Database() {
    sentenceCount = 0;
}

void Database::insertSentence(const vector<string> &words, int id) {
    for (const string &word : words) {
        trie.insert(word, id);
    }
    sentenceCount++;
}

vector<int> Database::searchTotalMatchIds(const string &word) {
    return trie.getTotalMatchIds(word);
}

double Database::getIDF(const string &word) {
    int existCount = trie.getTotalMatchIds(word).size();
    if (existCount == 0) {
        return 0;
    }
    return log10((double)sentenceCount/existCount);
}