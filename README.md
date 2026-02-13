# PA2-cpp - Data Structure Implementations

## Overview
Template-based collection of fundamental data structures in C++98 with automatic memory management and comprehensive testing.

**Common Features:**
- **Template-based**: Works with any data type
- **C++98 compliant**: Uses `assert()` for precondition checking
- **Memory safe**: Automatic management with deep copy semantics
- **Tested**: Each structure has 10+ test cases with expected outputs
- **Explicit instantiation**: Pre-compiled for `int`, `float`, and `double`

---

## Building and Testing

### Quick Start (All Structures)
Navigate to any data structure folder and run:

```bash
cd <data_structure_folder>    # e.g., cd dynamic_array
make                          # Build main program
make test                     # Build and run all tests automatically
```

**Expected Test Output:**
```
Running tests...
test0 PASS
test1 PASS
test2 PASS
...
...
test9 PASS
```

### Running Individual Tests
```bash
make                          # Build main program first
./main < tests/test1.<txt or in>      # Run specific test (replace 1 with test number)
cat tests/eout1.txt           # View expected output for comparison
or 
cat tests/test1.out           # only applicable to some structures
```

### Interactive Mode
```bash
make run                      # Run interactive main program
```

### Memory Leak Detection
```bash
make valgrind-main            # Check main program for leaks
```

### Cleanup
```bash
make clean                    # Remove all build artifacts
```

---

## Test Input Format (Universal)

All test files follow the same format:
```
<number_of_operations>
<instance_id> <operation> [arguments...]
```

**Common Operations Across Structures:**
- `+` value / `i` key value: Insert/push element
- `-` / `e` key: Remove/pop/erase element
- `p` / `t` / `g`: Peek/top/get element
- `s`: Get size OR set value (context-dependent)
- `a` other_id: Assignment from another instance

*Specific operations vary by structure - see individual sections below*

---

## Data Structures

### 1. Dynamic Array (DArr)

**Overview:**
A template-based dynamically resizable array with automatic growth and shrinkage.

**Key Properties:**
- **Growth factor**: Doubles capacity (2x) when full
- **Shrink factor**: Reduces to cap/4 when size ≤ cap/4 (minimum capacity: 8)
- **Default capacity**: 8 elements
- **Underlying structure**: Raw pointer to dynamically allocated array
- **Index 0-based**: Direct access via `operator[]`
- **Templated**

**Time Complexities & Edge Cases**

| Operation | Time Complexity | Exceptional Cases / Behavior |
|-----------|----------------|------------------------------|
| **Constructor** | O(n) where n is initial capacity | Allocates array of size init_cap (default 8) |
| **Destructor** | O(1) | Frees allocated memory, sets pointer to NULL |
| **Copy Constructor** | O(n) where n is size | Deep copy of all elements |
| **Assignment Operator** | O(n) where n is size | Self-assignment protected, deep copy |
| **push_back** | O(1) amortized, O(n) worst | Doubles capacity when full (requires copying all elements) |
| **pop_back** | O(1) amortized | Asserts size != 0; Shrinks to cap/4 when size ≤ cap/4 and cap > 8 |
| **operator[]** (get) | O(1) | Asserts 0 ≤ index < size; Returns reference to element |
| **operator[]** (set) | O(1) | Asserts 0 ≤ index < size; Modifies element in place |
| **insert** | O(n) where n is size | Asserts valid index; Shifts elements right; May trigger resize |
| **erase** | O(n) where n is size | Asserts 0 ≤ index < size; Shifts elements left |
| **resize** | O(n) where n is new size | May call reserve if n ≥ cap; Initializes new elements to T() |
| **reserve** | O(n) where n is new capacity | Allocates new array, copies elements, updates capacity |


**Test Operations:**
- `+` value: push_back(value)
- `-`: pop_back()
- `i` idx value: insert(value, idx)
- `e` idx: erase(idx)
- `g` idx: get element at index
- `s` idx value: set element at index
- `r` size: resize(size)
- `p`: print array (size + all elements)

**Memory Management:**
- Amortized O(1) insertions via doubling strategy
- Each element copied at most log₂(n) times
- Automatic shrinking prevents memory waste
- Deep copy semantics for copy constructor and assignment

---

### 2. Min Heap

**Overview:**
A binary min-heap using function pointer-based comparator, built on our Dynamic Array implementation.

**Key Properties:**
- **Underlying structure**: Dynamic Array (index 0 is dummy)
- **Parent/child formula**: parent = i/2, left = 2i, right = 2i+1
- **Heap property**: parent ≤ children (for min-heap)
- **Comparator**: Function pointer allows custom comparison
- **Default**: `min` function for min-heap behavior
- **Templated**

**Time Complexities & Edge Cases**

| Operation | Time Complexity | Exceptional Cases / Behavior |
|-----------|----------------|------------------------------|
| **Constructor** | O(1) | Initializes with dummy element at index 0 |
| **Destructor** | O(1) | DArr handles memory cleanup automatically |
| **Copy Constructor** | O(n) | Deep copy via DArr copy constructor |
| **Assignment Operator** | O(n) | Deep copy via DArr assignment |
| **push** | O(log n) amortized | Adds element and swims up to maintain heap property |
| **pop** | O(log n) | Asserts heap not empty; Returns and removes min element; Sinks replacement down |
| **peek** | O(1) | Asserts heap not empty; Returns reference to minimum element (index 1) |
| **get_size** | O(1) | Returns `arr.size - 1` (excluding dummy element) |
| **swim** | O(log n) | Moves element up tree until heap property restored |
| **sink** | O(log n) | Moves element down tree, choosing smaller child |


**Test Operations:**
- `+` value: push(value)
- `-`: pop()
- `p`: peek()
- `s`: get_size()

**Heap Operations:**
- **Swim**: Moves element up tree until heap property restored
- **Sink**: Moves element down tree, choosing smaller child
- **Index 0 dummy**: Simplifies parent/child calculations

**Memory Management:**
- Relies on Dynamic Array for allocation
- No NULL checks needed (dummy at index 0)
- O(log n) height guarantees performance

---

### 3. Stack (LIFO)

**Overview:**
Last-In-First-Out stack built as a wrapper around our implementation of Dynamic Array.

**Key Properties:**
- **LIFO principle**: Last pushed is first popped
- **Underlying structure**: Dynamic Array
- **Top element**: Always at arr[size-1]
- **No random access**: Only top element accessible
- **Templated**

**Time Complexities & Edge Cases**

| Operation | Time Complexity | Exceptional Cases / Behavior |
|-----------|----------------|------------------------------|
| **Constructor** | O(1) | Initializes empty stack with underlying DArr |
| **Destructor** | O(1) | DArr handles cleanup automatically |
| **Copy Constructor** | O(n) | Deep copy via DArr copy constructor |
| **Assignment Operator** | O(n) | Deep copy via DArr assignment |
| **push** | O(1) amortized | Adds element to top; May trigger DArr resize |
| **pop** | O(1) amortized | Asserts stack not empty; Removes top element; May trigger DArr shrink |
| **top** | O(1) | Asserts stack not empty; Returns reference to top element |
| **get_size** | O(1) | Returns number of elements in stack |

**Test Operations:**
- `+` value: push(value)
- `-`: pop()
- `t`: top()
- `s`: get_size()

**Memory Management:**
- Automatic via Dynamic Array
- No additional memory overhead
- Top returns reference (allows modification)

---

### 4. AVL Tree (Self-Balancing BST)

**Overview:**
A self-balancing binary search tree maintaining height balance via rotations.

**Key Properties:**
- **Balance factor**: height(left) - height(right) ∈ [-1, 1] for all nodes
- **Rotations**: Single (left, right) and double (left-right, right-left)
- **Augmented nodes**: Store height and subtree size
- **Parent pointers**: Enable efficient traversal
- **Guaranteed height**: ≤ 1.44 * log₂(n + 2)



**Time Complexities & Edge Cases**

| Operation | Time Complexity | Exceptional Cases / Behavior |
|-----------|----------------|------------------------------|
| **Constructor** | O(1) | Initializes empty tree with NULL root |
| **Constructor(key, value)** | O(1) | Creates tree with single root node |
| **Destructor** | O(n) | Recursively deletes all nodes via delete_tree |
| **Assignment Operator** | O(n) | Deep copy via copy_of_tree; Handles self-assignment |
| **insert(key, value)** | O(log n) | Returns pointer to inserted/existing node; Duplicate keys update existing node; Triggers rebalancing |
| **erase(node)** | O(log n) | Asserts node not NULL; Removes node and rebalances tree; Returns NULL |
| **find(key)** | O(log n) | Returns pointer to node with key, or NULL if not found |
| **lower_bound(key)** | O(log n) | Returns node with smallest key ≥ given key, or NULL if none exists |
| **upper_bound(key)** | O(log n) | Returns node with smallest key > given key, or NULL if none exists |
| **front()** | O(log n) | Returns leftmost (minimum) node, or NULL if tree empty |
| **back()** | O(log n) | Returns rightmost (maximum) node, or NULL if tree empty |
| **successor(node)** | O(log n) | Returns next node in sorted order, or NULL if node is maximum |
| **predecessor(node)** | O(log n) | Returns previous node in sorted order, or NULL if node is minimum |
| **rank(node)** | O(log n) | Returns 0-based index of node in sorted order; Returns 0 if node is NULL |
| **kth(k)** | O(log n) | Returns node at 0-based index k in sorted order, or NULL if k out of bounds |
| **size()** | O(1) | Returns total number of nodes in tree; Returns 0 if tree empty |

**Test Operations:**
- `i` key value: insert(key, value) - sets cursor
- `?` key: find(key) - sets cursor
- `l` key: lower_bound(key) - sets cursor
- `u` key: upper_bound(key) - sets cursor
- `e`: erase(cursor) - removes node at cursor
- `f`: front() - sets cursor to min
- `b`: back() - sets cursor to max
- `>`: successor(cursor) - updates cursor
- `<`: predecessor(cursor) - updates cursor
- `r`: rank(cursor) - prints rank
- `k` k: kth(k) - sets cursor to kth element
- `g`: get value at cursor
- `s` value: set value at cursor
- `z`: size()

**Rotation Types:**
```
Left-Left (LL):     Right-Right (RR):
    y                    x
   / \                  / \
  x   C    →  right    A   y
 / \                      / \
A   B                    B   C

Left-Right (LR):    Right-Left (RL):
  y                    x
 / \                  / \
x   D    →  LR       A   y
 \                      /
  z                    z
```

**Order Statistics:**
- **rank(node)**: Find position of node (0-based)
- **kth(k)**: Find kth smallest element
- Enabled by storing subtree size in each node

**Memory Management:**
- Each node: key, value, height, size, left, right, parent (7 integers + pointers)
- Deep copy via copy_of_tree
- Automatic rebalancing maintains O(log n) height

---

### 5. Hash Table (Separate Chaining)

**Overview:**
Hash table using separate chaining for collision resolution with automatic resizing.

**Key Properties:**
- **Hash function**: `hash(key) = abs(key * 539) % capacity`
- **Collision resolution**: Separate chaining with linked lists
- **Initial capacity**: 16 buckets
- **Load factor threshold**: 0.7 (70%)
- **Resize factor**: 2x capacity when threshold exceeded
- **Duplicate handling**: Insert ignores duplicates (use erase + insert to update)

**Time Complexities & Edge Cases**

| Operation | Average Case | Worst Case | Exceptional Cases / Behavior |
|-----------|-------------|------------|------------------------------|
| **Constructor** | O(c) | O(c) | Initializes hash table with capacity c (default 16); Allocates bucket array |
| **Destructor** | O(n) | O(n) | Traverses all chains to delete nodes; Deallocates bucket array |
| **Copy Constructor** | O(n) | O(n) | Deep copy via insert; Creates independent copy with same capacity |
| **Assignment Operator** | O(n + m) | O(n + m) | Destroys current table (m elements), deep copies rhs (n elements); Handles self-assignment |
| **insert(key, value)** | O(1) amortized | O(n) | Ignores duplicate keys (no update); May trigger resize; Worst case when all keys hash to same bucket |
| **erase(key)** | O(1) amortized | O(n) | Removes key-value pair; Does nothing if key not found; Decrements size |
| **access(key, ret_val)** | O(1) amortized | O(n) | Returns true and sets ret_val if key found; Returns false and sets ret_val to 0 if not found |
| **get_size()** | O(1) | O(1) | Returns number of key-value pairs in table |
| **resize()** | O(n) | O(n) | Doubles capacity; Rehashes all n elements; Called automatically when load factor > 0.7 |


**Test Operations:**
- `i` key value: insert(key, value) - ignores if exists
- `e` key: erase(key)
- `g` key: access(key, value) - prints value or "-"
- `s` key value: set (erase + insert) - updates value
- `z`: get_size()

**Hash Function:**
```
hash(key) = ( key * 2654435769L >> 32 ) % capacity
```
- Well known knuths multiplicitive hashing function.
- Modulo ensures index in [0, capacity-1]

**Collision Handling:**
```
Bucket 5: key=10 -> key=49 -> key=88 -> NULL
```
- Separate chaining with singly-linked lists
- Insert at end of chain (checks for duplicates)
- Linear search within chain for lookup/delete

**Resizing:**
```
Load Factor = (size + 1) / capacity

If Load Factor > 0.7:
    new_capacity = 2 × old_capacity
    Rehash all elements (hash values change)
```

**Memory Management:**
- Array of capacity pointers (bucket heads)
- Nodes allocated dynamically per element
- Average chain length ≈ 0.7 at threshold
- Worst case: all keys in one chain (O(n) operations)

**Note on Updates:**
- `insert()` with existing key is ignored (no update)
- Use set operation (erase then insert) to update values
- Example: `s 20 999` = erase(20), then insert(20, 999)

---

### 6. Doubly Linked List (Circular with Sentinel)

**Overview:**
Doubly linked list using circular structure with sentinel node for simplified operations.

**Key Properties:**
- **Sentinel node**: Dummy node marking both begin and end
- **Circular structure**: Last->next = sentinel, sentinel->prev = last
- **Bidirectional links**: Each node has prev and next pointers
- **No NULL pointers**: All pointers always valid
- **Cursor-based**: Operations use node pointers as positions

**Time Complexities:**

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Constructor | O(1) | Creates sentinel pointing to itself |
| insert(cursor, value) | O(1) | Inserts before cursor, returns new node |
| erase(cursor) | O(1) | Removes node, returns successor |
| successor(cursor) | O(1) | Returns next node |
| predecessor(cursor) | O(1) | Returns previous node |
| begin_node() | O(1) | Returns first element (sentinel->next) |
| sentinel_end_node() | O(1) | Returns sentinel (end position) |
| size() | O(1) | Number of elements (excludes sentinel) |

**Test Operations:**
- `i` value: insert(cursor, value) - sets cursor to new node
- `e`: erase(cursor) - sets cursor to successor
- `f`: begin_node() - move cursor to first
- `b`: sentinel_end_node() - move cursor to sentinel
- `>`: successor(cursor) - move cursor forward
- `<`: predecessor(cursor) - move cursor backward
- `g`: get data at cursor
- `s` value: set data at cursor
- `z`: size()

**Structure:**
```
Empty list:
    sentinel <-> sentinel (points to itself)

List [10, 20, 30]:
    sentinel <-> [10] <-> [20] <-> [30] <-> sentinel
    ^_______________________________________________|
```

**Sentinel Benefits:**
- No NULL checks needed
- Unified insert/erase logic at all positions
- Simple empty list representation
- Acts as past-the-end iterator marker

**Insert Operation:**
```
List: [10, 20, 30], cursor at [20]
insert(cursor, 15):
    Creates new [15]
    [10]->next = [15], [15]->prev = [10]
    [15]->next = [20], [20]->prev = [15]
Result: [10, 15, 20, 30]
```

**Erase Operation:**
```
List: [10, 20, 30], cursor at [20]
erase(cursor):
    [10]->next = [30]
    [30]->prev = [10]
    delete [20]
    return [30]
Result: [10, 30], cursor now at [30]
```

**Traversal Examples:**

Forward:
```cpp
    Node* current = sentinel->next;
    while (current != sentinel) {
        Node* nextNode = current->next;
        current = nextNode;
    }
```

**Memory Management:**
- Each node: 1 integer (data) + 2 pointers (prev, next)
- Sentinel always present (even in empty list)
- Circular structure: no NULL pointers
- Deep copy creates independent list

---
## Implementation Files Structure

Each data structure folder contains:

```
structure_name/
├── structure_name.h          # Class declaration
├── structure_name.cpp        # Implementation
├── main.cpp                  # Interactive testing
├── Makefile                  # Build automation
└── tests/
    ├── test1.txt ... test10.txt    # Input files
    └── eout1.txt ... eout10.txt    # Expected outputs
```

---

## Design Decisions Summary

**Dynamic Array:**
- Doubling growth ensures O(1) amortized push_back
- Shrinking at cap/4 prevents thrashing
- Minimum capacity 8 avoids excessive reallocations

**Min Heap:**
- Dummy at index 0 simplifies parent/child math: parent=i/2, left=2i, right=2i+1
- Function pointer comparator allows custom heap types without inheritance

**Stack:**
- Thin LIFO wrapper over Dynamic Array
- Top returns reference for in-place modification
- Zero additional memory overhead

**AVL Tree:**
- Parent pointers enable O(log n) successor/predecessor without stack
- Size augmentation enables O(log n) order statistics (rank, kth)
- Balance factor ∈ [-1, 1] guarantees height ≤ 1.44 log₂(n)

**Hash Table:**
- Load factor 0.7 balances memory and performance
- Separate chaining handles collisions gracefully
- Insert ignores duplicates (intentional design choice)

**Doubly Linked List:**
- Circular sentinel eliminates NULL checks and special cases
- Insert before cursor enables consistent interface
- Erase returns successor for easy iteration