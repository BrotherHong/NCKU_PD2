#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
using namespace std;

#define ALPHABET_SIZE (26)

class TrieNode {
public:
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
    vector<int> ids;

    TrieNode();
};

class Trie {
public:
    void insert(const string &word, int id);
    bool totalMatch(const string &word);
    vector<int> getTotalMatchIds(const string &word);

    Trie();

private:
    TrieNode *root;
};

#endif