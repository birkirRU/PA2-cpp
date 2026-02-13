#include <cassert>
#include <iostream>
#include "hash_table.h"

using std::cout;
using std::cin;
using std::ws;

HashTable table[1000];

int main() {
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int instance;
        cin >> instance;
        instance--;

        cin >> ws;
        char op;
        cin >> op;

        if (op == 'a') {
            int other;
            cin >> other;
            other--;
            table[instance] = table[other];
        }
        else if (op == 'i') {
            int key, value;
            cin >> key >> value;
            table[instance].insert(key,value);
        }
        else if (op == 'e') {
            int key;
            cin >> key;
            table[instance].remove(key);
        }
        else if (op == 'g') {
            int key;
            cin >> key;
            int value;
            if (table[instance].access(key, value)) {
                cout << value << '\n';
            }
            else {
                cout << "-\n";
            }
        }

        else if (op == 's') {
            int key, value;
            cin >> key >> value;
            table[instance].remove(key);
            table[instance].insert(key, value);
        }

        else if (op == 'z') {
            int size = table[instance].size;
            cout << size << '\n';
        }

        else {
            assert(false);
        }
    }
}