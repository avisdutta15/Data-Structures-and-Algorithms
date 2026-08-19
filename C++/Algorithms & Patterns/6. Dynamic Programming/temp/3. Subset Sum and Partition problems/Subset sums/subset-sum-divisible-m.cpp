#include <bits/stdc++.h>
using namespace std;

/*
    Given a set of non-negative distinct integers, and a value m, determine 
    if there is a subset of the given set with sum divisible by m.

    Input : arr[] = {3, 1, 7, 5};
        m = 6;
    Output : YES

    Input : arr[] = {1, 6};
            m = 5;
    Output : NO

    Steps:
    1. Take modulo of each number in the array with 'm'. Now array becomes of remainders.
    2. Now use the simple SUBSET SUM PROBLEM sol
    This solution works because taking modulo of each array element ensures that the sum now won't be greater than 'm'. 
    We have remove all extra m's by taking modulo.

*/


class Solution{
    bool subsetSum(vector<int> A, int totalSum){
        int n = A.size();
        bool lookup[n+1][sum+1] = {false};

        for(int i=0; i<=n; i++){
            lookup[i][0] = true;
        }
        for(int sum=1; sum<=totalSum; sum++){
            lookup[0][sum] = false;
        }

        for(int i=1; i<=n; i++){
            for(int sum=1; sum<=totalSum; sum++){
                if(A[i-1]>sum)
                    lookup[i][sum] = lookup[i-1][sum];
                else{
                    bool include = lookup[i][sum-A[i-1]];
                    bool exclude = lookup[i-1][sum-1];
                    lookup[i][sum] = include || exclude;
                }
            }
        }
        return lookup[n][sum];
    }
    public:
        bool subsetWithSumDivisibleByM(vector<int> A, int m){
            int vector<int> B;
            for(int i: A)
                B.push_back(A[i]%m);

            return subsetSum(B, m);
        }
};

int main(){

    vector<int> A= {3, 1, 7, 5};
    int m = 6;

    Solution obj;
    cout<<obj.subsetWithSumDivisibleByM(A, m);

    return 0;
}