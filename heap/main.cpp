
#include <cassert>
#include <iostream>
#include "heap.h"

using std::cout;
using std::cin;
using std::ws;

Heap<int, min> vecs[1000];

int main() {
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int instance;
        cin >> instance;
        instance--; // change to 0-based index
        // consume whitespace before reading character, otherwise we get a space
        cin >> ws;
        char op;
        cin >> op; // read operation character
        Heap<int, min>& heap = vecs[instance];

        if (op == 'a') {
            int other;
            cin >> other;
            other--; // change to 0-based index
            Heap<int, min>& heapOther = vecs[other];
            heap = heapOther;
            // assignment
        }
        else if (op == '+') {
            int value;
            cin >> value;
            heap.push(value);
            // push back
        }
        else if (op == '-') {
            heap.pop();
            // pop back
        }
        else if (op == 's') {
            std::cout << heap.get_size() << '\n';
            // size
        }
        else if (op == 'p') {
            std::cout << heap.peek() << '\n';
            // smallest element
        }
        else {
            assert(false);
        }
    }
}