#include <cassert>
#include <iostream>
#include "dynamic_array.h"

using std::cout;
using std::cin;
using std::ws;

DArr<int> vecs[1000];

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

        if (op == 'a') {
            int other;
            cin >> other;
            other--; // change to 0-based index
            DArr<int>& arr = vecs[instance];
            DArr<int>& arrOther = vecs[other];
            arr = arrOther;
            // assignment
        }
        else if (op == '+') {
            int value;
            cin >> value;
            DArr<int>& arr = vecs[instance];
            arr.push_back(value);
            // push back
        }
        else if (op == '-') {
            
            DArr<int>& arr = vecs[instance];
            arr.pop_back();
            // pop back
        }
        else if (op == 'i') {
            int index, value;
            cin >> index >> value;
            DArr<int>& arr = vecs[instance];
            arr.insert(value, index);
            // insert
        }
        else if (op == 'e') {
            int index;
            cin >> index;
            DArr<int>& arr = vecs[instance];
            arr.erase(index);
            // erase
        }
        else if (op == 'g') {
            int index;
            cin >> index;
            DArr<int>& arr = vecs[instance];
            int element = arr[index];
            std::cout << element << '\n';
            // get
        }
        else if (op == 's') {
            int index, value;
            cin >> index >> value;
            DArr<int>& arr = vecs[instance];
            arr[index] = value;
            // set
        }
        else if (op == 'r') {
            int sz;
            cin >> sz;
            DArr<int>& arr = vecs[instance];
            arr.resize(sz);

        }
        else if (op == 'p') {
            DArr<int> arr = vecs[instance];
            arr.print();
        }
        else {
            assert(false);
        }
    }
}