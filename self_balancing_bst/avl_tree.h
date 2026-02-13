#ifndef SBBST
#define SBBST

#include <cmath>

struct Node {
    int key;
    int value;
    int height;
    int size;
    Node *left;
    Node *right;
    Node *parent;

    Node(int key, int value) : key(key), value(value), height(1), size(1), left(NULL), right(NULL), parent(NULL) {}
};

struct AVLTree {

    Node* root;
    AVLTree() : root(NULL) {}
    
    AVLTree(int key, int value) {
        root = new Node(key, value);
    }

    Node* insert(int key, int value) {
        Node* new_node = NULL;
        root = Insert(root, key, value, new_node);

            if (root) {
                root->parent = NULL;
            }
        
        return new_node;
}

    Node* Insert(Node* node, int key, int value, Node*& new_node) {
        if (node == NULL) {
            new_node = new Node(key, value);
            return new_node;
        }

        if (key > node->key) {
            node->right = Insert(node->right, key, value, new_node);
            if (node->right) {
                node->right->parent = node;
            }
        }
        else if (key < node->key) {
            node->left = Insert(node->left, key, value, new_node);
            if (node->left) {
                node->left->parent = node;
            }
        }
        else {
            new_node = node;
            return node;
        }

        update_height(node);
        update_size(node); 
        node = balance(node);
       
        return node;
    }

    int size() { 
        if (root == NULL) {
            return 0;
        }
    return root->size;
    }

    Node* balance(Node* node) {
        int balance_factor = getbalance(node);  
        if (balance_factor > 1) {
            if (getbalance(node->left) < 0) { 
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);  
        }
        
        if (balance_factor < -1) {
            if (getbalance(node->right) > 0) {  
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);  
        }
        
        return node;
    }

    int getbalance(Node* node) {
        if (node == NULL) {
            return 0;
        }

        int left_node = (node->left) ? node->left->height : 0;
        int right_node = (node->right) ? node->right->height : 0;
        return left_node - right_node;
    }

    Node* rotate_right(Node* node) {
        Node* temp = node->left;
        Node* temp2 = temp->right;   
        temp->right = node;
        node->left = temp2;

        temp->parent = node->parent;
        node->parent = temp;

        if (temp2 != NULL) {
            temp2->parent = node;
        }
        
        update_height(node);
        update_height(temp);
        update_size(node); 
        update_size(temp);

        return temp;
    }

    Node* rotate_left(Node* node) {
        Node* temp = node->right;
        Node* temp2 = temp->left;   
        temp->left = node;
        node->right = temp2;

        temp->parent = node->parent;
        node->parent = temp;

        if (temp2 != NULL) {
            temp2->parent = node;
        }
        
        update_height(node);
        update_height(temp);
        update_size(node);
        update_size(temp);

        return temp;
    }

    void update_height(Node* node) {
        int left = 0;
        int right = 0;

        if (node == NULL) {
            return;
        }

        if (node->left) {
            left = node->left->height;
        }

        if (node->right) {
            right = node->right->height;
        }

        if (right > left) {
            node->height = 1 + right;
        }
        else {
            node->height = 1 + left;
        }
    }

     AVLTree& operator=(const AVLTree& rhs) {
        if (this == &rhs) return *this;

        delete_tree(root);
        root = copy_of_tree(rhs.root,NULL);

        return *this;

     }

     Node* copy_of_tree(Node* node, Node* parent) {
        if (node == NULL) {
            return NULL;
        }

        Node* temp = new Node(node->key,node->value);
        temp->height = node->height;
        temp->parent = (parent) ? parent: NULL;
        temp->size = node->size;

        temp->left = copy_of_tree(node->left, temp);
        temp->right = copy_of_tree(node->right,temp);

        return temp;
     }

     void delete_tree(Node* node) {

        if (node == NULL) {
            return; 
        }
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;

     }

    Node* find(int key) {
        return find(root, key);
    }

     Node* find(Node* node, int key) {
        if (node == NULL) {
            return NULL;
        }

        if (key == node->key) {
            return node;
        }

        else if (key > node->key) {
            return find(node->right,key);
        }

        else {
            return find(node->left,key);
        }

     }

     Node* lower_bound(int key) {
        return lower(root, key);
    }

     Node* lower(Node* node, int key) {
        if (node == NULL) {
            return NULL;
        }
        if (key == node->key) {
            return node;
        }
        else if (key > node->key) {
            return lower(node->right,key);
        }

        else {
            Node* left_tree = lower(node->left, key);
        
            if (left_tree != NULL) {
                return left_tree;
            }

            return node;
        }
     }

     Node* upper_bound(int key) {
        return upper(root, key);
    }

     Node* upper(Node* node, int key) {
        if (node == NULL) {
            return NULL;
        }
        if (key == node->key) {
            return upper(node->right,key);
        }
        else if (key > node->key) {
            return upper(node->right,key);
        }

        else {
            Node* left_tree = upper(node->left, key);
        
            if (left_tree != NULL) {
                return left_tree;
            }

            return node;
        }
     }

    Node* erase(Node* node) {

        if (node == NULL) {
            return NULL;
        }

        Node* original_parent = node->parent;
        
        if (node->left == NULL && node->right == NULL) {
            if (node->parent == NULL) {
                root = NULL;
            }
            else {
                if (node->parent->left == node) {
                    node->parent->left = NULL;
                }
                else {
                    node->parent->right = NULL;
                }
            }
            delete node;
        
        }
        
        else if (node->left && node->right == NULL) {
            node->left->parent = node->parent; 
            
            if (node->parent == NULL) {
                root = node->left;
            }
            else {
                if (node->parent->left == node) {
                    node->parent->left = node->left;
                }
                else {
                    node->parent->right = node->left;
                }
            }
            delete node;
    
        }
        
        else if (node->left == NULL && node->right) {
            node->right->parent = node->parent;
            
            if (node->parent == NULL) {
                root = node->right;
            }
            else {
                if (node->parent->left == node) {
                    node->parent->left = node->right;
                }
                else {
                    node->parent->right = node->right;
                }
            }
            delete node;
        
        }
    
        else {
            
            Node *succ = successor(node);
            node->key = succ->key;
            node->value = succ->value;
            erase(succ);
            return NULL;
        };

        Node* current = original_parent;

        while (current != NULL) {
            update_height(current);
            update_size(current);
        Node* parent = current->parent;  
        Node* balanced = balance(current);  
        
        if (parent == NULL) {
            root = balanced;
            balanced->parent = NULL;
        } else if (parent->left == current) {
            parent->left = balanced; 
        }
        
        else {
            parent->right = balanced;
        }

        balanced->parent = parent;
        current = parent; 
        
        }

        return NULL;


    };

    Node* successor(Node* node) {

        if (node == NULL) {
            return NULL;
        };

        if (node->right != NULL) {
            return successor_helper(node->right);
        };

        Node* parent = node->parent;
        Node* current = node;
    
        while (parent != NULL && current == parent->right) {
            current = parent;
            parent = parent->parent;
        }
    
        return parent;

    };

    Node* successor_helper(Node* node) {
        if (node->left == NULL) {
            return node;
        }
        return successor_helper(node->left);

    };

    Node* front() {
        return Front_helper(root);
    };

    Node* Front_helper(Node* node) {
        if (node == NULL) {
            return node;
        }

        if (node->left == NULL) {
            return node; 
        }

        return Front_helper(node->left);
    };

    Node* back() {
        return Back_helper(root);
    };

    Node* Back_helper(Node* node) {
        if (node == NULL) {
            return node;
        }

        if (node->right == NULL) {
            return node; 
        }

        return Back_helper(node->right);
    };

    Node* predecessor(Node* node) {

        if (node == NULL) {
            return NULL;
        };

        if (node->left != NULL) {
            return predecessor_helper(node->left);
        };

        Node* parent = node->parent;
        Node* current = node;
    
        while (parent != NULL && current == parent->left) {
            current = parent;
            parent = parent->parent;
        }
    
        return parent;

    };

    Node* predecessor_helper(Node* node) {
        if (node->right == NULL) {
            return node;
        }
        return predecessor_helper(node->right);

    };

    void update_size(Node* node) {
        if (node == NULL) {
            return;
        }
        
        int left_size = (node->left) ? node->left->size : 0;
        int right_size = (node->right) ? node->right->size : 0;
        
        node->size = 1 + left_size + right_size;
    }

    int rank(Node* node) {

        if (node == NULL) {
            return 0;
        }
        
        int rank;
        if (node->left) {
            rank = node->left->size;
        }
        else {
            rank = 0;
        }
        
        Node* current = node;
        Node* parent = node->parent;
        
        while (parent != NULL) {

            if (parent->right == current) {
                rank += 1;  
                if (parent->left) {
                    rank += parent->left->size;
                }
            }

            current = parent;
            parent = parent->parent;
        }
        
        return rank;
    }

    Node* kth(int k) {
        return kth_helper(root, k);
    }

    Node* kth_helper(Node* node, int element) {
        if (node == NULL) {
            return NULL;
        }

        int left_size;
        
        if (node->left) {
            left_size = node->left->size;
        }
        else {
            left_size = 0;
        }
        
        
        if (element < left_size) {
            return kth_helper(node->left, element);
        }
        else if (element == left_size) {
            return node;
        }


        else {
            return kth_helper(node->right, element - left_size - 1);
        }
    }

};


#endif

