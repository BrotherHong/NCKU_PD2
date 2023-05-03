#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <set>
using namespace std;

#define ALPHABET_SIZE (26)

class TrieNode {
public:
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
    set<int> ids;

    TrieNode();
};

class Trie {
public:
    void insert(const string &word, int id);
    bool totalMatch(const string &word);
    set<int> getTotalMatchIds(const string &word);

    Trie();

private:
    TrieNode *root;
};

#endif