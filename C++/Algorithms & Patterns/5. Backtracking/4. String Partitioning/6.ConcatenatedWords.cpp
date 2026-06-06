#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    Given an array of strings words (without duplicates), return all the concatenated words 
    in the given list of words.
    
    A concatenated word is defined as a string that is comprised entirely of at least two 
    shorter words (not necessarily distinct) in the given array.
    

    Examples:
    ---------
    Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
    Output:        ["catsdogcats","dogcatsdog","ratcatdogcat"]
    Explanation:   "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
                   "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
                   "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".

    Input: words = ["cat","dog","catdog"]
    Output: ["catdog"]

    Constraints:
    ------------
        1 <= words.length <= 104
        1 <= words[i].length <= 30
        words[i] consists of only lowercase English letters.
        All the strings of words are unique.
        1 <= sum(words[i].length) <= 10^5

    Approach:
    ---------
    The problem asks us to find all words that are made up of at least two other words in the dictionary. 
    This is a variation of the classic "Word Break" problem.

    Here is a breakdown of how the three solutions progressively optimize the approach.

    Solution 1: Standard Backtracking with a Counter
    -----------
    The Approach: This is the most direct translation of the problem statement. 
                  For every word in the list, it temporarily removes the word from 
                  the dictionary (so a word doesn't just match itself) and runs a 
                  standard Word Break recursive check.

    The Key Feature (numberOfSubWords): Because the problem strictly requires a concatenated word 
                  to be made of at least two shorter words, this solution passes a reference variable 
                  numberOfSubWords. Every time a valid prefix is found and the recursion goes deeper, 
                  the counter increments. If the recursion reaches the end of the string, it returns 
                  true and the main loop checks if (possible && numberOfSubWords >= 2) before adding 
                  it to the answers.

    Pros: Straightforward and easy to reason about.
    Cons: The counter requires explicit backtracking (numberOfSubWords--), 
          and the recursion explores every branch without caching, making it slow.

    Solution 2: The "Minimum Length" Optimization
    -------------
    The Approach: This solution removes the clunky numberOfSubWords counter entirely by 
                  using a clever logical deduction about the dictionary's shortest word.

    The Key Feature (minWordLength): First, it loops through the array to find the length of the 
    shortest word in the entire dictionary (minWordLength).
    When it's time to check if a word is concatenated, it skips any word whose length is equal 
    to (or less than) minWordLength.

    Why does this work? The absolute shortest word in a dictionary cannot possibly be 
    made up of two other words from that same dictionary (because those other words would 
    have to be even shorter, which is impossible by definition). Furthermore, because we 
    temporarily remove the current word from the wordLookUp set before testing it, if 
    our Word Break algorithm successfully finds a match for it, it must have been formed 
    by at least two other distinct words. Thus, the counter is no longer needed!

    Pros: Cleaner code, less backtracking state to manage, and skips unnecessary evaluations for small words.
    Cons: Still recalculates overlapping subproblems for long strings.

    Solution 3: Full Optimization with Memoization
    -----------
    The Approach: This is the optimal top-down solution. It takes the clever minWordLength 
                  logic from Solution 2 and pairs it with Top-Down Dynamic Programming (Memoization) 
                  to solve the overlapping subproblems issue.

    The Key Feature (vector<int>& memo): Inside the main loop, before checking a word, it initializes 
                  a memo array of size 31 initialized to -1. 
                  (The size is 31 because the problem constraints guarantee that words[i].length <= 30).

    Inside the recursive canBeFormed function:
        - It checks the cache: if (memo[start_index] != -1) return memo[start_index];
        - It caches success: return memo[start_index] = true;
        - It caches failure: return memo[start_index] = false;
    
    Pros: Extremely fast. If the algorithm evaluates a substring and finds it cannot 
          be broken down further, it remembers that failure for that specific start_index. 
          If another prefix path lands on that same index, the memoization instantly cuts 
          off the branch, preventing exponential time complexity.
        
*/

// Word Break Problem + Minimum Of 2 Word Breaks (TLE)
class Solution1 {
private:
    bool canBeFormed(string& word, int start_index, unordered_set<string>& wordLookUp, int& numberOfSubWords) {
        if (start_index == word.length()) {
            return true;
        }

        if (wordLookUp.find(word) != wordLookUp.end())
            return true;

        for (int i = start_index; i < word.length(); i++) {
            string prefix = word.substr(start_index, i - start_index + 1);

            if (wordLookUp.find(prefix) != wordLookUp.end()) {
                //found prefix. Check if the rest of the word can be found
                numberOfSubWords++;
                if (canBeFormed(word, i + 1, wordLookUp, numberOfSubWords) == true)
                    return true;

                //else backtrack
                numberOfSubWords--;
            }
        }
        return false;
    }
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        unordered_set<string> wordLookUp(words.begin(), words.end());
        vector<string> allConcatenatedWordsInADict;

        for (string& word : words) {
            int numberOfSubWords = 0;
            wordLookUp.erase(word);

            bool possible = canBeFormed(word, 0, wordLookUp, numberOfSubWords);
            if (possible && numberOfSubWords >= 2)
                allConcatenatedWordsInADict.push_back(word);

            wordLookUp.insert(word);
        }

        return allConcatenatedWordsInADict;
    }
};

// Word Break Problem + Skip Minimum Sized Words as they cannot be splitted - Optimized (TLE)
class Solution2 {
private:
    bool canBeFormed(string& word, int start_index, unordered_set<string>& wordLookUp) {
        if (start_index == word.length()) {
            return true;
        }

        if (wordLookUp.find(word) != wordLookUp.end())
            return true;

        for (int i = start_index; i < word.length(); i++) {
            string prefix = word.substr(start_index, i - start_index + 1);

            if (wordLookUp.find(prefix) != wordLookUp.end()) {
                //found prefix. Check if the rest of the word can be found
                if (canBeFormed(word, i + 1, wordLookUp) == true)
                    return true;
            }
        }
        return false;
    }
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> allConcatenatedWordsInADict;

        unordered_set<string> wordLookUp;
        int minWordLength = 0;
        for (string word : words) {
            minWordLength = min(minWordLength, (int)word.length());
            wordLookUp.insert(word);
        }        

        for (string& word : words) {
            if (word.length() > minWordLength) {
                wordLookUp.erase(word);

                bool possible = canBeFormed(word, 0, wordLookUp);
                if (possible)
                    allConcatenatedWordsInADict.push_back(word);

                wordLookUp.insert(word);
            }            
        }

        return allConcatenatedWordsInADict;
    }
};

// Word Break Problem + Skip Minimum Sized Words as they cannot be splitted + Memoization - Optimized (TLE)
class Solution3 {
private:
    bool canBeFormed(string& word, int start_index, unordered_set<string>& wordLookUp, vector<int>& memo) {
        if (start_index == word.length()) {
            return true;
        }

        if (wordLookUp.find(word) != wordLookUp.end())
            return true;

        if (memo[start_index] != -1)
            return memo[start_index];

        for (int i = start_index; i < word.length(); i++) {
            string prefix = word.substr(start_index, i - start_index + 1);

            if (wordLookUp.find(prefix) != wordLookUp.end()) {
                //found prefix. Check if the rest of the word can be found
                if (canBeFormed(word, i + 1, wordLookUp, memo) == true)
                    return memo[start_index] = true;
            }
        }
        return memo[start_index] = false;
    }
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> allConcatenatedWordsInADict;

        unordered_set<string> wordLookUp;
        int minWordLength = 0;
        for (string word : words) {
            minWordLength = min(minWordLength, (int)word.length());
            wordLookUp.insert(word);
        }

        for (string& word : words) {
            if (word.length() > minWordLength) {
                vector<int> memo(31, -1);
                wordLookUp.erase(word);

                bool possible = canBeFormed(word, 0, wordLookUp, memo);
                if (possible)
                    allConcatenatedWordsInADict.push_back(word);

                wordLookUp.insert(word);
            }
        }

        return allConcatenatedWordsInADict;
    }
};

int main() {
    Solution1 obj1;
    vector<string> words = {"cat", "dog", "catdog"};
    vector<string> result = obj1.findAllConcatenatedWordsInADict(words);
    for (auto s : result)
        cout << s << endl;

    cout << endl;

    Solution2 obj2;
    result = obj2.findAllConcatenatedWordsInADict(words);
    for (auto s : result)
        cout << s << endl;

    cout << endl;

    Solution3 obj3;
    result = obj3.findAllConcatenatedWordsInADict(words);
    for (auto s : result)
        cout << s << endl;

    cout << endl;
    
    return 0;
}
