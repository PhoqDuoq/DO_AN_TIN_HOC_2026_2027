#include "BookTrie.h"

#include <cstring>
using namespace std;

BookTrie::BookTrie() {
    root = new Node();
    memset(root->children, 0, sizeof(root->children));
    root->isEnd = false;
}

BookTrie::~BookTrie() {
    clear();
}

void BookTrie::clear() {
    destroy(root);
    root = new Node();
    memset(root->children, 0, sizeof(root->children));
    root->isEnd = false;
}

void BookTrie::destroy(Node* node) {
    if (!node) return;
    for (int i = 0; i < 26; ++i) {
        destroy(node->children[i]);
    }
    delete node;
}

void BookTrie::insert(const string& word) {
    if (word.empty()) return;
    Node* current = root;
    for (char ch : word) {
        int index = ch - 'a';
        if (index < 0 || index >= 26) {
            continue;
        }
        if (!current->children[index]) {
            current->children[index] = new Node();
            memset(current->children[index]->children, 0, sizeof(current->children[index]->children));
            current->children[index]->isEnd = false;
        }
        current = current->children[index];
    }
    current->isEnd = true;
}

bool BookTrie::contains(const string& word) const {
    if (word.empty()) return false;
    Node* current = root;
    for (char ch : word) {
        int index = ch - 'a';
        if (index < 0 || index >= 26 || !current->children[index]) {
            return false;
        }
        current = current->children[index];
    }
    return current->isEnd;
}
