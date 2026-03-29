#include <bits/stdc++.h>
using namespace std;

/*
    Given 3 strings say s1, s2 and s3. The task is to find the longest common sub-sequence in all three given sequences.

    Examples: 
    Input:  s1 = “geeks” , s2 = “geeksfor”, s3 = “geeksforgeeks”
    Output : 5
    Explanation: Longest common subsequence is “geeks” i.e., length = 5

    Input: s1= “abcd1e2” , s2= “bc12ea” , s3= “bd1ea”
    Output: 3
    Explanation: Longest common subsequence is “b1e” i.e. length = 3.
*/

class Solution{
        int LCSofThreeStringsRecursive(string &s1, int N1, string &s2, int N2, string &s3, int N3){
            // Base case: If any of the strings is empty
            if(N1 == 0 || N2 == 0 || N3 == 0)
                return 0;

            // If last characters of s1, s2, and s3 are the same
            if(s1[N1-1] == s2[N2-1] && s2[N2-1] == s3[N3-1])
                return 1 + LCSofThreeStringsRecursive(s1, N1-1, s2, N2-1, s3, N3-1);
            
            // If last characters are not the same, calculate
            // LCS by excluding one string at a time
            return max({
                    LCSofThreeStringsRecursive(s1, N1-1, s2, N2, s3, N3),
                    LCSofThreeStringsRecursive(s1, N1, s2, N2-1, s3, N3),
                    LCSofThreeStringsRecursive(s1, N1, s2, N2, s3, N3-1)});
        }

    public:
        int LCSofThreeStrings(string s1, string s2, string s3){
            int N1 = s1.length(), N2 = s2.length(), N3 = s3.length();

            return LCSofThreeStringsRecursive(s1, N1, s2, N2, s3, N3);            
        }
};


int main(){
    Solution obj;
    string s1 = "AGGT12";
    string s2 = "12TXAYB";
    string s3 = "12XBA";
    cout<<obj.LCSofThreeStrings(s1, s2, s3)<<endl;

    return 0;
}