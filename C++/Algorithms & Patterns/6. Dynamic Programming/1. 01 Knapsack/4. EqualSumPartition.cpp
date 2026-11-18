#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Equal Sum Partition / Partition Equal Subset Sum (LeetCode 416)
    ────────────────────────────────────────────────────────────────────────

    Problem Statement:
    ------------------
    Given a non-empty array nums containing only positive integers, find if the
    array can be partitioned into two subsets such that the sum of elements in
    both subsets is equal.

    Examples:
    ---------
    Input:  nums = [1, 5, 11, 5]
    Output: true
    Explanation: [1, 5, 5] and [11] both sum to 11.

    Input:  nums = [1, 2, 3, 5]
    Output: false

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: Reduction to Subset Sum
    ════════════════════════════════════════════════════════════════════════

    If we partition array into two subsets S1 and S2 with equal sum:
        sum(S1) = sum(S2) = totalSum / 2

    So the problem becomes:
        "Does there exist a subset with sum = totalSum / 2?"

    This is exactly the Subset Sum problem!

    Pre-check: If totalSum is ODD, partition is impossible (can't split odd into two equal halves).

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE (same as Subset Sum with target = totalSum/2)
    ════════════════════════════════════════════════════════════════════════

    f(n, s) = can we form sum s using the first n elements?

    Base cases:
        f(0, 0) = true     (empty subset sums to 0)
        f(0, s) = false    (no elements, can't form positive sum)

    Recurrence:
        if A[n-1] <= s:
            f(n, s) = f(n-1, s - A[n-1])  ||  f(n-1, s)
                      (include item n)         (exclude item n)
        else:
            f(n, s) = f(n-1, s)

    Answer: f(N, totalSum/2)

    ════════════════════════════════════════════════════════════════════════
*/


class Solution{
    // ── Recursive: O(2^N) time, O(N) stack space ──
    // Standard subset sum recursion with target = totalSum/2
    bool equalSumPartitionRecursive(vector<int> &A, int N, int sum){
        if(N == 0 && sum ==0)
            return true;    // found a valid subset
        if(N == 0 && sum!=0)
            return false;   // no more elements, can't reach target
        
        bool include = false, exclude = false;
        if(A[N-1]<=sum)
            include = equalSumPartitionRecursive(A, N-1, sum - A[N-1]);
        exclude = equalSumPartitionRecursive(A, N-1, sum);
        return include || exclude;
    }

    // ── Top-Down Memoization: O(N * sum) time and space ──
    // Cache results for each (N, sum) state to avoid recomputation
    bool equalSumPartitionTopDown(vector<int> &A, int N, int sum, unordered_map<string, bool> &lookup){
        if(N == 0 && sum ==0)
            return true; 
        if(N == 0 && sum!=0)
            return false;
        
        string key = to_string(N) + " " + to_string(sum);
        if(lookup.find(key) != lookup.end())
            return lookup[key];

        bool include = false, exclude = false;
        if(A[N-1]<=sum)
            include = equalSumPartitionTopDown(A, N-1, sum - A[N-1], lookup);
        exclude = equalSumPartitionTopDown(A, N-1, sum, lookup);

        lookup[key] = include || exclude;
        
        return lookup[key];
    }

    // ── Bottom-Up: O(N * sum) time and space ──
    // dp[n][w] = can we form sum w using first n elements?
    bool equalSumPartitionBottomUp(vector<int> &A, int N, int sum){
        vector<vector<bool>> dp(N+1, vector<bool>(sum+1, false));

        for(int n=0; n<=N; n++){
            for(int w=0; w<=sum; w++){
                if(n == 0 && w == 0)
                    dp[n][w] = true;    // empty subset sums to 0
                else if(n == 0 && w != 0)
                    dp[n][w] = false;   // no items, can't form positive sum
                else{
                    bool include = false, exclude = false;
                    if(A[n-1] <= w)
                        include = dp[n-1][w-A[n-1]];  // include item n
                    exclude = dp[n-1][w];              // exclude item n
                    dp[n][w] = include || exclude;
                }
            }
        }
        return dp[N][sum];
    }

public:
    bool equalSumPartition(vector<int> A){
        int N = A.size();
        int sum = accumulate(A.begin(), A.end(), 0);

        // If total sum is odd, can't split into two equal halves
        if(sum % 2!=0)
            return false;

        // Reduce to: does a subset with sum = totalSum/2 exist?
        //return equalSumPartitionRecursive(A, N, sum/2);        
        // unordered_map<string, bool> lookup;
        // return equalSumPartitionTopDown(A, N, sum/2, lookup); 
        return equalSumPartitionBottomUp(A, N, sum/2);
    }
};


int main(){
    Solution obj;
    vector<int> A = {1, 5, 11, 5};
    obj.equalSumPartition(A) == true? cout<<"Possible"<<endl : cout<<"Not Possible"<<endl;
}