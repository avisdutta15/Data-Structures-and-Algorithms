#include<bits/stdc++.h>
using namespace std;

/*
    Given an array arr[] of non-negative integers and a value sum, the task is to check 
    if there is a subset of the given array whose sum is equal to the given sum. 

    Examples: 
    Input: arr[] = {3, 34, 4, 12, 5, 2}, sum = 9
    Output: True
    Explanation: There is a subset (4, 5) with sum 9.

    Input: arr[] = {3, 34, 4, 12, 5, 2}, sum = 30
    Output: False
    Explanation: There is no subset that add up to 30.

Approach:

    In the base case why did we consider only
    if(N==0 && targetSum == 0)
        return true;    //empty subset if N = 0 and sum = 0
    if(N == 0 && targetSum!=0)
        return false;
    
    and not 
        if(targetSum == 0)
            return 1;

    This is because if we have an array like {1, -1, 24} and target = 24.
    Then there are 2 subsets possible (1, -1, 24) and (24).

    If your base case is if (targetSum == 0) return 1:
        At f(3, 24), you include A[2] = 24, which gives f(2, 0). 
        Now targetSum == 0, so you immediately return 1 and stop recursing. 
        You never explore whether including A[1] = -1 and A[0] = 1 (which sum to 0) could also work alongside 24. 
        So you find {24} but miss {1, -1, 24}.

    The problem is you're saying "sum is 0, I'm done" before you've given the remaining elements a chance 
    to form a zero-sum group that could also be part of a valid subset.

    By only checking at N == 0 (when you've made a decision about every element), you force the recursion 
    to go all the way down the tree:

    i.e. at 
                     f(3, 24)
              inc A[2]/   \ excl A[2]
                f(2, 0)   f(2, 24)

    Now here if we return f(2,0) == returns 1 then we would not get the other subsets where 24 is 
    included but the sum of other elements are also included and their sum is 0.

    Draw a complete recursion tree to understand.

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE
    ════════════════════════════════════════════════════════════════════════

    dp[n][s] = can we form sum s using the first n elements?

    Base cases:
        f(0, 0) = true     (empty subset has sum 0)
        f(0, s) = false    (no elements, can't form positive sum)

    Recurrence:
        if A[n-1] <= s:
            include = f(n-1, s - A[n-1])        //(include item n)
            exclude = f(n-1, s)                 //(exclude item n)
            f(n, s) = include || exclude                                 
        else:
            f(n, s) = f(n-1, s)   (can't include, too big)

    Answer: f(N, targetSum)

    States:
    - n: number of items considered so far (0 to N)
    - s: the remaining sum we're trying to achieve (0 to targetSum)

    Why 2D memoization?
    ───────────────────
    The function has TWO changing parameters: N (items remaining) and targetSum.
    Looking at the recursive function f(n, targetSum):
        n ranges from 0 to N (the size of the array). It starts at N and decreases by 1 each call, so you need N + 1 rows.
        targetSum ranges from 0 to targetSum (the original target).  It either stays the same (exclude) or decreases by A[i] (include), so you need targetSum + 1 columns.
    Each unique (N, targetSum) pair defines a unique subproblem.
    So we need a 2D structure indexed by [N][targetSum] to store results.

    Using a hashmap with string key "N targetSum" works but is slow due to
    string creation and hashing. A 2D vector dp[N+1][targetSum+1] is faster
    because both dimensions are bounded integers with direct indexing.

    ════════════════════════════════════════════════════════════════════════      
*/

class Solution{
    // Recursive: try all include/exclude combinations, check if targetSum is reachable
    bool subsetSumRecursive(vector<int> &A, int N, int targetSum){
        // Base case 1: all decisions made and sum is exactly 0 — found a valid subset
        if(N==0 && targetSum == 0)
            return true;    
        // Base case 2: all decisions made but sum isn't 0 — this path doesn't work
        if(N == 0 && targetSum!=0)
            return false;
        
        bool include = false, exclude = false;
        // Include A[N-1]: subtract its value from targetSum, move to N-1
        if(A[N-1]<=targetSum)
            include = subsetSumRecursive(A, N-1, targetSum - A[N-1]);
        // Exclude A[N-1]: targetSum stays the same, move to N-1
        exclude = subsetSumRecursive(A, N-1, targetSum);
        // If either path found a valid subset, return true
        return include || exclude;
    }

    // Top-Down with hashmap: same as recursive but caches results by "N targetSum" key
    bool subsetSumTopDown(vector<int> &A, int N, int targetSum, unordered_map<string, bool> &lookup){
        // Base case 1: all decisions made, sum reached 0 — valid subset exists
        if(N==0 && targetSum == 0)
            return true;
        // Base case 2: all decisions made, sum not 0 — no valid subset on this path
        if(N == 0 && targetSum!=0)
            return false;

        // Check if this (N, targetSum) subproblem was already solved
        string key = to_string(N) + " " + to_string(targetSum);
        if(lookup.find(key)!=lookup.end())
            return lookup[key];

        bool include = false, exclude = false;
        // Include A[N-1] if it doesn't exceed remaining targetSum
        if(A[N-1]<=targetSum)
            include = subsetSumTopDown(A, N-1, targetSum - A[N-1], lookup);

        // Exclude A[N-1]
        exclude = subsetSumTopDown(A, N-1, targetSum, lookup);

        // Cache and return result for this subproblem
        lookup[key] = include || exclude;
        return lookup[key];
    }

    // ── Top-Down with 2D Vector Memoization ──
    // 
    // Why 2D? The recursive function has 2 changing parameters:
    //   1. N (index/number of items considered, ranges from 0 to N)
    //   2. targetSum (remaining sum to form, ranges from 0 to targetSum)
    //
    // Each unique combination (N, targetSum) is a unique subproblem.
    // A 2D vector memo[N+1][targetSum+1] maps directly to these states:
    //   - Row index = how many items are being considered
    //   - Col index = the remaining sum we're trying to form
    //
    // We use -1 = not computed, 0 = false, 1 = true.
    //
    // Advantage over hashmap approach:
    //   - O(1) lookup (direct indexing) vs O(1) amortized but with string
    //     creation overhead and hash collisions.
    //   - No string allocation per subproblem.
    //
    bool subsetSumTopDown2(vector<int> &A, int N, int targetSum, vector<vector<int>> &memo){
        // Base cases
        if(N == 0 && targetSum == 0)
            return true;
        if(N == 0 && targetSum != 0)
            return false;

        // Check memo: -1 means not computed yet
        if(memo[N][targetSum] != -1)
            return memo[N][targetSum];

        bool include = false, exclude = false;

        // Include A[N-1] if it fits
        if(A[N-1] <= targetSum)
            include = subsetSumTopDown2(A, N-1, targetSum - A[N-1], memo);

        // Exclude A[N-1]
        exclude = subsetSumTopDown2(A, N-1, targetSum, memo);

        // Store in memo and return
        memo[N][targetSum] = (include || exclude) ? 1 : 0;
        return memo[N][targetSum];
    }

    // Bottom-Up: fill dp[n][sum] iteratively from base cases
    // dp[n][sum] = can we form 'sum' using the first 'n' elements?
    bool subsetSumBottomDown(vector<int> &A, int N, int targetSum){        
        vector<vector<bool>> dp(N+1, vector<bool>(targetSum+1, false));
        for(int n=0; n<=N; n++){
            for(int sum=0; sum<=targetSum; sum++){
                // Base case 1: empty subset has sum 0
                if(n == 0 && sum == 0)
                    dp[n][sum] = true;
                // Base case 2: no elements left, can't form positive sum
                else if(n == 0 && sum!=0)
                    dp[n][sum] = false;
                else{
                    bool include = false, exclude = false;
                    // Include A[n-1]: check if (sum - A[n-1]) was achievable with n-1 elements
                    if(A[n-1]<=sum){
                        include = dp[n-1][sum-A[n-1]];
                    }
                    // Exclude A[n-1]: check if sum was already achievable with n-1 elements
                    exclude = dp[n-1][sum];
                    // Either path makes this sum achievable
                    dp[n][sum] = include || exclude;
                }
            }
        }

        // Answer: can we form targetSum using all N elements?
        return dp[N][targetSum];
    }

public:    
    int subsetSum(vector<int> &A, int targetSum){
        int N = A.size();
        unordered_map<string, bool> lookup;
        // return subsetSumRecursive(A, N, targetSum);
        // return subsetSumTopDown(A, N, targetSum, lookup);
        return subsetSumBottomDown(A, N, targetSum);
    }
};

int main(){
    Solution obj;
    vector<int> A = {3, 34, 4, 12, 5, 2};
    obj.subsetSum(A, 9)==true?cout<<"Exists"<<endl:cout<<"Not Exists"<<endl;

    A = {3, 34, 4, 12, 5, 2};
    obj.subsetSum(A, 30)==true?cout<<"Exists"<<endl:cout<<"Not Exists"<<endl;
    return 0;
}