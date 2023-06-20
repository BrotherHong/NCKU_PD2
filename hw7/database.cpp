#include "database.h"
#include <cmath>

Database::Database() {
    sentenceCount = 0;
}

void Database::insertSentence(const vector<string> &words, int id) {
    for (const string &word : words) {
        trie.insert(word, id);
        wordCount[id][word]++;
    }
    totalWordCount[id] = words.size();
    sentenceCount++;
}

vector<int> Database::searchTotalMatchIds(const string &word) {
    return trie.getTotalMatchIds(word);
}

bool Database::hasWord(int id, const string &word) {
    if (wordCount.find(id) == wordCount.end()) {
        return false;
    }
    if (wordCount[id].find(word) == wordCount[id].end()) {
        return false;
    }
    return true;
}

double Database::getIDF(const string &word) {
    int existCount = trie.getTotalMatchIds(word).size();
    if (existCount == 0) {
        return 0;
    }
    return log10((double)sentenceCount/existCount);
}

double Database::getTermFrequency(const string &word, int id) {
    return (double) wordCount[id][word] / totalWordCount[id]; 
}