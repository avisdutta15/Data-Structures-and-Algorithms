#include <algorithm>
#include <iostream>
#include <climits>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: (LeetCode 140 - Word Break II)
    ------------------
    Given a string s and a dictionary of strings wordDict, add spaces in s to
    construct a sentence where each word is a valid dictionary word.
    Return ALL such possible sentences in any order.

    Examples:
    --------
    Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
    Output: ["cats and dog","cat sand dog"]

    Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
    Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]

    Constraints:
    ------------
    - 1 <= s.length <= 20
    - 1 <= wordDict.length <= 1000

    Approach:
    ---------
    Same as Word Break I, but instead of returning true/false, we collect ALL
    valid sentences. Use backtracking to build the sentence word by word.

    Recurrence:
        solve(start_index, currentSentence):
            if start_index == n:
                result.add(currentSentence)     // found one valid segmentation
                return

            for i = start_index to n-1:
                word = s[start_index..i]
                if word in dict:
                    solve(i+1, currentSentence + word + " ")

        Answer: solve(0, "")

    Memoization version returns list of all sentences from start_index onwards:
        solve(start_index):
            if start_index == n: return [""]

            sentences = []
            for i = start_index to n-1:
                word = s[start_index..i]
                if word in dict:
                    suffixSentences = solve(i+1)
                    for each suffix in suffixSentences:
                        sentences.add(word + " " + suffix)

            return sentences

        Answer: solve(0)

    Time: O(2^n * n) worst case (exponential number of valid sentences)
    Space: O(2^n * n) for storing results
*/

// ============================================================================
// Solution 1: Backtracking (build sentence as you go)
// Time: O(2^n * n), Space: O(n) recursion stack + O(2^n) results
// ============================================================================
class Solution1 {
private:
    void solve(string& s, int start_index, unordered_set<string>& dict,
               string currentSentence, vector<string>& result) {
        // Reached end — found a valid segmentation
        if (start_index == s.size()) {
            // Remove trailing space
            result.push_back(currentSentence.substr(0, currentSentence.size() - 1));
            return;
        }

        // Try every possible word starting at start_index
        for (int i = start_index; i < (int)s.size(); i++) {
            string word = s.substr(start_index, i - start_index + 1);

            // If prefix exists in dictionary, recurse on suffix
            if (dict.count(word)) {
                solve(s, i + 1, dict, currentSentence + word + " ", result);
            }
        }
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<string> result;
        solve(s, 0, dict, "", result);
        return result;
    }
};

// ============================================================================
// Solution 2: Memoization (return all sentences from start_index)
// Time: O(2^n * n), Space: O(2^n * n)
// ============================================================================
/*
    To memoize this problem, we have to make a fundamental shift in how the recursive function works.
    In your original backtracking code, the function has a void return type and modifies a current_sentence
    variable on the way down the tree.

    To use memoization, the function needs to return the results (all valid sentences for a given substring)
    so we can cache them and build the sentences on the way up the tree.
*/
class Solution2 {
private:
    vector<string> solve(string& s, int start_index, unordered_set<string>& dict,
                         unordered_map<int, vector<string>>& memo) {
        // Check cache
        if (memo.find(start_index) != memo.end())
            return memo[start_index];

        vector<string> sentences;

        // Reached end — return empty string (base case for joining)
        if (start_index == s.size()) {
            sentences.push_back("");
            return sentences;
        }

        // Try every possible word starting at start_index
        for (int i = start_index; i < (int)s.size(); i++) {
            string prefix = s.substr(start_index, i - start_index + 1);

            if (dict.count(prefix)) {
                // Get all valid sentences for the suffix
                vector<string> suffixSentences = solve(s, i + 1, dict, memo);

                // Combine our current valid prefix with all valid suffixes
                for (string& suffix : suffixSentences) {
                    if (suffix.empty())
                        // If suffix is empty, this prefix reached the very end of the string
                        sentences.push_back(prefix);
                    else
                        // Otherwise, add a space between the prefix and the suffix
                        sentences.push_back(prefix + " " + suffix);
                }
            }
        }

        // Store the calculated list in our memo cache before returning
        memo[start_index] = sentences;
        return sentences;
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        unordered_map<int, vector<string>> memo;
        return solve(s, 0, dict, memo);
    }
};


int main() {
    Solution1 backtrack;
    Solution2 memo;

    string s1 = "catsanddog";
    vector<string> dict1 = {"cat", "cats", "and", "sand", "dog"};

    cout << "Backtracking:" << endl;
    auto res1 = backtrack.wordBreak(s1, dict1);
    for (auto& sentence : res1) cout << "  \"" << sentence << "\"" << endl;

    cout << "Memoization:" << endl;
    auto res2 = memo.wordBreak(s1, dict1);
    for (auto& sentence : res2) cout << "  \"" << sentence << "\"" << endl;

    return 0;
}
