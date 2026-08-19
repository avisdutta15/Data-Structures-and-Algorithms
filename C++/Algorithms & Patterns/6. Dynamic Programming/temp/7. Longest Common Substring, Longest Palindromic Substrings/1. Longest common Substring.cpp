#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
        vector<string> longestCommonSubstring(string s1, string s2){
            int DP[s1.length()][s2.length()];
            vector<string> ans;
            int maxLen = INT_MIN;

            for(int i=0; i<s1.length(); i++){
                for(int j=0; j<s2.length(); j++){                    
                    if(s1[i] == s2[j]){                        
                        //if the match happened in the first row or column then longest common substring is 1.
                        if(i==0 || j==0)
                            DP[i][j] = 1;
                        else{
                            //recur for DP[i-1][j-1]
                            DP[i][j] = DP[i-1][j-1] + 1;

                            //if this new common string is longer than the longest found so far                            
                            if(DP[i][j] > maxLen){
                                maxLen = DP[i][j];
                                ans.clear();
                                ans.push_back(s1.substr(i-maxLen+1, maxLen));
                            }
                            else if(DP[i][j] == maxLen){
                                ans.push_back(s1.substr(i-maxLen+1, maxLen));
                            }
                        }
                    }
                    else
                        DP[i][j]=0;
                }
            }
            return ans;
        }
};

int main(){
    string str1 = "LCLC";
    string str2 = "CLCL";

    Solution obj;
    vector<string> ans = obj.longestCommonSubstring(str1, str2);
    if(ans.size() == 0)
        cout<<"No Common Substring";
    else{ 
        for(string i: ans)  
            cout<<"Longest Common Sustring: "<<i<<", ";
    }
    return 0;
}