#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Number of Longest Increasing Subsequences (LeetCode 673)
    ──────────────────────────────────────────────────────────────────

    Given an integer array nums, return the number of longest increasing subsequences.

    Examples:
    ---------
    Input:  [1, 3, 5, 4, 7]
    Output: 2
    Explanation: The two longest increasing subsequences are [1, 3, 5, 7] and [1, 3, 4, 7].

    Input:  [2, 2, 2, 2, 2]
    Output: 5
    Explanation: Each element alone is a LIS of length 1.

    Input:  [1, 2, 4, 3, 5, 4, 7, 2]
    Output: 3
    Explanation: LIS length = 5. The three LIS are:
                 [1, 2, 4, 5, 7], [1, 2, 3, 5, 7], [1, 2, 3, 4, 7]

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT
    ════════════════════════════════════════════════════════════════════════

    This builds on top of the standard LIS problem.

    In standard LIS bottom-up:
        dp[i] = length of LIS ending at index i

    For counting, we add:
        count[i] = number of LIS of length dp[i] that end at index i

    When we find that dp[j] + 1 == dp[i] for some j < i with A[j] < A[i]:
        - If dp[j] + 1 > dp[i]:  found a LONGER LIS ending at i
          → update dp[i], reset count[i] = count[j]
        - If dp[j] + 1 == dp[i]: found ANOTHER LIS of the same length
          → add count[j] to count[i]

    Final answer: sum of count[i] for all i where dp[i] == maxLIS

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE
    ════════════════════════════════════════════════════════════════════════

    Recursive (include/exclude with prev tracking):
        f(i, prevIndex) returns {length, count} of LIS starting from index i

        Base: i == N → {0, 1}

        Exclude: {exLen, exCnt} = f(i+1, prevIndex)
        Include (if A[i] > A[prevIndex]):
                {inLen, inCnt} = {1 + f(i+1, i).length, f(i+1, i).count}

        Merge:
            if inLen > exLen:  return {inLen, inCnt}
            if exLen > inLen:  return {exLen, exCnt}
            if equal:          return {inLen, inCnt + exCnt}

    Bottom-Up (classic O(N^2)):
        dp[i]    = length of LIS ending at i
        count[i] = number of LIS of that length ending at i

        For each j < i where A[j] < A[i]:
            if dp[j] + 1 > dp[i]:   dp[i] = dp[j]+1, count[i] = count[j]
            if dp[j] + 1 == dp[i]:  count[i] += count[j]

        Answer: sum of count[i] where dp[i] == max(dp)

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    private:

        // ══════════════════════════════════════════════════════════════════
        // Approach 1: Recursive — O(2^N)
        // ══════════════════════════════════════════════════════════════════

        // Returns {LIS length, count of LIS} starting from index i
        pair<int,int> numberOfLISRecursive(vector<int> &A, int i, int prevIndex, int N){
            // Base case: no more elements — length 0, but 1 way (empty choice)
            if(i == N)
                return {0, 1};

            // Exclude A[i]: skip it
            auto [exLen, exCnt] = numberOfLISRecursive(A, i+1, prevIndex, N);

            // Include A[i]: only if it maintains increasing order
            int inLen = 0, inCnt = 0;
            if(prevIndex == -1 || A[i] > A[prevIndex]){
                auto [subLen, subCnt] = numberOfLISRecursive(A, i+1, i, N);
                inLen = 1 + subLen;
                inCnt = subCnt;
            }

            // Merge: pick the longer one, or add counts if equal
            if(inLen > exLen)
                return {inLen, inCnt};
            else if(exLen > inLen)
                return {exLen, exCnt};
            else
                return {inLen, inCnt + exCnt};
        }

        // ══════════════════════════════════════════════════════════════════
        // Approach 2: Top-Down Memoized — O(N^2)
        // ══════════════════════════════════════════════════════════════════

        // memo[i][prevIndex+1] = {LIS length, count}
        // prevIndex shifted by +1 so -1 maps to index 0
        pair<int,int> numberOfLISTopDown(vector<int> &A, int i, int prevIndex, int N,
                                          vector<vector<pair<int,int>>> &memo){
            if(i == N)
                return {0, 1};

            // Check memo
            if(memo[i][prevIndex + 1].first != -1)
                return memo[i][prevIndex + 1];

            // Exclude A[i]
            auto [exLen, exCnt] = numberOfLISTopDown(A, i+1, prevIndex, N, memo);

            // Include A[i] if valid
            int inLen = 0, inCnt = 0;
            if(prevIndex == -1 || A[i] > A[prevIndex]){
                auto [subLen, subCnt] = numberOfLISTopDown(A, i+1, i, N, memo);
                inLen = 1 + subLen;
                inCnt = subCnt;
            }

            // Merge
            pair<int,int> result;
            if(inLen > exLen)
                result = {inLen, inCnt};
            else if(exLen > inLen)
                result = {exLen, exCnt};
            else
                result = {inLen, inCnt + exCnt};

            memo[i][prevIndex + 1] = result;
            return result;
        }

        // ══════════════════════════════════════════════════════════════════
        // Approach 3: Bottom-Up — O(N^2)
        // ══════════════════════════════════════════════════════════════════

        // dp[i]    = length of LIS ending at index i
        // count[i] = number of LIS of length dp[i] ending at index i
        int numberOfLISBottomUp(vector<int> &A, int N){
            // Every element is a LIS of length 1, with 1 way
            vector<int> dp(N, 1);
            vector<int> count(N, 1);

            for(int i = 1; i < N; i++){
                for(int j = 0; j < i; j++){
                    // A[j] < A[i]: we can extend the LIS ending at j by including A[i]
                    if(A[j] < A[i]){
                        if(dp[j] + 1 > dp[i]){
                            // Found a LONGER LIS ending at i
                            dp[i] = dp[j] + 1;
                            // Reset count: all LIS of this new length come from j
                            count[i] = count[j];
                        }
                        else if(dp[j] + 1 == dp[i]){
                            // Found ANOTHER way to form LIS of same length ending at i
                            count[i] += count[j];
                        }
                    }
                }
            }

            // Find the maximum LIS length
            int maxLIS = *max_element(dp.begin(), dp.end());

            // Sum counts of all indices where dp[i] == maxLIS
            int totalCount = 0;
            for(int i = 0; i < N; i++){
                if(dp[i] == maxLIS)
                    totalCount += count[i];
            }

            return totalCount;
        }

    public:
        int numberOfLIS(vector<int> &A){
            int N = A.size();
            if(N == 0) return 0;

            // Approach 1: Recursive
            // auto [len, cnt] = numberOfLISRecursive(A, 0, -1, N);
            // return cnt;

            // Approach 2: Top-Down
            // vector<vector<pair<int,int>>> memo(N, vector<pair<int,int>>(N+1, {-1, -1}));
            // auto [len, cnt] = numberOfLISTopDown(A, 0, -1, N, memo);
            // return cnt;

            // Approach 3: Bottom-Up
            return numberOfLISBottomUp(A, N);
        }
};

int main(){
    Solution obj;

    vector<int> A1 = {1, 3, 5, 4, 7};
    cout << "Number of LIS: " << obj.numberOfLIS(A1) << endl;  // 2: [1,3,5,7] and [1,3,4,7]

    vector<int> A2 = {2, 2, 2, 2, 2};
    cout << "Number of LIS: " << obj.numberOfLIS(A2) << endl;  // 5: each element alone

    vector<int> A3 = {1, 2, 4, 3, 5, 4, 7, 2};
    cout << "Number of LIS: " << obj.numberOfLIS(A3) << endl;  // 3

    vector<int> A4 = {1, 2, 3};
    cout << "Number of LIS: " << obj.numberOfLIS(A4) << endl;  // 1: only [1,2,3]

    vector<int> A5 = {3, 2, 1};
    cout << "Number of LIS: " << obj.numberOfLIS(A5) << endl;  // 3: [3], [2], [1] each is LIS of length 1

    return 0;
}
