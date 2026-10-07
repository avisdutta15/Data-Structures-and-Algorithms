#include <bits/stdc++.h>
using namespace std;

/*
    https://www.youtube.com/watch?v=-GtpxG6l_Mc
    
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
    // Recursive: try all ways to partition elements into S1 (accumulated in 'sum') and S2 (the rest)
    // At each element, either include it in S1 or exclude it (goes to S2)
    int minimumSumPartitionRecursive(vector<int> &A, int N, int sum, int &totalSum){
        // Base case: all decisions made — compute the difference
        // S1 got 'sum', S2 gets whatever is left (totalSum - sum)
        if(N==0){
            int subset1Sum = sum;
            int subset2Sum = totalSum - subset1Sum;
            return abs(subset2Sum-subset1Sum);
        }

        int include = INT_MAX, exclude = INT_MAX;
        // Include A[N-1] in S1: add its value to running sum
        include = minimumSumPartitionRecursive(A, N-1, sum + A[N-1], totalSum);
        // Exclude A[N-1] from S1: it goes to S2 implicitly
        exclude = minimumSumPartitionRecursive(A, N-1, sum, totalSum);
        // Return the partition that gives minimum difference
        return min(include, exclude);
    }

    // Top-Down with 2D vector: same as recursive but caches results in memo[N][sum]
    // 2 changing parameters → 2D vector memo[N+1][totalSum+1]
    //   - Row = number of elements considered (0 to N)
    //   - Col = running sum accumulated in S1 (0 to totalSum)
    // Values: -1 = not computed, otherwise stores the minimum difference
    // Advantage over hashmap: direct O(1) indexing, no string allocation overhead.
    int minimumSumPartitionTopDown(vector<int> &A, int N, int sum, int &totalSum, vector<vector<int>> &memo){
        // Base case: all decisions made, compute |S2 - S1|
        if(N==0){
            int subset1Sum = sum;
            int subset2Sum = totalSum - subset1Sum;
            return abs(subset2Sum-subset1Sum);
        }

        // Check memo: -1 means not computed yet
        if(memo[N][sum] != -1)
            return memo[N][sum];
        
        int include = INT_MAX, exclude = INT_MAX;
        // Include A[N-1] in S1
        include = minimumSumPartitionTopDown(A, N-1, sum + A[N-1], totalSum, memo);
        // Exclude A[N-1] from S1
        exclude = minimumSumPartitionTopDown(A, N-1, sum, totalSum, memo);

        // Cache and return the minimum difference
        return memo[N][sum] = min(include, exclude);
    }

    // Bottom-Up: reuses the subset sum DP table
    // dp[n][sum] = can we form 'sum' using the first 'n' elements?
    // After building the table, scan the last row to find which S1 sums are achievable,
    // then pick the one that minimizes |S2 - S1| = |totalSum - 2*S1|
    int minimumSumPartitionBottomUp(vector<int> &A, int N, int totalSum){
        // Standard subset sum DP table
        vector<vector<bool>> dp(N+1, vector<bool>(totalSum + 1, false));

        for(int n=0; n<=N; n++){
            for(int sum=0; sum<=totalSum; sum++){
                // Base case 1: empty subset has sum 0
                if(n==0 && sum==0)
                    dp[n][sum] = true;
                // Base case 2: no elements, can't form positive sum
                else if(n==0 && sum!=0)
                    dp[n][sum] = false;
                else{
                    bool include = false, exclude = false;
                    // Include A[n-1]: check if (sum - A[n-1]) was achievable with n-1 elements
                    if(A[n-1]<=sum)
                        include = dp[n-1][sum-A[n-1]];
                    // Exclude A[n-1]: check if sum was already achievable with n-1 elements
                    exclude = dp[n-1][sum];
                    dp[n][sum] = include || exclude;
                }
            }
        }

        // Now dp[N][sum] tells us if 'sum' is achievable as S1 using all N elements.
        // S2 = totalSum - S1, so diff = |totalSum - 2*S1|
        //
        // We want to minimize |totalSum - 2*S1|.
        // Since totalSum - 2*S1 decreases as S1 increases, the minimum difference
        // occurs when S1 is as close to totalSum/2 as possible.
        //
        // Why S1 can be at most totalSum/2:
        //   If S1 > totalSum/2, then S2 < totalSum/2, meaning S2 < S1.
        //   But that's just the mirror case — swapping S1 and S2 gives the same |diff|.
        //   So we only need to check S1 in [0, totalSum/2]. For every S1 > totalSum/2,
        //   there's an equivalent partition with S1' = totalSum - S1 <= totalSum/2
        //   that gives the same difference. Checking only [0, totalSum/2] avoids
        //   redundant symmetric pairs and finds the answer faster.
        vector<int> s1;
        for(int sum=0; sum<=totalSum/2; sum++)
            if(dp[N][sum] == true)
                s1.push_back(sum);
        
        // Find the achievable S1 that minimizes |totalSum - 2*S1|
        int minimumSubsetPartitionSum = INT_MAX;
        for(int i: s1){
            int subset1Sum = i;
            int subset2Sum = totalSum - i;
            minimumSubsetPartitionSum = min(minimumSubsetPartitionSum, abs(subset2Sum - subset1Sum));
        }            

        return minimumSubsetPartitionSum;
    }
    
    public:
        int minimumSumPartition(vector<int> &A){
            int N = A.size();
            int totalSum = accumulate(A.begin(), A.end(), 0);
            // return minimumSumPartitionRecursive(A, N, 0, totalSum);

            // vector<vector<int>> memo(N+1, vector<int>(totalSum+1, -1));
            // return minimumSumPartitionTopDown(A, N, 0, totalSum, memo);
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