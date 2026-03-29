#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    Given a string, find the count of distinct subsequences of it.
        Example:
        I/P: gfgg
        O/P: 10

        All the subsequences are: (append str[i] to all the available subsequences seen)
        
        "",
        "", g
        "", g, f, gf
        "", g, f, gf, g, gg, fg, gfg
        "", g, f, gf, g, gg, fg, gfg, g, fg, gfg, gg, ggg, fgg, gfgg
        
        Among them the distinct are:
        "", g, f, gf, gg, fg, gfg, ggg, fgg, gfgg 

    Approach 1:
        Generate all subsequences, and store them in a hash table. Size of the hash table is 
        the answer. Time Required - Exponential

    Approach 2:
        count(n) = 2 * count(n-1) - Repititions
        where Repititions = No of subsequences which previously ended with current character i.e. str[n-1].
        count(n) contains the number of subsequences which ended with the current character i.e. str[n-1].
        count(0) = 1 because it denotes the count of empty string

        How This Works? - Lets understand part by part
        A.  2 * count(n-1)
            This is because we will append the current character str[n-1] with all the 
            subsequences seen so far which is given by count(n-1).
        B.  -Repititions
            If the current character has not appreared before in the given string then
            Repitition = 0
            Else Repitition = count(m) where m is the index of previous occurence of current
            character str[n-1]. 

    Lets understand Approach 2 in detail:
    Lets create an array DP[n+1] where n = str.length(). 
    Why n+1?? To accomodate empty string "".
    Now DP[0] = 1 ?? count of empty string is 1

    current_char = g. 
    Append g to all the existing susequences
    existing susequences: {""}
    new subsequences :    {"", "g"}
    DP[1] = 2 * DP[0]
          = 2
          See we appended g to all the existing subsequences which doubles the ans.
    Did current character g apprear before? No. So Repitition = 0

    current_char = f.
    Append f to all the existing susequences
    existing susequences: {"", "g"}
    new subsequences :    {"", "g", "f", "gf"}
    DP[2] = 2 * DP[1]
          = 4
          See we appended f to all the existing subsequences which doubles the ans.
    Did current character f apprear before? No. So Repitition = 0

    current_char = g.
    Append g to all the existing susequences
    existing susequences: {"", "g", "f", "gf"}
    new subsequences :    {"", "g", "f", "gf", "g", "gg", "fg", "gfg"}
    DP[3] = 2 * DP[2]
          = 8
          See we appended g to all the existing subsequences which doubles the ans.
    Did current character g apprear before? Yes.
    It appeared at index = 0.
    DP[0] = 1. It means we had appended the previous occurrence of g to 1 subsequence i.e. "".
    So, we have to remove all the previous subsequences which is a result of append of g.
    DP[3] = 8 - DP[1]
          = 7
    new subsequences :    {"", "f", "gf", "g", "gg", "fg", "gfg"} [Look first "g" is removed]

    current_char = g.
    Append g to all the existing susequences
    existing susequences: {"", "f", "gf", "g", "gg", "fg", "gfg"} 
    new subsequences :    {"", "f", "gf", "g", "gg", "fg", "gfg", "g", "fg", "gfg", "gg", "ggg", "fgg", "gfgg"}
    DP[4] = 2 * DP[3]
          = 14
          See we appended g to all the existing subsequences which doubles the ans.
    Did current character g apprear before? Yes.
    It appeared at index = 2.
    DP[2] = 4. It means we had appended the previous occurrence of g to 4 subsequences i.e. "gf", "g", "gg", "fg", "gfg".
    So, we have to remove all the previous subsequences which is a result of append of g.
    DP[3] = 14 - DP[2]
          = 10

*/


class Solution{
    public:
        int countDistinctSubsequences(string s){
            int n = s.length();
            int DP[n+1];
            DP[0] = 1;

            unordered_map<char, int>index_map;

            // Traverse through all lengths from 1 to n. 
            for(int i=1; i<=n; i++){
                
                // Number of subsequences with substring str[0..i-1] 
                DP[i] = 2 * DP[i-1];

                // If current character has appeared before, then remove all subsequences 
                // ending with previous occurrence.
                char currentChar = s[i-1];
                if(index_map.find(currentChar)!=index_map.end()){
                    
                    DP[i] = DP[i] - DP[index_map[s[i-1]]];
                }
                
                // Mark occurrence of current character 
                index_map[s[i-1]] = i-1;
            }
            return DP[n];
        }
};

int main(){
    Solution obj;
    string s = "gfgg";
    cout<<obj.countDistinctSubsequences(s);
    return 0;
}