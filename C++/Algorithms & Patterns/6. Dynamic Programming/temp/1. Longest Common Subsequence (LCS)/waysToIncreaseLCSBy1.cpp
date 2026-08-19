#include <bits/stdc++.h>
using namespace std;

class Solution{
    int toInt(char c){
        return c-'A';
    }
    public:
        int waysToIncreaseLCSBy1(string s1, string s2){
            int M = s1.length();
            int N = s2.length();
            
            vector<int> positions[26]; 
            for (int i = 0; i < N; i++) 
                positions[toInt(s2[i])].push_back(i);

            //calculate the prefix lcs
            vector<vector<int>>LCSP(M+1, vector<int>(N+1)); 

            for(int i=1; i<=M; i++){
                for(int j=1; j<=N; j++){
                    if(s1[i-1]==s2[j-1])
                        LCSP[i][j] = LCSP[i-1][j-1] + 1;
                    else
                        LCSP[i][j] = max(LCSP[i-1][j],LCSP[i][j-1]);
                }
            }    
            
            
            //calculate the suffix lcs
            vector<vector<int>>LCSS(M+2, vector<int>(N+2));           

            for(int i=M; i>=1; i--){
                for(int j=N; j>=1; j--){
                    if(s1[i-1]==s2[j-1])
                        LCSS[i][j] = LCSS[i+1][j+1] + 1;
                    else
                        LCSS[i][j] = max(LCSS[i+1][j],LCSS[i][j+1]);
                }
            }
            
            int possibleWays = 0;

            //insert into all possible positions of s1 [There are |m|+1 positions]
            for(int i=0; i<=M; i++){

                //insert a character from 26 letters, find its position in s2. Let the position be j
                //insert it at position i of s1. The LCS will increase iff 
                //LCS( s1[1..m], s2[1..n] ) = LCS( s1[1...i], s2[1...j-1]  ) + 
                //                            LCS( s1[i+1...m], s2[j+1...n])

                for(char c='A'; c<='Z'; c++){
                    //if character c is present in s2 then
                    if(positions[toInt(c)].size()!=0)
                    {
                        for(int j: positions[toInt(c)])
                            // If both, left and right substrings make 
                            // total LCS then increase result by 1 
                            if (LCSP[i][j-1] + LCSS[i+1][j+1] == LCSP[M][N]) 
                                possibleWays++; 
                    }
                }                                
            }
            return possibleWays;
        }
};

int main(){
    string s1 = "ABAB";
    string s2 = "ABC";

    Solution obj;
    cout<<obj.waysToIncreaseLCSBy1(s1, s2)<<endl;

    s1 = "ABCABC";
    s2 = "ABCD";
    cout<<obj.waysToIncreaseLCSBy1(s1, s2)<<endl;

    s1 = "AA";
    s2 = "BAAA";
    cout<<obj.waysToIncreaseLCSBy1(s1, s2);
}