#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a 
    space-separated sequence of one or more dictionary words.
    Note that the same word in the dictionary may be reused multiple times in the segmentation.
    

    Examples:
    ---------
    Input: s = "leetcode", wordDict = ["leet","code"]
    Output: true
    Explanation: Return true because "leetcode" can be segmented as "leet code".


    Input: s = "applepenapple", wordDict = ["apple","pen"]
    Output: true
    Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
    Note that you are allowed to reuse a dictionary word.

    Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
    Output: false

    Constraints:
    ------------
        1 <= s.length <= 300
        1 <= wordDict.length <= 1000
        1 <= wordDict[i].length <= 20
        s and wordDict[i] consist of only lowercase English letters.
        All the strings of wordDict are unique.

    Approach:
    ---------
    String Partitioning
    for every index i in string
        Extract Prefix (start_index to i).
        Validate Prefix (in this case check if present in the dict)
        Recurse for the rest of the string. (start_index = i+1, s, dict)

    Base Cases:
    -----------
    1. If start_index >= string_length => return true
    

    Recursion Tree
    s = "leetcode" 
    dict = {"leet","code"}
                                 
Level 0:                                    solve(0)
                        [Looping i from 0 to 7. Remaining: "leetcode"]
                                 |
                                 |-- i = 0: prefix "l"    (Not in dict)
                                 |-- i = 1: prefix "le"   (Not in dict)
                                 |-- i = 2: prefix "lee"  (Not in dict)
                                 |-- i = 3: prefix "leet" [IN DICT!] -> Call solve(4)
                                                                            |
                                 --------------------------------------------
                                 |
Level 1:                      solve(4)
               [Looping i from 4 to 7. Remaining: "code"]
                        |
                        |-- i = 4: prefix "c"    (Not in dict)
                        |-- i = 5: prefix "co"   (Not in dict)
                        |-- i = 6: prefix "cod"  (Not in dict)
                        |-- i = 7: prefix "code" [IN DICT!] -> Call solve(8)
                                                                   |
                        --------------------------------------------
                        |
Level 2:             solve(8)
              [start_index == 8]
             Base Case Reached! 
        Returns True (Sets memo[8] = 1)


    How Memoization is used?
    Let's use a new Word Break example that fails, forcing the algorithm to try everything:
        
        s = "aab"
        wordDict = ["a", "aa"]

    solve(0)  [Remaining: "aab"]
      |
      |-- i=0: prefix "a" (In dict) -> Call solve(1)  [Remaining: "ab"]
      |                                   |
      |                                   |-- i=1: prefix "a" (In dict) -> Call solve(2) [Remaining: "b"]
      |                                   |                                   |
      |                                   |                                   |-- i=2: prefix "b" (Not in dict)
      |                                   |                                   Returns FALSE
      |                                   |
      |                                   |-- i=2: prefix "ab" (Not in dict)
      |                                   Returns FALSE
      |
      |-- i=1: prefix "aa" (In dict) -> Call solve(2) [Remaining: "b"]
                                              |
                                              |-- i=2: prefix "b" (Not in dict)
                                              Returns FALSE

    Notice that solve(2) (which evaluates the remaining string "b") is called twice.
    Once after taking "a" then "a".
    Again after taking "aa".
    In a small string, this is fine. But in a string like "aaaaaaaaab", this overlapping 
    explodes exponentially, causing millions of redundant solve() calls.

    Now, let's watch the cache (memo) intercept and trim the tree. Remember, our memo 
    array starts as [-1, -1, -1, -1].

    memo is used as both visited array as well as a memoization cache (able to break at start_index or not).
    solve(0)
      |
      |-- i=0: prefix "a" -> Call solve(1)
      |                         |
      |                         |-- i=1: prefix "a" -> Call solve(2)
      |                                                   |
      |                                                   |-- i=2: "b" fails.
      |                                                   *CACHE SAVES RESULT*: memo[2] = 0
      |                                                   Returns FALSE
      |                         |
      |                         *CACHE SAVES RESULT*: memo[1] = 0
      |                         Returns FALSE
      |
      |-- i=1: prefix "aa" -> Call solve(2)
                                 |
                                 *MEMOIZATION KICKS IN!*
                                 Checks: if (memo[2] != -1)
                                 It sees memo[2] is 0.
                                 Instantly Returns FALSE. (Branch cut off!)

*/

class Solution1 {
private:
    bool solve(int start_index, string& s, unordered_set<string>& wordDictLookup) {
        //if we have reached the end of the string then that means
        //we have found all the words in the dictionary
        if (start_index == s.length())
            return true;

        //if this entire word is in the dict then return true
        if (wordDictLookup.find(s) != wordDictLookup.end())
            return true;

        //try every possible prefix at this position
        for (int i = start_index; i < s.length(); i++) {
            // Extract the current prefix [startIndex...i]
            string prefix = s.substr(start_index, i - start_index + 1);

            //if prefix exists in the dictionary, then look for the remaining
            //string in the dictionary
            if (wordDictLookup.find(prefix) != wordDictLookup.end()) {
                if (solve(i + 1, s, wordDictLookup) == true)
                    return true;
            }
        }

        return false;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordDictLookup(wordDict.begin(), wordDict.end());
        int start_index = 0;
        return solve(start_index, s, wordDictLookup);
    }
};

// Memoization
class Solution2 {
private:
    bool solve(int start_index, string& s, unordered_set<string>& wordDictLookup, vector<int>& memo) {
        // if we have reached the end of the string then that means
        // we have found all the words in the dictionary
        if (start_index == s.length())
            return memo[start_index] = true;

        //if this entire word is in the dict then return true
        if (wordDictLookup.find(s) != wordDictLookup.end())
            return memo[start_index] = true;

        // Check memoization cache
        if (memo[start_index] != -1)
            return memo[start_index];

        // try every possible prefix at this position
        for (int i = start_index; i < s.length(); i++) {
            // Extract the current prefix [startIndex...i]
            string prefix = s.substr(start_index, i - start_index + 1);

            // if prefix exists in the dictionary, then look for the remaining
            // string in the dictionary
            if (wordDictLookup.find(prefix) != wordDictLookup.end()) {
                if (solve(i + 1, s, wordDictLookup, memo) == true)
                    return memo[start_index] = true;
            }
        }

        return memo[start_index] = false;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordDictLookup(wordDict.begin(), wordDict.end());

        // -1 : not visited 0: visited and false 1: visited and true
        // Initialize with -1 to indicate "unvisited"
        vector<int> memo(s.length() + 1, -1);

        int start_index = 0;
        return solve(start_index, s, wordDictLookup, memo);
    }
};

int main() {
    Solution1 obj;
    string s = "leetcode";
    vector<string> wordDict = { "leet","code" };
    cout << obj.wordBreak(s, wordDict) << endl;


    s = "applepenapple";
    wordDict = { "apple", "pen" };
    cout << obj.wordBreak(s, wordDict) << endl;

    s = "catsandog";
    wordDict = { "cats", "dog", "sand", "and", "cat" };
    cout << obj.wordBreak(s, wordDict) << endl;

    return 0;
}
