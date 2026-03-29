#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
        int countWaysToIncreaseLCSByOne(string str1, string str2){
            int len1 = str1.length();
            int len2 = str2.length();
            int LCS = 0, ways = 0;

            vector<vector<int>> DPLeft(len1+1,vector<int>(len2+1,0));
            for(int i=1; i<=len1; i++){
                for(int j=1; j<=len2; j++){
                    if(str1[i-1] == str2[j-1])
                        DPLeft[i][j] = 1 + DPLeft[i-1][j-1];
                    else
                        DPLeft[i][j] = max(DPLeft[i-1][j], DPLeft[i][j-1]);
                }
            }
            
            
            
            vector<vector<int>> DPRight(len1+2,vector<int>(len2+2,0));
            for(int i=len1; i>=1; i--){
                for(int j=len2; j>=1; j--){
                    if(str1[i-1] == str2[j-1])
                        DPRight[i][j] = 1 + DPRight[i+1][j+1];
                    else
                        DPRight[i][j] = max(DPRight[i+1][j], DPRight[i][j+1]);
                }
            }

            //store the position of every letter in B.
            //if a character occurs multiple times, then store its all indexes.
            unordered_map<int, vector<int>> position;
            for(int i=0; i<len2; i++){
                char c = str2[i];
                int charToIntKey = 0;
                if(c>='a' && c<='z')
                    charToIntKey = c - 'a';
                if(c>='A' && c<='Z')
                    charToIntKey = c - 'A' + 26; //26 is added for displacement
                
                position[charToIntKey].push_back(i+1);
            }
            
            
            //inserting the character between the position i and i+1 of str1
            for(int posA=0; posA<=len1; posA++){

                //for all the 26 characters 
                for(int j=0; j<=52; j++){
                    if(position.find(j)!=position.end()){
                        for(auto x : position[j]){
                            if(DPLeft[posA][x-1] + DPRight[posA+1][x+1]==LCS){
                                ways++;
                                break;
                            }
                        }
                    }
                }
            }
            return ways;
        }
};

int main(){
    Solution obj;
    string A = "aa", B = "baaa"; 
    cout<<obj.countWaysToIncreaseLCSByOne(A, B);
}