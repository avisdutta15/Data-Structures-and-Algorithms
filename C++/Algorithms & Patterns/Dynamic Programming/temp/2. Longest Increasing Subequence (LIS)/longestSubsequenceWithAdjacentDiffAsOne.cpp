#include <bits/stdc++.h>
using namespace std;

/*
    Given an array of n size, the task is to find the longest subsequence such 
    that difference between adjacents is one.

    Examples:
    Input :  arr[] = {10, 9, 4, 5, 4, 8, 6}
    Output :  3
    As longest subsequences with difference 1 are, "10, 9, 8", 
    "4, 5, 4" and "4, 5, 6"

    Approach 1: Same like LIS. For A[i] find A[j] such that j<i and abs(A[j]-A[i]) = 1
    Approach 2: we are just searching for A[i]-1 or A[i]+1. So just keep a hashmap
                Map{element, LIAS_ending_at_that_element}.
                For each A[i] check if A[i]-1 and A[i]+1 exists in the map.
                Refer : longestIncreasingConsequtiveSubsequence

*/

class Solution{
    public:
        int longestConsequtiveSubsequence(vector<int> A){

        }
};

int main(){
    vector<int> A = {10, 9, 4, 5, 4, 8, 6};
    Solution obj;
    obj.longestConsequtiveSubsequence(A);
}