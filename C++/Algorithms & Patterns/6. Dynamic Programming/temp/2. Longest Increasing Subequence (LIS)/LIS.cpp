#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    -----------------
    The longest Increasing Subsequence (LIS) problem is to find the length of the longest subsequence of a 
    given sequence such that all elements of the subsequence are sorted in increasing order.

    Input:  [10, 22, 9, 33, 21, 50, 41, 60, 80]
    Output: [10, 22, 33, 50, 60, 80] 
         OR [10 22 33 41 60 80] or any other LIS of same length.

    Approach:
        Recurrence Relation - 
            L[0] = {arr[0]}
            L[i] = {Max(L[j])} + arr[i] 
                   where j < i and arr[j] < arr[i] and if there is no such j then L[i] = arr[i]
*/

class Solution{
    private:
        int LISNaiveUtil(vector<int>A, int prev, int i){
            if(i==A.size())
                return 0;
            
            int include = 0;
            if(A[i]>prev)
                include = 1 + LISNaiveUtil(A, A[i], i+1);
            int exclude = LISNaiveUtil(A, prev, i+1);
            return max(include, exclude);
        }
    public:
        int LISNaive(vector<int>A){
            return LISNaiveUtil(A, INT_MIN, 0);
        }

        int LIS(vector<int> A){
            
            //LIS[] is initialized to 1 because the LIS of a single element is 1
            int LIS[A.size()] = {1};
            int maxLIS = -1;
            
            for(int i=0; i<A.size(); i++){
                for(int j=0; j<=i-1; j++){
                    if(A[i]>=A[j]){
                        if(LIS[j]+1>=LIS[i]){
                            LIS[i] = LIS[j]+1;
                            maxLIS = max(maxLIS, LIS[i]);
                        }
                    }
                }
            }

            return maxLIS;
        }

        int printLIS(vector<int> A){
            vector<vector<int>>LIS;
            //LIS[0] denotes the longest increasing subsequence ending with A[0]
            LIS[0].push_back(A[0]);
            
            //start from 2nd element
            for(int i=1; i<A.size(); i++){
                for(int j=0; j<=i-1; j++){
                    if(A[i]>A[j]){
                        if(LIS[j].size() > LIS[i].size())
                            LIS[i] = LIS[j];
                    }
                }
                //include A[i]
                LIS[i].push_back(A[i]);
            }

            int maxLISIndex = 0;
            int maxLIS = 0;
            for(int i=0; i<LIS.size(); i++){
                if(LIS[maxLISIndex].size() < LIS[i].size()){
                    maxLIS = LIS[i].size();
                    maxLISIndex = i;
                }
            }

            vector<int> ans = LIS[maxLISIndex];
            for(int i:ans){
                cout<<i<<" ";
            }
            return maxLIS;
        }

};

int main(){
    vector<int> A = {3, 1, 5, 2, 6, 4, 9};
    Solution obj;
    //cout<<obj.LISNaive(A);
    //cout<<obj.LIS(A);
    cout<<obj.printLIS(A);
    
    return 0;
}