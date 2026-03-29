#include <bits/stdc++.h>
using namespace std;

class Solution{

    public:
        int count(string s, int i, int j){
            
            //Only 1 character left then return 1 as it is also a subsequence of length 1
            if(i==j) 
                return 1;
            
            //If both the characters match
            if(s[i]==s[j]){
                return count(s, i+1, j) + count(s, i, j-1) + 1;
            }

            //If both the characters donot match
            return count(s, i+1, j) + count(s, i, j-1) - count(s, i+1, j-1);
        }

        int countAllPalindromicSubsequences(string s){
            return count(s, 0, s.size()-1);
        }

        int countAllPalindromicSubsequencesDP(string str){
            int n = str.size();
            int lookup[n][n] = {0};

            //each character in itself is a palindromic subsequence
            for(int i=0; i<n; i++)
                lookup[i][i] = 1;

            //Finding palindromes of length 2 to n and counting them
            for(int current_length = 2; current_length<=n; current_length++){

                for(int start_index=0; start_index<(n-current_length+1); start_index++)
                {
                    int end_index = start_index + current_length - 1;
                    if(str[start_index]==str[end_index])
                        lookup[start_index][end_index] = lookup[start_index+1][end_index] + 
                                                         lookup[start_index][end_index-1] + 1;
                    else
                        lookup[start_index][end_index] = lookup[start_index+1][end_index] +
                                                         lookup[start_index][end_index-1] -
                                                         lookup[start_index+1][end_index-1];
                }
            }
            return lookup[0][n-1];
        }
};

/*
       A B C B A
    A  1 2 3 6 13 
    B  0 1 2 5 6 
    C  0 0 1 2 3 
    B  0 0 0 1 2 
    A  0 0 0 0 1 

*/

int main(){
    Solution obj;
    string str = "abcba";

    cout<<obj.countAllPalindromicSubsequencesDP(str);

    return 0;
}