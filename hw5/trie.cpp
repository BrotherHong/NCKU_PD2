#include "trie.h"

// TrieNode
TrieNode::TrieNode() {
    for (int i = 0;i < ALPHABET_SIZE;i++) {
        children[i] = nullptr;
    }
    isEndOfWord = false;
}

// Trie
Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const string &word) {
    TrieNode *node = root;

    for (const char &c : word) {
        int idx = c-'a';
        if (node->children[idx] == nullptr) {
            node->children[idx] = new TrieNode();
        }
        node = node->children[idx];
    }

    node->isEndOfWord = true;
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
