#ifndef BORROWLINKEDLIST_H
#define BORROWLINKEDLIST_H

#include <string>

class BorrowRecord;

class BorrowLinkedList {
public:
    BorrowLinkedList();
    ~BorrowLinkedList();

    void pushBack(BorrowRecord* record);
    void remove(int borrowId);
    BorrowRecord* find(int borrowId) const;
    bool isEmpty() const;
    void clear();

private:
    struct Node {
        BorrowRecord* data;
        Node* next;
    };

    Node* head;
    Node* tail;
};

#endif
