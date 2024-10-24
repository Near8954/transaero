//
// Created by near on 10/24/24.
//

#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <string>

class Trie {
public:
    Trie() : root(new TrieNode) {
    }

    ~Trie() {
        delete root;
    }

    void insert(const std::string &word);

    [[nodiscard]] bool search(const std::string &word) const;

private:
    struct TrieNode {
        std::vector<TrieNode *> children;
        bool terminal;

        TrieNode() {
            children.assign(26, nullptr);
            terminal = false;
        }

        ~TrieNode() {
            for (TrieNode *child: children) {
                delete child;
            }
        }
    };

    TrieNode *root;
};


#endif //TRIE_H
