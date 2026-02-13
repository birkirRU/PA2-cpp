#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int value = 0) : data(value), prev(NULL), next(NULL) {}
};

class DLL {
private:
    Node* sentinel;
    std::size_t nodeCount;

    void clear();
    void copyFrom(const DLL& other);

public:
    DLL();
    DLL(const DLL& other);
    DLL& operator=(const DLL& other);
    ~DLL();

    Node* sentinel_end_node() const;
    Node* begin_node() const;

    Node* insert(Node* cursor, int value);
    Node* erase(Node* cursor);

    Node* successor(Node* cursor) const;
    Node* predecessor(Node* cursor) const;

    std::size_t size() const;
};

#endif