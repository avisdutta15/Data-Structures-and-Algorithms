#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
        bool wordBreakNaiveUtil(unordered_set<string> Hash, string word){

            if(word.length()==0)
                return true;

            //Consider all prefix positions of the current string
            for(int i=1; i<=word.length(); i++){
                if(Hash.find(word.substr(0, i))!=Hash.end() && wordBreakNaiveUtil(Hash, word.substr(i, word.length()))==true)
                    return true;
            }
            return false;
        }

        bool wordBreakNaive(vector<string> dict, string word){
            unordered_set<string> Hash(dict.begin(), dict.end());
            return wordBreakNaiveUtil(Hash, word);
        }

        bool wordBreakTopDownUtil(unordered_set<string> dictionary, string word, unordered_map<int, bool> &lookup){
            
            int n = word.length();
            
            if(n==0)
                return true;

            if(lookup.find(n)==lookup.end()){
                
                lookup[n] = false;
                
                //Consider all prefix positions of the current string
                for(int i=1; i<=word.length(); i++){
                    if(dictionary.find(word.substr(0, i))!=dictionary.end() && wordBreakTopDownUtil(dictionary, word.substr(i, word.length()), lookup)==true)
                        return lookup[n] = true;
                    
                }
            }
            
            return lookup[n]=false;
        }

        bool wordBreakTopDown(vector<string> dict, string word){
            unordered_set<string> dictionary(dict.begin(), dict.end());
            unordered_map<int, bool> lookup;
            return wordBreakTopDownUtil(dictionary, word, lookup);
        }

        bool wordBreakBottomUp(vector<string> dict, string word){
            int n = word.length();
            if(n==0)
                return 0;
            unordered_set<string> dictionary(dict.begin(), dict.end());
            vector<bool> dp(n+1, false);  //dp[i] denotes str(0..i-1) can be segmented.
            dp[0] = true;

            for(int i=1; i<=n; i++){
                for(int j=0; j<i; j++){
                    //if left part is possible: dp[j] == true i.e. str[0..j-1] can be segmented
                    //then check the right part: str[j..i] in the dictionary
                    if(dp[j] == true){
                        string subword = word.substr(j, i-j);
                        if(dictionary.find(subword)!=dictionary.end()){
                            dp[i] = true;
                            break;
                        }
                    }
                }
            }
            return dp[n];
        }
};

int main(){
    vector<string> dict = {"leet", "code"};
    string word = "leetcode";

    Solution obj;
    obj.wordBreakTopDown(dict, word)==true?cout<<"Can be segmented": cout<<"Cannot be segmented";
}