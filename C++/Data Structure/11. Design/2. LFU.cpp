#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

/*
    https://www.youtube.com/watch?v=0PSB9y8ehbk
    
    Problem Statement:
    ------------------
    LeetCode 460 - LFU Cache

    Design a data structure for a Least Frequently Used (LFU) cache.

    Implement the LFUCache class:
        - LFUCache(int capacity): initializes with positive capacity.
        - int get(int key): return the value if key exists, else -1.
          Increases the use count of the key.
        - void put(int key, int value): update the value if key exists,
          or insert a new key-value pair. When capacity is exceeded,
          evict the LEAST FREQUENTLY used key. If there's a tie
          (multiple keys with the same lowest frequency), evict the
          LEAST RECENTLY used among them.

    Both get and put must run in O(1) average time.

    How is this different from LRU?
    --------------------------------
    LRU: evict the least RECENTLY used     (based on time of last access)
    LFU: evict the least FREQUENTLY used   (based on total access count)
         tie-break: least recently used among those with the same count

    Examples:
    ---------

    Example 1:
        LFUCache cache(2);
        cache.put(1, 10);           // key 1 freq=1
        cache.put(2, 20);           // key 2 freq=1
        cache.get(1);               // returns 10. key 1 freq=2
        cache.put(3, 30);           // evicts key 2 (freq=1, LRU among freq=1)
        cache.get(2);               // returns -1 (evicted)
        cache.get(3);               // returns 30. key 3 freq=2
        cache.get(1);               // returns 10. key 1 freq=3

    Constraints:
    ------------
    - 1 <= capacity <= 10^4
    - 0 <= key <= 10^5
    - 0 <= value <= 10^9
    - At most 2 * 10^5 calls to get and put.

    Data Structures:
    -----------------
    Three hashmaps:

    1. key_map:  key → {value, frequency}
       Purpose: O(1) lookup of value and current frequency by key.

    2. freq_map: frequency → list<int> of keys
       Purpose: groups all keys by their frequency. Each list is
       ordered: front = most recently used, back = LRU.
       When evicting, we go to freq_map[min_freq] and pop the back.

    3. iter_map: key → iterator into freq_map[freq] list
       Purpose: O(1) removal of a key from its frequency list
       (without scanning). Erase by iterator is O(1).

    4. min_freq: int
       Purpose: tracks the current minimum frequency across all keys.
       When we need to evict, we instantly know which frequency list
       to look at: freq_map[min_freq].

    Significance of min_freq:
    --------------------------
    Without min_freq, finding the least frequent key would require
    scanning all frequency lists — O(n). min_freq gives us O(1)
    direct access to the eviction target.

    How is min_freq maintained?
        - When a NEW key is inserted: min_freq = 1
          (new keys always start with frequency 1, which is the lowest)
        - When a key is touched (get/put existing):
          Its frequency goes from f to f+1.
          If freq_map[f] becomes empty AND f == min_freq:
              min_freq++ (the old minimum no longer has any keys)
        - After eviction: min_freq is set to 1 (new key is inserted
          right after eviction, and it has frequency 1).

    Pseudocode:
    -----------

    touch(key):
        1. Look up key's current frequency f from key_map.
        2. Remove key from freq_map[f] using iter_map[key].
        3. If freq_map[f] is now empty:
            - Delete freq_map[f].
            - If f == min_freq: min_freq++.
        4. f = f + 1.
        5. Push key to front of freq_map[f] (most recent position).
        6. Update key_map[key] with new frequency.
        7. Update iter_map[key] with new iterator.

    get(key):
        1. If key not in key_map → return -1.
        2. Call touch(key).
        3. Return the value.

    put(key, value):
        1. If key exists in key_map:
            - Update value.
            - Call touch(key).
            - Return.
        2. If at capacity:
            - Evict: pop back of freq_map[min_freq] (LRU among LFU).
            - Remove evicted key from key_map and iter_map.
        3. Insert new key:
            - key_map[key] = {value, 1}.
            - Push key to front of freq_map[1].
            - iter_map[key] = iterator to front of freq_map[1].
            - min_freq = 1.

    Dry Run (capacity = 2):
    ------------------------

    put(1, 10):
        key_map: {1:(10, freq=1)}
        freq_map: {1: [1]}
        min_freq = 1

    put(2, 20):
        key_map: {1:(10,1), 2:(20,1)}
        freq_map: {1: [2, 1]}     ← 2 is more recent (front)
        min_freq = 1

    get(1):  touch(1): freq 1→2
        Remove 1 from freq_map[1]. freq_map[1] = [2]. Not empty → min_freq stays 1.
        Push 1 to freq_map[2].
        key_map: {1:(10,2), 2:(20,1)}
        freq_map: {1: [2], 2: [1]}
        min_freq = 1.  Returns 10.

    put(3, 30):  key 3 is new. At capacity (2).
        Evict from freq_map[min_freq=1]. Back of [2] = key 2. Evict key 2.
        freq_map: {2: [1]}
        Insert key 3 with freq=1.
        key_map: {1:(10,2), 3:(30,1)}
        freq_map: {1: [3], 2: [1]}
        min_freq = 1

    get(2):  not in key_map → returns -1

    get(3):  touch(3): freq 1→2
        freq_map[1] = []. Empty and 1==min_freq → min_freq = 2.
        key_map: {1:(10,2), 3:(30,2)}
        freq_map: {2: [3, 1]}     ← 3 more recent
        min_freq = 2.  Returns 30.

    get(1):  touch(1): freq 2→3
        Remove 1 from freq_map[2]. freq_map[2] = [3]. Not empty → min_freq stays 2.
        key_map: {1:(10,3), 3:(30,2)}
        freq_map: {2: [3], 3: [1]}
        min_freq = 2.  Returns 10.

    Complexity Analysis:
    --------------------
    get:   O(1) — hashmap lookups + list erase/insert by iterator.
    put:   O(1) — hashmap operations + list operations.
    Space: O(capacity) — three hashmaps store at most capacity entries.

*/

class LFUCache {
private:
    unordered_map<int, pair<int, int>> key_map;
    unordered_map<int, list<int>> freq_map;
    unordered_map<int, list<int>::iterator> iter_map;

    int capacity;
    int min_freq;

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        min_freq = 0;
    }

    int get(int key) {
        if(key_map.count(key) == 0)
            return -1;

        auto &[value, frequency] = key_map[key];
        auto iter = iter_map[key];
        freq_map[frequency].erase(iter);

        if(freq_map[frequency].empty()){
            freq_map.erase(frequency);
            if(frequency == min_freq)
                min_freq++;
        }
            
        frequency++;
        freq_map[frequency].push_front(key);
        key_map[key] = {value, frequency};
        iter_map[key] = freq_map[frequency].begin();

        return value;
    }

    void put(int key, int value){
        
        if(key_map.count(key) > 0){
            auto &[oldValue, frequency] = key_map[key];

            auto iter = iter_map[key];
            freq_map[frequency].erase(iter);

            if(freq_map[frequency].empty()){
                freq_map.erase(frequency);
                if(frequency == min_freq)
                    min_freq++;
            }
            
            frequency++;
            freq_map[frequency].push_front(key);
            key_map[key] = {value, frequency};
            iter_map[key] = freq_map[frequency].begin();

            return;
        }else{
            // Eviction : LRU
            if(key_map.size() == capacity){
                int evict_key = freq_map[min_freq].back();
                freq_map[min_freq].pop_back();
                if(freq_map[min_freq].empty())
                    freq_map.erase(min_freq);
                key_map.erase(evict_key);
                iter_map.erase(evict_key);
            }

            // Do this first in interview. Normal flow.
            // Insert new key with frequency 1
            key_map[key] = {value, 1};
            freq_map[1].push_front(key);
            iter_map[key] = freq_map[1].begin();
            min_freq = 1;    // new key always has freq 1, which is the new minimum
        }
    }
};


int main() {
    LFUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    cout << cache.get(1) << endl;    // 10 (key 1 freq: 1→2)

    cache.put(3, 30);               // evicts key 2 (freq=1, LRU among freq=1)
    cout << cache.get(2) << endl;    // -1 (evicted)
    cout << cache.get(3) << endl;    // 30 (key 3 freq: 1→2)
    cout << cache.get(1) << endl;    // 10 (key 1 freq: 2→3)

    cache.put(4, 40);               // evicts key 3 (freq=2, lowest freq now)
    cout << cache.get(3) << endl;    // -1 (evicted)
    cout << cache.get(4) << endl;    // 40

    // Test value update
    cache.put(1, 100);              // update key 1's value
    cout << cache.get(1) << endl;    // 100 (updated value, freq: 3→4→5)

    return 0;
}