#ifndef BOOKTRIE_H
#define BOOKTRIE_H

#include <string>
using namespace std;

class BookTrie {
public:
    BookTrie();
    ~BookTrie();

    void insert(const string& word);
    bool contains(const string& word) const;
    void clear();

private:
    struct Node {
        bool isEnd;
        Node* children[26];
    };

    Node* root;

    void destroy(Node* node);
};

#endif
