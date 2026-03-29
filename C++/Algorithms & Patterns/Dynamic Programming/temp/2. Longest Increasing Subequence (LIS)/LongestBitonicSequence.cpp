#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    -----------------
    Given an array arr[0 … n-1] containing n positive integers, a subsequence of arr[] is called 
    Bitonic if it is first increasing, then decreasing. Write a function that takes an array as 
    argument and returns the length of the longest bitonic subsequence.

    Approach:
        Create 2 arrays LIS(longest increasing subsequence) and LDS(longest decreasing subsequence).
        They will hold the LIS and LDS of A[].

        Now the length of Longest Bitonic Sequence is max(LIS[i]+LDS[i]-1)

    Example:
        A =   {1, 11, 2, 10, 4, 5, 2, 1}
        LIS = {1, 2,  2, 3,  3, 4, 2, 1}
        LDS = {1, 5,  2, 4,  3, 3, 2, 1} //fill it from back with same update formula
        LBS = LIS[i] + LDS[i] - 1
              {1, 6,  3, 6,  5, 6, 3, 1}
    
    Time Complexity: O(n2)
*/


class Solution
{
    public:
        int lenOfLongestBitonicSeq(vector<int> A){
            if(A.size()==0)
                return 0;
            
            //Create 2 arrays lis(longest increasing subsequence) and lds(longest decreasing subsequence)
            //initialize them with 1
            vector<int> lps(A.size(), 1); 
            vector<int> lds(A.size(), 1);

            lps[0] = 1;
            for(int i=1; i<A.size(); i++){
                for(int j=0; j<i; j++){
                    if(A[i]>A[j]){
                        if(lps[j] + 1 > lps[i])
                            lps[i] = lps[j] + 1;
                    }
                }
            }

            lds[A.size()-1] = 1;
            for(int i=A.size()-2; i>=0; i--){
                for(int j=A.size()-1; j>i; j--){
                    if(A[i]>A[j]){
                        if(lds[j] + 1 > lds[i])
                            lds[i] = lds[j] + 1;
                    }
                }
            }

            //Return the maximum of lps[i] + lds[i] - 1 
            int maxLen = lps[0] + lds[0] - 1;
            for(int i=0; i<A.size(); i++)
                maxLen = max(maxLen, lps[i]+lds[i]-1);

            return maxLen; 
        }
};

int main(){
    Solution obj;
    vector<int> A = {1, 11, 2, 10, 4, 5, 2, 1};

    cout<<obj.lenOfLongestBitonicSeq(A);
    return 0;
}