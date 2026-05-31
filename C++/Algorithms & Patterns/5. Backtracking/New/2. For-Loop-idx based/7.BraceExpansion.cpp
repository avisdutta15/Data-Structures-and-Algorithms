#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <string.h>

using namespace std;

/*
    Problem Statement:
    -----------------
    You are given a string s representing a list of words. Each letter in the word has one or more options.

    If there is one option, the letter is represented as is.
    If there is more than one option, then curly braces delimit the options. For example, "{a,b,c}" 
    represents options ["a", "b", "c"].
    
    For example, if s = "a{b,c}", the first character is always 'a', but the second character can 
    be 'b' or 'c'. The original list is ["ab", "ac"].

    Return all words that can be formed in this manner, sorted in lexicographical order.


    Examples:
    ---------
    Example 1:
    Input: s = "{a,b}c{d,e}f"
    Output: ["acdf","acef","bcdf","bcef"]
    
    Example 2:
    Input: s = "abcd"
    Output: ["abcd"]
 

    Constraints:
    1 <= s.length <= 50
    s consists of curly brackets '{}', commas ',', and lowercase English letters.
    s is guaranteed to be a valid input.
    There are no nested curly brackets.
    All characters inside a pair of consecutive opening and ending curly brackets are different.
    
    Approach:
    ----------
    1. Parse the string and create lists of strings.
    2. Once we have the lists, it's a simple backtracking problem.

    We will create lists [[][][]]

    str = "{a,b}cd{e,f}g"
        = ["a","b"],["cd"],["e","f"],["g"]

                                 ["a","b"]
                        / {a}               \ {b}
                    ["cd"]                  ["cd"]
                      /  {acd}                  \ {bcd}
                  ["e","f"]                   ["e","f"]
                  / {acde}  \ {acdf}         / {bcde}  \{bcdf}
                ["g"]       ["g"]         ["g"]        ["g"]
                /             \            /             \
             {"acdeg"}     {"acdfg"}   {"bcdeg"}         {"bcdfg"}

*/

class Solution {
private:
    void solve(const vector<vector<string>>& lists, int list_index, string& current_str, vector<string>& result) {
        if (list_index == lists.size()) {
            result.push_back(current_str);
            return;
        }

        vector<string> current_list = lists[list_index];
        for(int string_index = 0; string_index < current_list.size(); string_index++) {
            string word = current_list[string_index];

            //add the word to the current_str
            current_str = current_str + word;

            //recurse for other lists
            solve(lists, list_index + 1, current_str, result);

            //erase this word from current_str
            current_str.erase(current_str.length() - word.length());
        }
    }

    vector<vector<string>> convertToListOfLists(string s) {
        vector<vector<string>> lists;

        // Iterate through the string and build the lists
        for (int i = 0; i < s.length(); i++) {
            vector<string> innerList;

            // {a, bc, d}
            if (s[i] == '{') {

                int j = i + 1;  //skipt the {

                //Build the list
                string str = "";
                while (j < s.length() && s[j] != '}') {

                    // if the current character is a letter
                    if (s[j] >= 'a' && s[j] <= 'z') {
                        str.push_back(s[j]);
                        j++;
                    }
                    // character is ','
                    else { 
                        if (str.length() != 0)
                            innerList.push_back(str);
                        str = "";
                        j++;
                    }
                }
                if (str.length() != 0)
                    innerList.push_back(str);
                i = j;  //i is at '}'
            }
            else {
                int j = i;
                string str = "";
                while (j < s.length() && s[j] != '{') {
                    str.push_back(s[j]);
                    j++;
                }
                innerList.push_back(str);
                i = j - 1;
            }

            lists.push_back(innerList);
        }
        return lists;
    }

public:
    vector<string> expand(string s) {
        
        // Transform the string from {a,b}cd{e,f}g  ->  [["a","b"],["cd"],["e","f"],["g"]]
        vector<vector<string>> lists = convertToListOfLists(s);
        
        vector<string> result;
        string current_str = "";
        int list_index = 0;
        
        // Run the backtracking algorithm
        solve(lists, list_index, current_str, result);

        // Sort the result before returning
        sort(result.begin(), result.end());

        return result;
    }
};

int main() {
    Solution obj;
    vector<string> result = obj.expand("{a,b}c{d,e}f");
    for (string s : result)  cout << s << endl;

    cout << endl;

    result = obj.expand("abcd");
    for (string s : result)  cout << s << endl;

    cout << endl;

    result = obj.expand("{a,b}cd{e,f}g");
    for (string s : result)  cout << s << endl;

    cout << endl;

    result = obj.expand("{ab,c}d");
    for (string s : result)  cout << s << endl;

    return 0;
}
