#include <bits/stdc++.h>
using namespace std;

/*
    Given a string str, the task is to find the minimum number of characters to be inserted to convert it to palindrome.
    Before we go further, let us understand with few examples:

    ab: Number of insertions required is 1 i.e. bab
    aa: Number of insertions required is 0 i.e. aa
    abcd: Number of insertions required is 3 i.e. dcbabcd
    abcda: Number of insertions required is 2 i.e. adcbcda which is same as number of insertions in the substring bcd(Why?).
    abcde: Number of insertions required is 4 i.e. edcbabcde


    Recurrence?
        if(l==r)  //single character
            return 0;
        if(l+1 == r)  //2 characters
            return s[l] == s[r]? 0 : 1;
        
        if(s[l] == s[r])  //if the first and last characters match then recur for remaining str
            return proc(s, l+1, r-1);
        if(s[l] != s[r])  
            return 1 + min(proc(str, l+1, r), proc(str, l, r-1));


    Overlapping Subproblem:
                                (0,4)
                           /           \
                        (0,3)         (1,4)
                        /   \        /     \ 
                      (0,2) (1,3)   (1,3)  (2, 4)


    Another Approach:
    minimum insertions = N-Longest Palindromic Subsequence.
    
*/

class Solution{
    public:
        int minimumInsertionsToFormPalindromeStringUtil(string str, int l, int r){
            if(l>r) 
                return INT_MAX;

            //if only one character then it is already a palindrome
            if(l == r) 
                return 0;

            //if there are two characters then check if they are same or not.
            //if not same then only any one character can be inserted to make it palindrome
            if(l+1 == r){
                return str[l] == str[r] ? 0 : 1;
            }

            //if both characters are same then recurse for the remaining characters
            if(str[l] == str[r])
                return minimumInsertionsToFormPalindromeStringUtil(str, l+1, r-1);

            return 1 + min(minimumInsertionsToFormPalindromeStringUtil(str, l+1, r),
                           minimumInsertionsToFormPalindromeStringUtil(str, l, r-1));
        }

        int minimumInsertionsToFormPalindromeString(string str){
            int l = 0;
            int r = str.length()-1;

            return minimumInsertionsToFormPalindromeStringUtil(str, l, r);
        }
};

class Solution2{
    public:
        int minimumInsertionsToFormPalindromeStringUtil(string str, int l, int r, unordered_map<string, int> &dict){
            if(l>r) 
                return INT_MAX;

            string key = to_string(l) + "|" + to_string(r);
            if(dict.find(key)!=dict.end())
                return dict[key];

            //if only one character then it is already a palindrome
            if(l == r)
                return 0;

            //if there are two characters then check if they are same or not.
            //if not same then only any one character can be inserted to make it palindrome
            if(l+1 == r){
                dict[key] = (str[l] == str[r]) ? 0 : 1;
                return dict[key];
            }

            //if both characters are same then recurse for the remaining characters
            if(str[l] == str[r]){
                dict[key] = minimumInsertionsToFormPalindromeStringUtil(str, l+1, r-1, dict);
            }
            else{
                dict[key] = 1 + min(minimumInsertionsToFormPalindromeStringUtil(str, l+1, r, dict),
                                    minimumInsertionsToFormPalindromeStringUtil(str, l, r-1, dict));
            }
            return dict[key];
        }

        int minimumInsertionsToFormPalindromeString(string str){
            int l = 0;
            int r = str.length()-1;
            unordered_map<string, int> dict;
            return minimumInsertionsToFormPalindromeStringUtil(str, l, r, dict);
        }
};


int main(){
    Solution2 obj;
    cout<<obj.minimumInsertionsToFormPalindromeString("abc")<<endl;
    cout<<obj.minimumInsertionsToFormPalindromeString("aabca")<<endl;
}