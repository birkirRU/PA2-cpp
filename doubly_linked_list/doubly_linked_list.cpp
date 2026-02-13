#include "doubly_linked_list.h"

DLL::DLL() {
    sentinel = new Node();
    nodeCount = 0;

    sentinel->next = sentinel;
    sentinel->prev = sentinel;
}

DLL::DLL(const DLL& other) {
    sentinel = new Node();
    nodeCount = 0;

    sentinel->next = sentinel;
    sentinel->prev = sentinel;

    copyFrom(other);
}

DLL& DLL::operator=(const DLL& other) {
    if (this == &other) {
        return *this;
    }

    clear();
    copyFrom(other);
    return *this;
}

DLL::~DLL() {
    clear();

    delete sentinel;
    sentinel = NULL;
}

void DLL::clear() {
    Node* current = sentinel->next;

    while (current != sentinel) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    nodeCount = 0;
}

void DLL::copyFrom(const DLL& other) {
    Node* current = other.sentinel->next;

    while (current != other.sentinel) {
        insert(sentinel, current->data);
        current = current->next;
    }
}

Node* DLL::sentinel_end_node() const {
    return sentinel;
}

Node* DLL::begin_node() const {
    return sentinel->next;
}

Node* DLL::insert(Node* cursor, int value) {
    Node* leftNode = cursor->prev;

    Node* newNode = new Node(value);
    newNode->prev = leftNode;
    newNode->next = cursor;

    leftNode->next = newNode;
    cursor->prev = newNode;

    nodeCount += 1;
    return newNode;
}

Node* DLL::erase(Node* cursor) {
    Node* leftNode = cursor->prev;
    Node* rightNode = cursor->next;

    leftNode->next = rightNode;
    rightNode->prev = leftNode;

    delete cursor;

    nodeCount -= 1;
    return rightNode;
}

Node* DLL::successor(Node* cursor) const {
    return cursor->next;
}

Node* DLL::predecessor(Node* cursor) const {
    return cursor->prev;
}

std::size_t DLL::size() const {
    return nodeCount;
}