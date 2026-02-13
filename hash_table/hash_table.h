#include <cmath>

struct Node {
    int key;
    int value;
    Node *next;

    Node(int key, int value) : key(key), value(value), next(NULL) {}
};

struct HashTable {

    Node** table;
    int size;
    int capacity;

    HashTable(int given_capacity = 16) {
        table = new Node*[given_capacity];
        size = 0;
        capacity = given_capacity;
        for (int i = 0; i < capacity; i++) {
            table[i] = NULL;
        }
    }

    HashTable(const HashTable& other) {
        table = new Node*[other.capacity];
        size = 0;
        capacity = other.capacity;
        for (int i = 0; i < capacity; i++) {
            table[i] = NULL;
        }

        for (int i = 0; i<other.capacity; i++) {
            Node* node = other.table[i];

            while (node != NULL) {
                insert(node->key,node->value);
                node = node->next;
            }

        }

    }

    int get_size () {
        return size;
    }

    void desctructor() {

        for (int i = 0; i < capacity; i++) {
            Node* first = table[i];

            while (first != NULL) {
                Node* current = first;
                first = first->next;
                delete current;
            }
        }

        delete[] table;
    }

    ~HashTable() {
        desctructor();
    }


    int hash(int key) {
       return std::abs(key) % capacity;
    }

    bool do_i_resize() {

        int new_size = size + 1;
        float temp = (float) new_size / capacity;

        if (temp > 0.7) {
            return true;
        }
        else {
            return false;
        }
    }

    void insert(int key,int value) {

        if (do_i_resize()) {  
        resize();
        }

        int index = hash(key);

        if (table[index] == NULL) {
            table[index] = new Node(key,value);
            size++;
            return;
        }
        Node* node = table[index];

        while(node->next != NULL) {
            if (node->key == key) {
            return;}
            node = node->next;
        }

        if (node->key == key) {
            return;
        }

        node->next = new Node(key,value);
        size++;
        return;

    }

    void resize() {

        Node** old = table;
        table = new Node*[capacity *2];

        for (int i = 0; i < capacity*2; i++) {
            table[i] = NULL;
        };

        int old_size = size;
        size = 0;
        int old_capacity = capacity;
        capacity = capacity * 2;

        for (int i = 0; i < old_capacity; i++) {

            Node* node = old[i];

            while (node != NULL) {
                insert(node->key,node->value);
                Node* temp = node;
                node = node->next;
                delete temp;
            }
        }

        delete[] old;

    }

    HashTable& operator=(const HashTable& rhs) {

        if (this == &rhs) return *this;

        desctructor();
        capacity = rhs.capacity;

        table = new Node*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = NULL;
        }       
        size = 0;

        for (int i = 0; i < capacity; i++) {
            Node* first = rhs.table[i];
            while (first != NULL) {
                insert(first->key, first->value);
                first = first->next;
            }
            }
        
        return *this;

     }

    void remove(int key) {
        int index = hash(key);
        Node* node = table[index];
        Node* before = NULL;

        while(node != NULL) {
            if (node->key == key) {
                if (before != NULL) {
                    before->next = node->next;
                }
                else {
                    table[index] = node->next;
                }
                delete node;
                size--;
                return;
            }
            before = node;
            node = node->next;
            }
        }

        bool access(int key, int& ret_val) {
            int index = hash(key);
            Node* node = table[index];
            while(node != NULL) {
                if (node->key == key) {
                    ret_val = node->value;
                    return true;
                }
                else {
                    node = node->next;
                }
            }
            ret_val = 0;
            return false;
        }
        };