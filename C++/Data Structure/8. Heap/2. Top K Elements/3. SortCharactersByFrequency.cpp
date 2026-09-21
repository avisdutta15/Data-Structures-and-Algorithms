#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <climits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 451 - Sort Characters By Frequency

    Given a string `s`, sort it in decreasing order based on the
    frequency of the characters. If multiple characters have the
    same frequency, their order doesn't matter.

    Return the sorted string.

    Examples:
    ---------

    Example 1:
        Input:  s = "tree"
        Output: "eert" (or "eetr")
        Explanation:
            Frequencies: e→2, t→1, r→1
            'e' appears most → comes first. 't' and 'r' can be in any order.

    Example 2:
        Input:  s = "cccaaa"
        Output: "aaaccc" (or "cccaaa")
        Explanation:
            Frequencies: c→3, a→3. Same frequency → either order is valid.

    Example 3:
        Input:  s = "Aabb"
        Output: "bbAa" (or "bbaA")
        Explanation:
            Frequencies: b→2, A→1, a→1. Case-sensitive: 'A' and 'a' are different.

    Constraints:
    ------------
    - 1 <= s.length <= 5 * 10^5
    - s consists of uppercase/lowercase English letters and digits.

    Approaches:
    ----------
    1. Max Heap with custom comparator — O(n + m log m)
    2. Bucket Sort                     — O(n)

    Approach 1 — Max Heap:
    -----------------------
    Build a frequency map. Push all (char, freq) pairs into a max-heap
    sorted by frequency. Pop them out and build the result string.

    Time:  O(n + m log m)
        - O(n) to build frequency map
        - O(m log m) to push m unique chars into heap and pop them
          (m = number of unique characters, at most 62: a-z + A-Z + 0-9)
        - O(n) to build the result string (total characters = n)
        - Since m ≤ 62 (constant), this is effectively O(n).
          But in general terms, it's O(n + m log m).
    Space: O(n) for the result string + O(m) for map and heap.

    Approach 2 — Bucket Sort:
    --------------------------
    Frequencies range from 1 to n. Create n+1 buckets, where bucket[f]
    holds all characters with frequency f. Walk from highest bucket
    downward and build the result.

    Time:  O(n)
        - O(n) to build frequency map
        - O(m) to fill buckets
        - O(n) to walk buckets and build result
          (the nested loop visits m characters total across all buckets,
           and appends n characters total to the result)
        - Total: O(n)
    Space: O(n) for buckets + result string.

    Both are effectively O(n) for this problem since m ≤ 62, but
    bucket sort is O(n) even without the constant-alphabet assumption.

    Note:
    -----
    result = result + "abc"    ❌  creates new string, copies everything → O(n²) total
    result += "abc"            ✓   appends in place → O(n) amortized total
    result.append(3, 'a')      ✓   appends in place, no temporary → O(n) total
*/

// Using custom heap
class Solution1 {
public:
    string frequencySort(string s) {

        // 1. Build the frequency map of each character.
        unordered_map<char, int> charFreq;
        for(auto &c : s){
            charFreq[c]++;
        }

        // 2. Sort them using custom max heap.
        auto cmp = [](pair<char, int> &a, pair<char, int> &b){
            return a.second < b.second;
        };
        priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(cmp)> pq;
        
        for(auto &item: charFreq){
            pq.push(item);
        }

        // 3. pop and build the string.
        string result = "";
        while(!pq.empty()){
            auto[character, frequency] = pq.top(); pq.pop();
            result.append(frequency, character);
        }
        return result;
    }
};

class Solution2 {
public:
    string frequencySort(string s) {
        int N = s.length();

        // 1. Build the frequency map of each character.
        unordered_map<char, int> charFreq;
        for (auto& c : s) {
            charFreq[c]++;
        }

        // 2. Create a bucket, where index represents the frequency.
        //    And store all characters with that frequency in the vector at that index.
        vector<vector<char>> bucket(N+1);

        for (auto& item : charFreq) {
            int frequency = item.second;
            int character = item.first;
            bucket[frequency].push_back(character);
        }

        string result = "";
        for(int frequency = N; frequency >= 1; frequency--){
            if(!bucket[frequency].empty()){
                // for each character in the bucket[frequency]
                for(auto &character : bucket[frequency]){
                    // append c, frequency number of times.
                    result.append(frequency, character);
                }
            }
        }

        return result;
    }
};


int main() {
    Solution1 obj;
    cout<<obj.frequencySort("tree")<<endl;
    return 0;
}
