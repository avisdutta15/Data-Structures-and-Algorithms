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
    2. For - loop based: start idx
*/

//include/exclude based
class Solution {
private:
    bool isPalindrome(string s) {
        int i = 0, j = s.length() - 1;
        while (i <= j) {
            if (s[i] != s[j])
                return false;
            i++; j--;
        }
        return true;
    }
    void solve(int idx, string s, vector<string>& currentPartition, vector<vector<string>>& allPalindromes) {
        // Base case: Reached the end of the string
        if (idx == s.length()) {
            allPalindromes.push_back(currentPartition);
            return;
        }

        for (int i = idx; i < s.length(); i++) {
            // Extract the current slice (starting at start_index, length is i - start_index + 1)
            string str = s.substr(idx, i - idx + 1);

            // Only recurse if the current slice is valid (e.g., is a palindrome)
            if (isPalindrome(str)) {
                currentPartition.push_back(str);

                // Recurse on the remaining part
                solve(i + 1, s, currentPartition, allPalindromes);

                // Undo choice
                currentPartition.pop_back();
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        vector<string> currentPartition;
        vector<vector<string>> allPalindromes;
        solve(0, s, currentPartition, allPalindromes);
        return allPalindromes;
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