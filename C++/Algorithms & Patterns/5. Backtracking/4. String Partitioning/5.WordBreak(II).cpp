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
    Given a string s and a dictionary of strings wordDict, add spaces in s to construct a 
    sentence where each word is a valid dictionary word. Return all such possible sentences in any order.
    
    Note that the same word in the dictionary may be reused multiple times in the segmentation.
    

    Examples:
    ---------
    Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
    Output: ["cats and dog","cat sand dog"]


    Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
    Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
    Explanation: Note that you are allowed to reuse a dictionary word.

    Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
    Output: []

    Constraints:
    ------------
        1 <= s.length <= 20
        1 <= wordDict.length <= 1000
        1 <= wordDict[i].length <= 10
        s and wordDict[i] consist of only lowercase English letters.
        All the strings of wordDict are unique.
        Input is generated in a way that the length of the answer doesn't exceed 10^5.

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
    


    Recursion Tree:
    ---------------
    solve(idx=0, curr="")
      |
      |-- prefix "cat" -> solve(3, curr="cat")
      |                     |
      |                     |-- prefix "sand" -> solve(7, curr="cat sand")
      |                                            |
      |                                            |-- prefix "dog" -> solve(10, curr="cat sand dog")
      |                                                                 |
      |                                                           [BASE CASE REACHED]
      |                                                           Add "cat sand dog" to global list.
      |
      |-- prefix "cats" -> solve(4, curr="cats")
                            |
                            |-- prefix "and" -> solve(7, curr="cats and")
                                                  |
                                                  |-- prefix "dog" -> solve(10, curr="cats and dog")
                                                                        |
                                                                  [BASE CASE REACHED]
                                                                  Add "cats and dog" to global list.
    
    
    Takeaway: solve(7) is executed twice. It does the exact same work of finding "dog", but because it is 
    carrying the history of the sentence with it, it doesn't realize it's repeating work.                     
    

    In the memoized approach currently in your Canvas, the function is "blind" to the history of the sentence. 
    It only cares about the start_index. It asks: "What are all the valid suffixes from index X to the end?" 
    Because of this, it can cache the result for index 7 and instantly reuse it the second time.

    solve(0)
      |
      |-- prefix "cat" -> call solve(3)
      |                     |
      |                     |-- prefix "sand" -> call solve(7)
      |                                            |
      |                                            |-- prefix "dog" -> call solve(10)
      |                                                                 |
      |                                                           [BASE CASE] Returns {""}
      |                                            |
      |                                            Appends "dog" + {""} -> Returns {"dog"}
      |                                            *CACHES: memo[7] = {"dog"}*
      |                     |
      |                     Appends "sand" + {"dog"} -> Returns {"sand dog"}
      |                     *CACHES: memo[3] = {"sand dog"}*
      |
      |-- prefix "cats" -> call solve(4)
                            |
                            |-- prefix "and" -> call solve(7)
                                                  |
                                            [CACHE HIT at index 7!]
                                            Sees memo[7] is already {"dog"}.
                                            Instantly Returns {"dog"} without re-evaluating!
                            |
                            Appends "and" + {"dog"} -> Returns {"and dog"}
                            *CACHES: memo[4] = {"and dog"}*

    [FINAL STEP at solve(0)]
    Combines the returned lists with its prefixes:
    1. "cat" + {"sand dog"} = "cat sand dog"
    2. "cats" + {"and dog"} = "cats and dog"
    Returns {"cat sand dog", "cats and dog"}

    Takeaway: When solve(4) calls solve(7), the tree gets aggressively pruned. The memoization cache intercepted the call, 
    completely skipping the need to evaluate "dog" a second time, and immediately returned the pre-built suffix list to 
    be attached to "cats and".
    
*/

class Solution1 {
private:
    void solve(int start_index, string& s, unordered_set<string>& wordDictLookup, string& current_sentence, vector<string>& all_strings) {
        //if we have reached the end of the string then that means
        //we have found all the words in the dictionary
        if (start_index == s.length()) {
            all_strings.push_back(current_sentence);
            return;
        }

        //try every possible prefix at this position
        for (int i = start_index; i < s.length(); i++) {
            // Extract the current prefix [startIndex...i]
            string prefix = s.substr(start_index, i - start_index + 1);

            if (wordDictLookup.find(prefix) != wordDictLookup.end()) {
                //check if the rest of the string can be partitioned
                current_sentence = current_sentence.length() == 0 ? prefix : current_sentence + " " + prefix;

                solve(i + 1, s, wordDictLookup, current_sentence, all_strings);

                //backtrack
                //remove the prefix that we added
                if (start_index == 0)   // if we need to remove the first word then make it ""
                    current_sentence = "";
                else
                    current_sentence = current_sentence.substr(0, current_sentence.length() - prefix.length() - 1);
            }
        }
        return;
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordDictLookup(wordDict.begin(), wordDict.end());
        int start_index = 0;
        string current_sentence;
        vector<string> all_strings;
        solve(start_index, s, wordDictLookup, current_sentence, all_strings);
        return all_strings;
    }
};



// Memoization
/*
    To memoize this problem, we have to make a fundamental shift in how the recursive function works. 
    In your original backtracking code, the function has a void return type and modifies a current_sentence 
    variable on the way down the tree.

    To use memoization, the function needs to return the results (all valid sentences for a given substring) 
    so we can cache them and build the sentences on the way up the tree.
*/
class Solution2 {
private:
    // The memoization cache: maps a start_index to all valid sentence endings from that index
    vector<string> solve(int start_index, string& s, unordered_set<string>& wordDictLookup, unordered_map<int, vector<string>>& memo) {

        // 1. Check Cache
        // If we have already calculated all valid sentences from this start_index, return them!
        if (memo.find(start_index) != memo.end()) {
            return memo[start_index];
        }

        // 2. Base Case
        // If we reach the end of the string, return a vector with an empty string.
        // This acts as a "success signal" for the caller to append to.
        if (start_index == s.length()) {
            return { "" };
        }

        vector<string> valid_sentences_from_here;

        // 3. Try every possible prefix
        for (int i = start_index; i < s.length(); i++) {
            // Extract the current prefix [startIndex...i]
            string prefix = s.substr(start_index, i - start_index + 1);

            if (wordDictLookup.find(prefix) != wordDictLookup.end()) {

                // Get all valid sentence endings for the REST of the string
                vector<string> valid_suffixes = solve(i + 1, s, wordDictLookup, memo);

                // Combine our current valid prefix with all valid suffixes
                for (const string& suffix : valid_suffixes) {
                    if (suffix == "") {
                        // If suffix is empty, this prefix reached the very end of the string
                        valid_sentences_from_here.push_back(prefix);
                    }
                    else {
                        // Otherwise, add a space between the prefix and the suffix
                        valid_sentences_from_here.push_back(prefix + " " + suffix);
                    }
                }
            }
        }

        // 4. Store the calculated list in our memo cache before returning
        return memo[start_index] = valid_sentences_from_here;
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordDictLookup(wordDict.begin(), wordDict.end());

        // Cache: maps index -> List of valid string combinations from that index
        unordered_map<int, vector<string>> memo;

        return solve(0, s, wordDictLookup, memo);
    }
};


int main() {
    Solution1 obj;
    string s = "catsanddog";
    vector<string> wordDict = { "cat", "cats", "and", "sand", "dog" };
    vector<string> result = obj.wordBreak(s, wordDict);
    for (auto s : result)
        cout << s << endl;

    cout << endl;


    s = "pineapplepenapple";
    wordDict = { "apple", "pen", "applepen", "pine", "pineapple" };
    result = obj.wordBreak(s, wordDict);
    for (auto s : result)
        cout << s << endl;

    cout << endl;


    s = "catsandog";
    wordDict = { "cats", "dog", "sand", "and", "cat" };
    result = obj.wordBreak(s, wordDict);
    for (auto s : result)
        cout << s << endl;

    cout << endl;

    return 0;
}
