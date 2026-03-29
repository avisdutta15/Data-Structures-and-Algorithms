#include <bits/stdc++.h>
using namespace std;

/*
    Given an array arr[] of size n, the task is to divide it into two sets S1 and S2 such 
    that the absolute difference between their sums is minimum. 
    If there is a set S with n elements, then if we assume Subset1 has m elements, Subset2 
    must have n-m elements and the value of abs(sum(Subset1) – sum(Subset2)) should be minimum.

    Example: 
    Input: arr = [1, 6, 11, 5]
    Output: 1
    Explanation: S1 = [1, 5, 6], sum = 12,  S2 = [11], sum = 11,  Absolute Difference (12 – 11) = 1

    Input: arr = [1, 5, 11, 5]
    Output: 0
    Explanation: S1 = [1, 5, 5], sum = 11, S2 = [11], sum = 11, Absolute Difference (11 – 11) = 0

    Approach:
        It is similar to subset sum.
        We need to check if one subset sum is possible or not. Other subset sum :subset2sum = totalSum - subset1sum.
        Then find the minimum. i.e. min(subset2sum - subset1sum)
                                =   min(totalSum - subset1sum - subset1sum) 
*/

class Solution{
    int minimumSumPartitionRecursive(vector<int> &A, int N, int sum, int &totalSum){
        if(N==0){
            int subset1Sum = sum;
            int subset2Sum = totalSum - subset1Sum;
            return abs(subset2Sum-subset1Sum);
        }

        int include = INT_MAX, exclude = INT_MAX;
        include = minimumSumPartitionRecursive(A, N-1, sum + A[N-1], totalSum);
        exclude = minimumSumPartitionRecursive(A, N-1, sum, totalSum);
        return min(include, exclude);
    }

    int minimumSumPartitionTopDown(vector<int> &A, int N, int sum, int &totalSum, unordered_map<string, int> &lookup){
        if(N==0){
            int subset1Sum = sum;
            int subset2Sum = totalSum - subset1Sum;
            return abs(subset2Sum-subset1Sum);
        }

        string key = to_string(N) + " " + to_string(sum);
        if(lookup.find(key) != lookup.end())
            return lookup[key];
        
        int include = INT_MAX, exclude = INT_MAX;
        include = minimumSumPartitionTopDown(A, N-1, sum + A[N-1], totalSum, lookup);
        exclude = minimumSumPartitionTopDown(A, N-1, sum, totalSum, lookup);

        return lookup[key] = min(include, exclude);
    }

    int minimumSumPartitionBottomUp(vector<int> &A, int N, int totalSum){
        vector<vector<bool>> dp(N+1, vector<bool>(totalSum + 1, false));

        for(int n=0; n<=N; n++){
            for(int sum=0; sum<=totalSum; sum++){
                if(n==0 && sum==0)
                    dp[n][sum] = true;
                else if(n==0 && sum!=0)
                    dp[n][sum] = false;
                else{
                    bool include = false, exclude = false;
                    if(A[n-1]<=sum)
                        include = dp[n-1][sum-A[n-1]];
                    exclude = dp[n-1][sum];
                    dp[n][sum] = include || exclude;
                }
            }
        }

        //Now the last row of the dp table denotes if the subset sum 'sum' is possible or not
        //with N elements. We know that subsetsum1 and subsetsum2, both will lie within range
        //0.....totalsum. Now we need to minimize them i.e. min(abs(s2-s1))
        //we know s1 + s2 = totalsum
        //s2 = totalsum - s1
        //then we need min(abs((totalsum-s1) - s1))
        //           = min(abs(totalsum-2s1))
        //collect all the sums that are possible with the array elements of size N into an array called s1.
        //find min(totalSum - 2S1) in that array
        //Optimization: We want to segregate the sum range (0....totalsum) into 2 parts,
        //              with minimum diff. In that case, the value of s1 can at be max (totalSum/2).
        //              So s1 lies between 0....totalsum/2.

        vector<int> s1;
        for(int sum=0; sum<=totalSum; sum++)        //or Optimization (int sum=0; sum<=totalSum/2; sum++)
            if(dp[N][sum] == true)
                s1.push_back(sum);
        
        int minimumSubsetPartitionSum = INT_MAX;
        for(int i: s1)
            minimumSubsetPartitionSum = min(minimumSubsetPartitionSum, abs((totalSum - i) - i));

        return minimumSubsetPartitionSum;
    }
    
    public:
        int minimumSumPartition(vector<int> &A){
            int N = A.size();
            int totalSum = accumulate(A.begin(), A.end(), 0);
            // return minimumSumPartitionRecursive(A, N, 0, totalSum);

            unordered_map<string, int> lookup;
            // return minimumSumPartitionTopDown(A, N, 0, totalSum, lookup);
            return minimumSumPartitionBottomUp(A, N, totalSum);
        }
};


int main(){
    Solution obj;
    vector<int> A = {1, 6, 11, 5};
    cout<<obj.minimumSumPartition(A)<<endl;         //S1 {11} S2 {1, 6, 5} abs(sum(S2)-sum(S1)) = 1

    A = {1, 5, 11, 5};
    cout<<obj.minimumSumPartition(A)<<endl;         //S1 {11} S2 {1, 5, 5} abs(sum(S2)-sum(S1)) = 0 

    return 0;    
}