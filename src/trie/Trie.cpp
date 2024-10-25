//
// Created by near on 10/24/24.
//

#include "Trie.h"


void Trie::insert(const std::string &word) {
    TrieNode *node = root;
    for (auto &c: word) {
        if (node->children[c - 'a'] == nullptr) {
            node->children[c - 'a'] = new TrieNode();
        }
        node = node->children[c - 'a'];
    }
    node->terminal = true;
}

bool Trie::search(const std::string &word) const {
    TrieNode *node = root;
    for (auto &c: word) {
        if (node->children[c - 'a'] == nullptr) {
            return false;
        }
        node = node->children[c - 'a'];
    }
    return node->terminal;
}
