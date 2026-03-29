#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
        void util(string str, int low, int high, unordered_set<string> &ans){
            while(low>=0 && high<str.length() && str[low]==str[high]){
                ans.insert(str.substr(low, high-low+1));
                low--;
                high++;
            }
        }
        vector<string> findAllDistinctPalindromicSubStr(string str){
            unordered_set<string> ans;

            for(int i=0; i<str.length(); i++){
                //check for odd length palindrome with str[i] as mid point
                util(str, i, i, ans);

                //check for even length palindrome with str[i] and str[i+1] as mid point
                util(str, i, i+1, ans);
                
            }
            vector<string> uniquePalindromes(ans.begin(), ans.end());
            return uniquePalindromes;
        }
};

int main(){
    string str = "google";
    Solution obj;
    vector<string> ans = obj.findAllDistinctPalindromicSubStr(str);
    if(ans.size()==0)
        cout<<"No Palindromic Substring";
    else{
        for(string s : ans)
            cout<<s<<endl;
    }
    return 0;
}