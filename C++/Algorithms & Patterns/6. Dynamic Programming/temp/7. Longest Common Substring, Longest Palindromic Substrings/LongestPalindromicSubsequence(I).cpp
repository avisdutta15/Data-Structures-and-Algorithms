#include <bits/stdc++.h>
using namespace std;

/*
    Given a sequence, find the length of the longest palindromic subsequence in it.
    I/p: GeeksForGeeks
    O/P: eekee or eesee etc. All are for length 5.
*/

class Solution{
    
    public:
        string LPSNaiveUtil(string str, int i, int j){
            //There is only 1 character
            if(i==j)
                return str[i];
            //If there are 2 characters and both of them are same.
            if(str[i]==str[j] && i+1==j)
                return str[i]+str[j];
            
            //if the first and last characters match (+2 because 2 characters matched)
            string s;
            if(str[i]==str[j]){
                s = LPSNaiveUtil(str, i+1, j-1);
                s = str[i]+s+str[j];
            }
            else{
                string left, right;
                //else go in any one direction and find the largest
                left = LPSNaiveUtil(str, i+1, j);
                right = LPSNaiveUtil(str, i, j-1);
                if(left.length()>right.length())
                    s = left;
                else
                    s = right;
            }
            return s;
        }

        string LPSNaive(string x){
            return LPSNaiveUtil(X, 0, X.length-1);
        }
};

int main(){
    string X = "GEEKSFORGEEKS";
    Solution obj;
    cout<<obj.LPSNaive(X);
    return 0;
}