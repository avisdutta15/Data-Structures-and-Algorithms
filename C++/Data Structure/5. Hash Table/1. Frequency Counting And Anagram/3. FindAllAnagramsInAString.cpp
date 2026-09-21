#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/*
    Problem Statement:
    -----------------
    Find All Anagrams in a String

    Given two strings s and p, return an array of all the start indices of p's anagrams in s.
    You may return the answer in any order.

    An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
    typically using all the original letters exactly once.

    Examples:
    --------
    Example 1:
        Input: s = "abab", p = "ab"
        Output: [0,2]
        Explanation:
        The substring with start index = 0 is "ab", which is an anagram of "ab".
        The substring with start index = 2 is "ab", which is an anagram of "ab".

    Example 2:
        Input: s = "abacabad", p = "aaab"
        Output: [0,1]
        Explanation:
        The substring with start index = 0 is "abac", which is an anagram of "aaab".
        The substring with start index = 1 is "baca", which is an anagram of "aaab".

    Constraints:
    1 <= s.length, p.length <= 3 * 10^4
    s and p consist of lowercase English letters only.

    Approach: SLIDING WINDOW WITH FREQUENCY MATCHING
    -----------------------------------------------

    TIME COMPLEXITY: O(|s|) - Single pass through string s
    SPACE COMPLEXITY: O(1) - Fixed size frequency arrays (26 characters)

    ALGORITHM:
    1. Create frequency map for pattern p
    2. Use sliding window of size |p| over string s
    3. Maintain frequency of current window
    4. Compare frequencies to detect anagrams
    5. Slide window: remove left char, add right char

    OPTIMIZATIONS: [Need to Dry run and understand more TODO]
    - Use arrays instead of hash maps (faster for fixed alphabet)
    - Track number of matching characters to avoid full array comparison
    - Early termination when impossible to find more matches
*/

class Solution {
private:
    /**
     * Helper function to check if two frequency arrays represent anagrams
     * TIME: O(26) = O(1) for lowercase English letters
     */
    bool isAnagram(const vector<int>& freq1, const vector<int>& freq2) {
        //We can also do return freq1 == freq2
        for (int i = 0; i < 26; i++) {
            if (freq1[i] != freq2[i]) {
                return false;
            }
        }
        return true;
    }
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;

        // Base Case: if p is longer than s, no anagrams possible
        if (p.length() > s.length()) {
            return result;
        }

        int sLen = s.length();
        int pLen = p.length();

        // Frequency arrays for pattern and current window (faster than hash maps)
        vector<int> pFreq(26, 0);
        vector<int> windowFreq(26, 0);

        // Build frequency array for pattern p
        for (char c : p) {
            pFreq[c - 'a']++;
        }

        // Process first window
        for (int i = 0; i < pLen; i++) {
            windowFreq[s[i] - 'a']++;
        }

        // Check if first window is an anagram
        if (isAnagram(pFreq, windowFreq)) {
            result.push_back(0);
        }

        // Slide the window through rest of string s
        for (int i = pLen; i < sLen; i++) {
            // Add new character (right side of window)
            windowFreq[s[i] - 'a']++;

            // Remove old character (left side of window)
            windowFreq[s[i - pLen] - 'a']--;

            // Check if current window is an anagram
            if (isAnagram(pFreq, windowFreq)) {
                result.push_back(i - pLen + 1);
            }
        }

        return result;
    }

    /**
     * OPTIMIZED VERSION: Using match counter to avoid full array comparison
     * This version is even more efficient for larger alphabets
     */
    vector<int> findAnagramsOptimized(string s, string p) {
        vector<int> result;

        if (p.length() > s.length()) {
            return result;
        }

        int sLen = s.length();
        int pLen = p.length();

        vector<int> pFreq(26, 0);
        vector<int> windowFreq(26, 0);

        // Build pattern frequency
        for (char c : p) {
            pFreq[c - 'a']++;
        }

        int matches = 0; // Count of characters with matching frequencies

        // Process first window
        for (int i = 0; i < pLen; i++) {
            int idx = s[i] - 'a';
            windowFreq[idx]++;

            // Update match counter
            if (windowFreq[idx] == pFreq[idx]) {
                matches++;
            }
            else if (windowFreq[idx] == pFreq[idx] + 1) {
                matches--;
            }
        }

        // Check first window
        if (matches == 26) {
            result.push_back(0);
        }

        // Slide window
        for (int i = pLen; i < sLen; i++) {
            // Add right character
            int rightIdx = s[i] - 'a';
            windowFreq[rightIdx]++;
            if (windowFreq[rightIdx] == pFreq[rightIdx]) {
                matches++;
            }
            else if (windowFreq[rightIdx] == pFreq[rightIdx] + 1) {
                matches--;
            }

            // Remove left character
            int leftIdx = s[i - pLen] - 'a';
            windowFreq[leftIdx]--;
            if (windowFreq[leftIdx] == pFreq[leftIdx]) {
                matches++;
            }
            else if (windowFreq[leftIdx] == pFreq[leftIdx] - 1) {
                matches--;
            }

            // Check if current window is anagram
            if (matches == 26) {
                result.push_back(i - pLen + 1);
            }
        }

        return result;
    }
};

int main() {
    Solution obj;

    // Test Case 1
    cout << "Test Case 1:" << endl;
    string s1 = "abab", p1 = "ab";
    vector<int> result1 = obj.findAnagrams(s1, p1);
    cout << "Input: s = \"" << s1 << "\", p = \"" << p1 << "\"" << endl;
    cout << "Output: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << result1[i];
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]" << endl << endl;

    // Test Case 2
    cout << "Test Case 2:" << endl;
    string s2 = "abacabad", p2 = "aaab";
    vector<int> result2 = obj.findAnagrams(s2, p2);
    cout << "Input: s = \"" << s2 << "\", p = \"" << p2 << "\"" << endl;
    cout << "Output: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << result2[i];
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "]" << endl << endl;

    // Test Case 3 - Optimized version
    cout << "Test Case 3 (Optimized):" << endl;
    string s3 = "cbaebabacd", p3 = "abc";
    vector<int> result3 = obj.findAnagramsOptimized(s3, p3);
    cout << "Input: s = \"" << s3 << "\", p = \"" << p3 << "\"" << endl;
    cout << "Output: [";
    for (int i = 0; i < result3.size(); i++) {
        cout << result3[i];
        if (i < result3.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    return 0;
}