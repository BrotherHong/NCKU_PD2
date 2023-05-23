#include "trie.h"

// TrieNode
TrieNode::TrieNode() {
    for (int i = 0;i < ALPHABET_SIZE;i++) {
        children[i] = nullptr;
    }
    isEndOfWord = false;
    ids.clear();
}

// Trie
Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const string &word, int id) {
    TrieNode *node = root;

    for (const char &c : word) {
        int idx = c-'a';
        if (node->children[idx] == nullptr) {
            node->children[idx] = new TrieNode();
        }
        node = node->children[idx];
    }

    node->isEndOfWord = true;
    if (node->ids.empty() || node->ids.back() != id) {
        node->ids.push_back(id);
    }
}

bool Trie::totalMatch(const string &word) {
    TrieNode *node = root;

    for (const char &c : word) {
        int idx = c-'a';

        if (node->children[idx] == nullptr) {
            return false;
        }

        node = node->children[idx];
    }

    return (node != nullptr && node->isEndOfWord);
}

vector<int> Trie::getTotalMatchIds(const string &word) {
    TrieNode *node = root;

    for (const char &c : word) {
        int idx = c-'a';

        if (node->children[idx] == nullptr) {
            return {};
        }

        node = node->children[idx];
    }

    return node->ids;
}
