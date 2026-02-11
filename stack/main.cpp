#include <iostream>
#include "stack.h"

#include <cassert>
#include <iostream>

using std::cout;
using std::cin;
using std::ws;

Stack<int> vecs[1000];

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
        
        Stack<int>& stack = vecs[instance];

        if (op == 'a') {
            int other;
            cin >> other;
            other--; // change to 0-based index
            Stack<int>& stackOther = vecs[other];
            stack = stackOther;
            // assignment
        }
        else if (op == '+') {
            int value;
            cin >> value;
            stack.push(value);
            // push back
        }
        else if (op == '-') {
            stack.pop();
            // pop back
        }
        else if (op == 't') {
            int top = stack.top();
            std::cout << top << '\n';
        }
        else if (op == 's') {
            int size = stack.get_size(); 
            std::cout << size << '\n';
        }
        else {
            assert(false);
        }
    }
}