#include "BorrowLinkedList.h"

#include "BorrowRecord.h"

BorrowLinkedList::BorrowLinkedList() : head(nullptr), tail(nullptr) {}

BorrowLinkedList::~BorrowLinkedList() {
    clear();
}

void BorrowLinkedList::pushBack(BorrowRecord* record) {
    if (!record) return;

    Node* newNode = new Node{record, nullptr};
    if (!head) {
        head = tail = newNode;
        return;
    }

    tail->next = newNode;
    tail = newNode;
}

bool BorrowLinkedList::isEmpty() const {
    return head == nullptr;
}

BorrowRecord* BorrowLinkedList::find(int borrowId) const {
    Node* current = head;
    while (current) {
        if (current->data && current->data->getBorrowId() == borrowId) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

void BorrowLinkedList::remove(int borrowId) {
    Node* current = head;
    Node* previous = nullptr;

    while (current) {
        if (current->data && current->data->getBorrowId() == borrowId) {
            if (previous) {
                previous->next = current->next;
            } else {
                head = current->next;
            }

            if (current == tail) {
                tail = previous;
            }

            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
}

void BorrowLinkedList::clear() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}
