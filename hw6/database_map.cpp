#include "database.h"
#include <cmath>

Database::Database() {
    mp.clear();
    sentenceCount = 0;
}

void Database::insertSentence(const vector<string> &words, int id) {
    for (const string &word : words) {
        vector<int> &ids = mp[word];
        if (ids.empty() || ids.back() != id) {
            ids.push_back(id);
        }
    }
    sentenceCount++;
}

vector<int> Database::searchTotalMatchIds(const string &word) {
    auto it = mp.find(word);
    if (it == mp.end()) {
        return {};
    }
    return it->second;
}

double Database::getIDF(const string &word) {
    auto it = mp.find(word);
    int count = (it == mp.end() ? 0 : it->second.size());
    if (count == 0) {
        return 0;
    }
    return log10((double)sentenceCount/count);
}
