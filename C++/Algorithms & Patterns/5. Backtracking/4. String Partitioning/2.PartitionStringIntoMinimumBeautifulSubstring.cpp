#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    Given a binary string s, partition the string into one or more substrings such that 
    each substring is beautiful.
    
    A string is beautiful if:
        - It doesn't contain leading zeros.
        - It's the binary representation of a number that is a power of 5.

    Return the minimum number of substrings in such partition. If it is impossible to 
    partition the string s into beautiful substrings, return -1.

    A substring is a contiguous sequence of characters in a string.
    

    Examples:
    ---------
    Input: s = "1011"
    Output: 2
    Explanation: We can paritition the given string into ["101", "1"].
    - The string "101" does not contain leading zeros and is the binary representation of integer 51 = 5.
    - The string "1" does not contain leading zeros and is the binary representation of integer 50 = 1.
    It can be shown that 2 is the minimum number of beautiful substrings that s can be partitioned into.

    Input: s = "111"
    Output: 3
    Explanation: We can paritition the given string into ["1", "1", "1"].
    - The string "1" does not contain leading zeros and is the binary representation of integer 50 = 1.
    It can be shown that 3 is the minimum number of beautiful substrings that s can be partitioned into.

    Input: s = "0"
    Output: -1
    Explanation: We can not partition the given string into beautiful substrings.

    Constraints:
        1 <= s.length <= 16
        s contains only lowercase English letters.

    Approach:
    ----------
    2. For - loop based: start idx
    Follow the Palindrome Partition pattern
*/

//for-loop based
class Solution {
private:
    bool isBeautifulSubstr(string s) {
        if (s.length() > 0 && s[0] == '0')
            return false;

        int num = 0;
        int twoPow = 1; //2^0 = 1

        //101 - 1*2^2 + 0*2^1 + 1*2^0
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s[i] == '1')
                num = num + twoPow;
            twoPow = twoPow * 2;
        }

        //Now check if the number is a power of 5.
        // Correct way to check for power of 5
        if (num == 0) return false;
        while (num % 5 == 0) {
            num /= 5;
        }
        return num == 1;
    }

    void solve(int idx, string s, vector<string>& currentPartition, int& minBeautiSubStr) {
        if (idx == s.length()) {
            minBeautiSubStr = min(minBeautiSubStr, (int)currentPartition.size());
            return;
        }

        for (int i = idx; i < s.length(); i++) {
            string str = s.substr(idx, i - idx + 1);
            if (isBeautifulSubstr(str)) {
                currentPartition.push_back(str);
                solve(i + 1, s, currentPartition, minBeautiSubStr);
                currentPartition.pop_back();
            }
        }
    }
public:
    int minimumBeautifulSubstrings(string s) {
        int minBeautiSubStr = INT_MAX;
        vector<string> currentPartition;
        solve(0, s, currentPartition, minBeautiSubStr);
        return minBeautiSubStr == INT_MAX ? -1 : minBeautiSubStr;
    }
};
int main() {
    Solution obj;
    string s = "1011";
    auto ans = obj.minimumBeautifulSubstrings(s);
    cout << ans;
    cout << endl;

    return 0;
}