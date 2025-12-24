#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    Given an array of strings strs, group the anagrams together. You can return the answer in any order.

    Examples:
    --------
    Example 1:
        Input: strs = ["eat","tea","tan","ate","nat","bat"]
        Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

        Explanation:
        There is no string in strs that can be rearranged to form "bat".
        The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
        The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.

    Example 2:
        Input: strs = [""]
        Output: [[""]]

    Example 3:
        Input: strs = ["a"]
        Output: [["a"]]

    Constraints:
    1 <= strs.length <= 104
    0 <= strs[i].length <= 100
    strs[i] consists of lowercase English letters.

    Approach:
    ---------
    We will store the groups based on some similarity.
    Let us use an unordered_map<similarity , similar_words[]>
    How to get the similarity? -> Key:
        1. Sort the characters and get the key.
                e.g. -> word: bottle,  key: beoltt
        2. Use Frequency sort to get the key.
                e.g. -> word: bottle,  key: b1e1l1o1t2

    TIME COMPLEXITY ANALYSIS:
    ------------------------

    APPROACH 1: SORTING-BASED
    - Per string: O(M * log M) for sorting
    - Total: O(N * M * log M)
    - Where N = number of strings, M = average string length

    APPROACH 2: FREQUENCY-BASED
    - Per string: O(M) for frequency counting
                  where M = string length
                    - Single pass through string: O(M)
                    - Building key string: O(1) amortized (max 26 characters)
                    - MAX KEY SIZE: 104 characters (26 letters + 26*3 digits for counts up to 100)
    - Total: O(N * M)
    - Where N = number of strings, M = average string length

    SPACE COMPLEXITY: O(N * M) for both approaches

    PERFORMANCE COMPARISON:
    - Short strings (M ≤ 10): Both approaches similar
    - Long strings (M > 15): Frequency approach significantly faster
    - Very long strings (M > 50): Frequency approach ~3-5x faster

    WHEN TO USE WHICH:
    - Frequency approach: Better for longer strings, more complex code
    - Sorting approach: Simpler code, good for shorter strings

*/


class Solution {
private:
    string getKeyUsingFrequency(const string& word) {
        vector<int> freq(26, 0);            // Only lowercase letters

        for (char c : word) {
            freq[c - 'a']++;
        }

        //example of key: a1e1t1
        string key;
        key.reserve(104);                   // 26 letters + 78 digits (26 * 3 digits max)

        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                key += char(i + 'a');
                key += to_string(freq[i]);
            }
        }

        return key;
    }

    string getKeyUsingSorting(const string& word) {
        string tempWord = word;
        sort(tempWord.begin(), tempWord.end());
        return tempWord;
    }
public:
    vector<vector<string>> groupAnagrams(vector<string>& words) {
        if (words.empty()) return {};
        if (words.size() == 1) return { words };        // Early termination

        unordered_map<string, vector<string>> hashToWordMap;
        hashToWordMap.reserve(words.size());            // Reserve capacity

        for (string& word : words) {                    // Use reference to avoid copy
            string key = getKeyUsingFrequency(word);
            //string key = getKeyUsingSorting(word);
            hashToWordMap[key].push_back(move(word));   // Move instead of copy
        }

        vector<vector<string>> groupedAnagrams;
        groupedAnagrams.reserve(hashToWordMap.size());  // Reserve capacity

        for (auto& pair : hashToWordMap) {
            groupedAnagrams.push_back(move(pair.second)); // Move instead of copy
        }

        return groupedAnagrams;
    }
};

int main() {
    Solution obj;
    cout << "Test Case: 1" << endl;
    vector<string> words = { "eat","tea","tan","ate","nat","bat", "tee" };

    // Test the optimized frequency-based approach
    auto groupedAnagrams = obj.groupAnagrams(words);
    cout << "Frequency-based approach:" << endl;
    for (const auto& group : groupedAnagrams) {
        for (const auto& anagram : group) {
            cout << anagram << " ";
        }
        cout << endl;
    }

    return 0;
}