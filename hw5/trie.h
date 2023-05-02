#ifndef TRIE_H
#define TRIE_H

#include <string>
using namespace std;

#define ALPHABET_SIZE (26)

class TrieNode {
public:
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode();
};

class Trie {
public:
    void insert(const string &word);
    bool totalMatch(const string &word);

    Trie();

private:
    TrieNode *root;
};

#endif