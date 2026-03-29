#include <bits/stdc++.h>
using namespace std;

/*
    Longest common subsequence with permutations allowed
    Given two strings in lowercase, find the longest string whose permutations 
    are subsequences of given two strings. The output longest string must be sorted.

    Examples:

        Input  :  str1 = "pink", str2 = "kite"
        Output : "ik" 
        The string "ik" is the longest sorted string 
        whose one permutation "ik" is subsequence of
        "pink" and another permutation "ki" is 
        subsequence of "kite". 

        Input  : str1 = "working", str2 = "women"
        Output : "now"

        Input  : str1 = "geeks" , str2 = "cake"
        Output : "ek"

        Input  : str1 = "aaaa" , str2 = "baba"
        Output : "aa"

    The idea is to count characters in both strings.
    calculate frequency of characters for each string and store them in their respective count arrays,
    say count1[] for str1 and count2[] for str2.
    Now we have count arrays for 26 characters. So traverse count1[] and for any index ‘i’ append 
    character (‘a’+i) in resultant string ‘result’ by min(count1[i], count2[i]) times.
    Since we traverse count array in ascending order, our final string characters will be in sorted order.
*/


class Solution{
    public:
    string LCSWithPermutation(string s1, string s2){
        if(s1.length()==0 || s2.length()==0)
            return 0;

        int freq1[26] = {0};
        int freq2[26] = {0};

        for(char c: s1)
            freq1[c-'a']++;

        for(char c: s2)
            freq2[c-'a']++;
    
        string ans = "";
        //for each character, append it the min(freq1[i], freq2[i]) times to the output
        for(int i=0; i<26; i++){

            //append character i min(freq1[i], freq2[i]) times to the output
            for(int j=1; j<=min(freq1[i], freq2[i]); j++)
                ans.push_back('a'+i);
        }
        return ans;        
    }
};

int main(){
    Solution obj;
    cout<<obj.LCSWithPermutation("geek", "kite");
}