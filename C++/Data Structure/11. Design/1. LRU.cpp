#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

/*
    https://www.youtube.com/shorts/Eb9IUMuiwYc
    
    Problem Statement:
    ------------------
    LeetCode 146 - LRU Cache

    Design a data structure that follows the Least Recently Used (LRU)
    cache eviction policy.

    Implement the LRUCache class:
        - LRUCache(int capacity): initializes with positive capacity.
        - int get(int key): return the value if key exists, else -1.
          Mark the key as recently used.
        - void put(int key, int value): update the value if key exists.
          Otherwise add the key-value pair. If adding exceeds capacity,
          evict the LEAST recently used key before inserting.

    Both get and put must run in O(1) average time.

    Examples:
    ---------

    Example 1:
        LRUCache cache(2);          // capacity = 2
        cache.put(1, 1);            // cache: {1=1}
        cache.put(2, 2);            // cache: {1=1, 2=2}
        cache.get(1);               // returns 1. cache: {2=2, 1=1}
                                    //   (1 is now most recent)
        cache.put(3, 3);            // evicts key 2. cache: {1=1, 3=3}
        cache.get(2);               // returns -1 (evicted)
        cache.put(4, 4);            // evicts key 1. cache: {3=3, 4=4}
        cache.get(1);               // returns -1 (evicted)
        cache.get(3);               // returns 3
        cache.get(4);               // returns 4

    Constraints:
    ------------
    - 1 <= capacity <= 3000
    - 0 <= key <= 10^4
    - 0 <= value <= 10^5
    - At most 2 * 10^5 calls to get and put.

    Approach: HashMap + Doubly Linked List
    ----------------------------------------
    We need two things in O(1):
        1. Lookup by key          → HashMap
        2. Track usage order      → Doubly Linked List

    The linked list maintains order: 
    [front.............................................................back]
    [MRU                                                               LRU]

    front = most recently used,
    back = least recently used (LRU).

    The hashmap maps key → {value, pointer/iterator to list node}
    so we can jump to any node in O(1) and move it to the front.

    Operations:
        get(key):
            - Lookup in map. If not found → -1.
            - Move the node to the front (most recent).
            - Return the value.

        put(key, value):
            - If key exists: update value, move to front.
            - If key doesn't exist:
                - If at capacity: evict from back (LRU), remove from map.
                - Insert new node at front, add to map.

    Why doubly linked list?
    -----------------------
    We need to remove a node from the middle (when moving to front
    or evicting). Singly linked lists need O(n) to find the previous
    node. Doubly linked lists do it in O(1) with prev/next pointers.

    Two implementations below:
    ---------------------------
    LRUCache1: uses std::list (built-in doubly linked list).
    LRUCache2: uses a custom LinkedList with sentinel head/tail nodes.

    Both are O(1) for get and put.

    Dry Run (capacity = 2):
    ------------------------
    put(1,1):  list: [1:1]                map: {1}
    put(2,2):  list: [2:2, 1:1]           map: {1, 2}
    get(1):    move 1 to front.
               list: [1:1, 2:2]           returns 1
    put(3,3):  at capacity. Evict back (2).
               list: [3:3, 1:1]           map: {1, 3}
    get(2):    not in map → returns -1
    put(4,4):  at capacity. Evict back (1).
               list: [4:4, 3:3]           map: {3, 4}
    get(1):    not in map → -1
    get(3):    move 3 to front.
               list: [3:3, 4:4]           returns 3
    get(4):    move 4 to front.
               list: [4:4, 3:3]           returns 4

    Complexity Analysis:
    --------------------
    get:   O(1) — hashmap lookup + list move (O(1) with iterators/pointers).
    put:   O(1) — hashmap insert/update + list insert/erase.
    Space: O(capacity) — list + hashmap store at most capacity entries.

*/

class LRUCache1 {
private:
    int capacity;
    list<pair<int, int>> linkedList;
    unordered_map<int, pair<int, list<pair<int, int>>::iterator>> lookup;   //[key, {value, listIterator}]
public:
    LRUCache1(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        if(lookup.count(key) == 0) 
            return -1;

        // Move to front (most recently used)
        auto &[value, listIterator] =  lookup[key];
        linkedList.erase(listIterator);
        linkedList.push_front({ key, value });
        lookup[key] = { value, linkedList.begin() };

        return value;
    }

    void put(int key, int value) {
        // key present in the cache
        if (lookup.count(key) > 0) {

            // Update value and move to front
            auto &[oldValue, listIterator] = lookup[key];
            linkedList.erase(listIterator);
            linkedList.push_front({key, value});            // use the NEW value
            lookup[key] = { value, linkedList.begin() };    // store the NEW value
        }
        // key not present in the cache
        else {
            if (linkedList.size() == capacity) {
                // Evict LRU if at capacity
                auto &[lastKey, lastValue] = linkedList.back();
                lookup.erase(lastKey);
                linkedList.pop_back();
            }
            // Insert new at front
            linkedList.push_front({ key, value });
            lookup[key] = { value, linkedList.begin() };
        }
    }
};

class ListNode {
public:
    int key, value;
    ListNode* prev;
    ListNode* next;
    ListNode(int key, int value)
        : key(key), value(value), prev(nullptr), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;
    ListNode* tail;
    int size;

public:
    LinkedList() {
        this->size = 0;
        head = new ListNode(-1, -1);
        tail = new ListNode(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    void push_front(ListNode* node) {
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
        size++;
    }

    void erase(ListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        node = nullptr;
        size--;
    }

    void pop_back() {
        ListNode* node = tail->prev;
        tail->prev = tail->prev->prev;
        tail->prev->next = tail;
        delete node;
        node = nullptr;
        size--;
    }

    ListNode* begin() { 
        return head->next; 
    }

    pair<int, int> back() { 
        return { tail->prev->key, tail->prev->value }; 
    }

    int getSize() { 
        return size; 
    }
};

class LRUCache2 {
private:
    int capacity;
    LinkedList linkedList;
    unordered_map<int, pair<int, ListNode*>> lookup; //[key, {value, ListNode}]
public:
    LRUCache2(int capacity) { this->capacity = capacity; }

    int get(int key) {
        if (lookup.count(key) == 0)
            return -1;

        // Move to front (most recently used)
        auto& [value, node] = lookup[key];
        linkedList.erase(node);
        linkedList.push_front(new ListNode(key, value));
        lookup[key] = { value, linkedList.begin() };

        return value;
    }

    void put(int key, int value) {
        // key present in the cache
        if (lookup.count(key) > 0) {

            // Update value and move to front
            auto& [oldValue, listIterator] = lookup[key];
            linkedList.erase(listIterator);
            linkedList.push_front(
                new ListNode(key, value));             // use the NEW value
            lookup[key] = { value, linkedList.begin() }; // store the NEW value
        }
        // key not present in the cache
        else {
            if (linkedList.getSize() == capacity) {
                // Evict LRU if at capacity
                auto [lastKey, lastValue] = linkedList.back();
                lookup.erase(lastKey);
                linkedList.pop_back();
            }
            // Insert new at front
            linkedList.push_front(new ListNode(key, value));
            lookup[key] = { value, linkedList.begin() };
        }
    }
};

int main() {
    // Test LRUCache1 (using std::list)
    cout << "=== LRUCache1 (std::list) ===" << endl;
    LRUCache1 cache1(2);
    cache1.put(1, 1);
    cache1.put(2, 2);
    cout << cache1.get(1) << endl;    // 1
    cache1.put(3, 3);                 // evicts key 2
    cout << cache1.get(2) << endl;    // -1
    cache1.put(4, 4);                 // evicts key 1
    cout << cache1.get(1) << endl;    // -1
    cout << cache1.get(3) << endl;    // 3
    cout << cache1.get(4) << endl;    // 4

    // Test LRUCache (custom LinkedList)
    cout << "=== LRUCache (custom list) ===" << endl;
    LRUCache2 cache2(2);
    cache2.put(1, 1);
    cache2.put(2, 2);
    cout << cache2.get(1) << endl;    // 1
    cache2.put(3, 3);                 // evicts key 2
    cout << cache2.get(2) << endl;    // -1
    cache2.put(4, 4);                 // evicts key 1
    cout << cache2.get(1) << endl;    // -1
    cout << cache2.get(3) << endl;    // 3
    cout << cache2.get(4) << endl;    // 4

    // Test value update
    cout << "=== Value update test ===" << endl;
    LRUCache2 cache3(2);
    cache3.put(1, 10);
    cache3.put(1, 20);               // update value of key 1
    cout << cache3.get(1) << endl;    // 20 (not 10)

    return 0;
}