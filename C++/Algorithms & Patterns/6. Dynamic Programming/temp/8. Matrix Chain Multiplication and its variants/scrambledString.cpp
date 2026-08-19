#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    We can scramble a string s to get a string t using the following algorithm:

    If the length of the string is 1, stop.
    If the length of the string is > 1, do the following:
    
    Split the string into two non-empty substrings at a random index, i.e., if 
    the string is s, divide it to x and y where s = x + y.
    
    Randomly decide to swap the two substrings or to keep them in the same order. 
    i.e., after this step, s may become s = x + y or s = y + x.
    
    Apply step 1 recursively on each of the two substrings x and y.
    Given two strings s1 and s2 of the same length, return true if s2 is a scrambled 
    string of s1, otherwise, return false.

    

    Example 1:

    Input: s1 = "great", s2 = "rgeat"
    Output: true
    Explanation: One possible scenario applied on s1 is:
    "great" --> "gr/eat" // divide at random index.
    "gr/eat" --> "gr/eat" // random decision is not to swap the two substrings and keep them in order.
    "gr/eat" --> "g/r / e/at" // apply the same algorithm recursively on both 
    substrings. divide at ranom index each of them.

    "g/r / e/at" --> "r/g / e/at" // random decision was to swap the first substring 
    and to keep the second substring in the same order.
    
    "r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively, divide "at" to "a/t".
    "r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both substrings in the same order.
    The algorithm stops now and the result string is "rgeat" which is s2.
    As there is one possible scenario that led s1 to be scrambled to s2, we return true.

*/

class Solution {
    unordered_map<string, bool> map;
public:
    bool isScramble(string s1, string s2){
        string key = s1+" | "+s2;
        if(map.find(key)!=map.end())
            return map[key];
        
        //if both are equal then return true
        if(s1==s2)
            return true;
        
        int sizeS1 = s1.length(), sizeS2 = s2.length();
        
        //both have different size then return false;
        if(sizeS1!=sizeS2)
            return false;
        
        //both having one character. check equality
        if(sizeS1==1 && sizeS2==1)
            return s1==s2;
        
        //both are of same size. check if the characters and their freq in both the strings are same and equal. 
        string temp1 = s1, temp2 = s2;
        sort(temp1.begin(), temp1.end());
        sort(temp2.begin(), temp2.end());
        
        //if not same then return false
        if(temp1!=temp2)
            return false;
        
        int N = sizeS1;
        for(int i=1; i<=N-1; i++){
            //no swap
            if(isScramble(s1.substr(0, i), s2.substr(0, i)) && isScramble(s1.substr(i), s2.substr(i)))
                return map[key] = true;
            
            //swap
            if(isScramble(s1.substr(0, i), s2.substr(N-i)) && isScramble(s1.substr(i), s2.substr(0,N-i)))
                return map[key] = true;
        }
        return map[key] = false;
    }
};


int main(){
    Solution obj;
}