#include <bits/stdc++.h>
using namespace std;

/*
    Given an array arr[] of size N and a given difference diff, the task is to count 
    the number of partitions that we can perform such that the difference between the 
    sum of the two subsets is equal to the given difference.

    Note: A partition in the array means dividing an array into two parts say S1 and S2 
    such that the union of S1 and S2 is equal to the original array and each element 
    is present in only of the subsets.

    Examples:
    Input: N = 4, arr[] = [5, 2, 6, 4], diff = 3
    Output: 1
    Explanation: We can only have a single partition which is shown below:
    {5, 2} and {6, 4} such that S1 = 7 and S2 = 10 and thus the difference is 3

    Input: N = 5, arr[] = [1, 2, 3, 1, 2], diff = 1
    Output: 5
    Explanation: We can have five partitions which is shown below
    {1, 3, 1} and {2, 2} – S1 = 5, S2 = 4
    {1, 2, 2} and {1, 3} – S1 = 5, S2 = 4
    {3, 2} and {1, 1, 2} – S1 = 5, S2 = 4
    {1, 2, 2} and {1, 3} – S1 = 5, S2 = 4
    {3, 2} and {1, 1, 2} – S1 = 5, S2 = 4

    Approach1:
    Find the subsetsum of 2 subsets. Then at N=0 check if their diff = givenDiff
    
    Approach2:
        We have 2 equations:
            subset1_sum + subset2_sum = total_sum
            subset1_sum - subset2_sum = diff
        ------------------------------------------
        =>  2*subset1_sum = total_sum + diff
        =>    subset1_sum = (total_sum + diff) / 2

    herefore, in this case of array the total number of possible ways depends on the 
    number of possible ways to create a subset having sum S1.

    Therefor ans := count ways to get subset sum = subset1_sum;
*/

class Solution{
        // ── Approach 1: Recursive ──
        // Try all ways to build S1 (accumulated in subset1Sum), S2 is the rest.
        // At N==0, check if |S2 - S1| == diff
        int countSubsetsWithGivenDifferenceRecursive(vector<int> &A, int N, int subset1Sum, int &totalSum, int &diff){
            // Base case: all decisions made — check if this partition has the required diff
            if(N==0){
                int subset2Sum = totalSum - subset1Sum;
                int subsetsumdiff = subset2Sum - subset1Sum;
                if(subsetsumdiff == diff)
                    return 1;   // valid partition found
                return 0;       // doesn't match
            }

            int include = 0, exclude = 0;
            // Include A[N-1] in S1: add its value to running sum
            include = countSubsetsWithGivenDifferenceRecursive(A, N-1, subset1Sum+A[N-1], totalSum, diff);
            // Exclude A[N-1] from S1: it goes to S2 implicitly
            exclude = countSubsetsWithGivenDifferenceRecursive(A, N-1, subset1Sum, totalSum, diff);
            // Total valid partitions = sum of both paths
            return include + exclude;
        }
        
        // ── Approach 1: Top-Down (memoized with hashmap) ──
        // Same as recursive but caches results by (N, subset1Sum)
        int countSubsetsWithGivenDifferenceTopDown(vector<int> &A, int N, int subset1Sum, int &totalSum, int &diff, unordered_map<string, int> &lookup){
            // Base case: all decisions made, check if partition diff matches
            if(N==0){
                int subset2Sum = totalSum - subset1Sum;
                int subsetsumdiff = subset2Sum - subset1Sum;
                if(subsetsumdiff == diff)
                    return 1;
                return 0; 
            }

            // Check if this (N, subset1Sum) subproblem was already solved
            string key = to_string(N) + " " + to_string(subset1Sum);
            if(lookup.find(key) != lookup.end())
                return lookup[key];

            int include = 0, exclude = 0;
            // Include A[N-1] in S1
            include = countSubsetsWithGivenDifferenceTopDown(A, N-1, subset1Sum+A[N-1], totalSum, diff, lookup);
            // Exclude A[N-1] from S1
            exclude = countSubsetsWithGivenDifferenceTopDown(A, N-1, subset1Sum, totalSum, diff, lookup);
            // Cache and return total count
            return lookup[key] = include + exclude;
        }

        // ── Approach 1: Bottom-Up ──
        // Build subset sum count table, then scan last row for partitions with required diff.
        // dp[n][sum] = number of subsets using first n elements that sum to 'sum'
        int countSubsetsWithGivenDifferenceBottomUp(vector<int> &A, int diff, int N, int totalSum){
            vector<vector<int>> dp(N+1, vector<int>(totalSum + 1, 0));

            for(int n=0; n<=N; n++){
                for(int sum=0; sum<=totalSum; sum++){
                    // Base case 1: empty subset has sum 0 — one way (take nothing)
                    if(n==0 && sum==0)
                        dp[n][sum] = 1;
                    // Base case 2: no elements, can't form positive sum — zero ways
                    else if(n==0 && sum!=0)
                        dp[n][sum] = 0;
                    else{
                        int include = 0, exclude = 0;
                        // Include A[n-1]: count subsets where remaining sum was (sum - A[n-1])
                        if(A[n-1]<=sum)
                            include = dp[n-1][sum-A[n-1]];
                        // Exclude A[n-1]: count subsets that already achieved this sum
                        exclude = dp[n-1][sum];
                        dp[n][sum] = include + exclude;
                    }
                }
            }

            // Scan last row: dp[N][sum] = number of ways to form 'sum' as S1 using all N elements
            // For each achievable S1, check if S2 - S1 == diff
            int count = 0;
            for(int sum=0; sum<=totalSum; sum++){
                if(dp[N][sum] != 0){
                    int subset1Sum = sum;
                    int subset2Sum = totalSum - subset1Sum;
                    if(subset2Sum - subset1Sum == diff)
                        count = count + dp[N][subset1Sum];
                }
            }
            return count;
        }

        // ── Approach 2: Reduce to "Count Subsets with Given Sum" ──
        // Math:
        //   S1 + S2 = totalSum
        //   S2 - S1 = diff
        //   Adding: 2*S2 = totalSum + diff  →  S2 = (totalSum + diff) / 2
        //
        // So instead of checking all partitions, just count subsets with sum = (totalSum + diff) / 2.
        // This is exactly the "Count Subsets with Given Sum" problem.
        //
        // Edge cases:
        //   - (totalSum + diff) must be even, otherwise no valid partition exists
        //   - (totalSum + diff) must be >= 0
        int countSubsetsWithGivenDifferenceOptimized(vector<int> &A, int diff, int N, int totalSum){
            // If (totalSum + diff) is odd, can't split evenly — no valid partition
            if((totalSum + diff) % 2 != 0)
                return 0;
            
            int target = (totalSum + diff) / 2;

            // If target is negative, no subset of non-negative numbers can sum to it
            if(target < 0)
                return 0;

            // Now just count subsets with sum = target (same as CountSubsetsWithGivenSum)
            // dp[n][sum] = number of subsets using first n elements that sum to 'sum'
            vector<vector<int>> dp(N+1, vector<int>(target + 1, 0));

            for(int n=0; n<=N; n++){
                for(int sum=0; sum<=target; sum++){
                    // Base case 1: empty subset has sum 0 — one way
                    if(n==0 && sum==0)
                        dp[n][sum] = 1;
                    // Base case 2: no elements, can't form positive sum
                    else if(n==0 && sum!=0)
                        dp[n][sum] = 0;
                    else{
                        int include = 0, exclude = 0;
                        if(A[n-1]<=sum)
                            include = dp[n-1][sum-A[n-1]];
                        exclude = dp[n-1][sum];
                        dp[n][sum] = include + exclude;
                    }
                }
            }

            // Answer: number of subsets that sum to target
            return dp[N][target];
        }
    public:
        int countSubsetsWithGivenDifference(vector<int> &A, int diff){
            int N = A.size();
            int totalSum = accumulate(A.begin(), A.end(), 0);
            int subset1Sum = 0;
            // Approach 1: Recursive
            // return countSubsetsWithGivenDifferenceRecursive(A, N, subset1Sum, totalSum, diff);

            // Approach 1: Top-Down (hashmap)
            // unordered_map<string, int> lookup;
            // return countSubsetsWithGivenDifferenceTopDown(A, N, subset1Sum, totalSum, diff, lookup);

            // Approach 1: Bottom-Up (scan last row for matching diff)
            // return countSubsetsWithGivenDifferenceBottomUp(A, diff, N, totalSum);

            // Approach 2: Reduce to count subsets with sum = (totalSum + diff) / 2
            return countSubsetsWithGivenDifferenceOptimized(A, diff, N, totalSum);
        }
};


int main(){
    Solution obj;
    vector<int> A = {5, 2, 6, 4};
    cout<<obj.countSubsetsWithGivenDifference(A, 3)<<endl;

    A = {1, 2, 3, 1, 2};
    cout<<obj.countSubsetsWithGivenDifference(A, 1)<<endl;
    return 0;
}