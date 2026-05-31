#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    Given a string s, partition s such that every substring of the partition is a palindrome. 
    Return all possible palindrome partitioning of s.
    

    Examples:
    ---------
    Input: s = "aab"
    Output: [["a","a","b"],["aa","b"]]

    Input: s = "a"
    Output: [["a"]]

    Constraints:
        1 <= s.length <= 16
        s contains only lowercase English letters.

    Approach:
    ----------
    2. For - loop based: start idx and slicing the string
    for(i=start_index to s.length)
        slice from [start_index to i]
        if(isValid(slice)
            add to current_partitions
            recurse for start_index = i+1
            undo to explore other options

                                             solve(start=0, [])
                         /                       |                  \
                    slice "a"               slice "aa"          slice "aab"
                  (palindrome✓)            (palindrome✓)     (not palindrome✗)
                       |                        |
              solve(start=1,["a"])      solve(start=2,["aa"])
                /          \                    |
          slice "a"     slice "ab"          slice "b"
        (palindrome✓) (not palin✗)        (palindrome✓)
              |                                 |
     solve(start=2,["a","a"])         solve(start=3,["aa","b"])
              |                                 |
          slice "b"                         BASE CASE
        (palindrome✓)                    ➜ ["aa","b"] ✓
              |
     solve(start=3,["a","a","b"])
              |
          BASE CASE
         ➜ ["a","a","b"] ✓
    
*/


class Solution {
private:
    bool isPalindrome(string s){
        int i=0, j=s.length()-1;
        while(i<=j){
            if(s[i] != s[j])
                return false;
            i++; j--;
        }
        return true;
    }
    
    void solve(string s, int start_index, vector<string> &current_partitions, vector<vector<string>>& all_partitions){
        // Base case: Reached the end of the string
        if(start_index == s.length()){
            all_partitions.push_back(current_partitions);
            return;
        }

        for(int i=start_index; i<s.length(); i++){
            // Extract the current slice [startIndex...i]
            string slice = s.substr(start_index, i-start_index+1);

            // Only recurse if the current slice is valid
            if(isPalindrome(slice)){
                // add
                current_partitions.push_back(slice);

                // recurse for the remainig string i.e. start_index = i+1
                solve(s, i+1, current_partitions, all_partitions);

                // undo to explore other options
                current_partitions.pop_back();
            }
        }
    }

public:
    vector<vector<string>> partition(string s) {
        vector<string> current_partitions;
        vector<vector<string>> all_partitions;
        int start_index = 0;
        solve(s, start_index, current_partitions, all_partitions);
        return all_partitions;
    }
};

int main() {
    Solution obj;
    string s = "aab";
    auto ans = obj.partition(s);
    for (auto v : ans) {
        for(auto i: v)
            cout << i << " ";
        cout << endl;
    }
    cout << endl;

    return 0;
}
