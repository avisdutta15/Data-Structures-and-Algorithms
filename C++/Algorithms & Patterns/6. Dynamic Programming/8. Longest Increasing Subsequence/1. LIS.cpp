#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    -----------------
    The Longest Increasing Subsequence (LIS) problem is to find the length of the longest subsequence of a
    given sequence such that all elements of the subsequence are sorted in increasing order.

    Input:  [10, 22, 9, 33, 21, 50, 41, 60, 80]
    Output: [10, 22, 33, 50, 60, 80]
         OR [10, 22, 33, 41, 60, 80] or any other LIS of same length.
    Length = 6

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE (Include/Exclude with prev tracking)
    ════════════════════════════════════════════════════════════════════════

    f(i, prevIndex) = length of LIS starting from index i, where prevIndex is the
                      index of the last element included in the subsequence.

    At each element A[i], we have 2 choices:
        - Include A[i]: only if A[i] > A[prevIndex] (maintains increasing order)
                        then LIS = 1 + f(i+1, i)
        - Exclude A[i]: skip it, move to i+1
                        then LIS = f(i+1, prevIndex)

    Base case:
        if i == N: return 0  (no more elements to consider)

    Answer: f(0, -1)  where -1 means no previous element chosen yet

    States: (i, prevIndex)
        i ranges from 0 to N
        prevIndex ranges from -1 to N-1
    For memoization, shift prevIndex by +1 so it ranges from 0 to N.
    Memo dimensions: (N+1) x (N+1)

    ════════════════════════════════════════════════════════════════════════
    BOTTOM-UP (Classic O(N²) DP)
    ════════════════════════════════════════════════════════════════════════

    dp[i] = length of LIS ending at index i

    For each i, look at all j < i where A[j] < A[i]:
        dp[i] = max(dp[j] + 1) for all valid j

    Base: dp[i] = 1 for all i (every element is a LIS of length 1 by itself)

    Answer: max(dp[0..N-1])

    This is a different (but equivalent) way of thinking about LIS.
    Instead of include/exclude from left to right, it asks:
    "What's the longest increasing subsequence that ENDS at i?"

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    private:

        // ══════════════════════════════════════════════════════════════════
        // Approach 1: Recursive (Include/Exclude) — O(2^N)
        // ══════════════════════════════════════════════════════════════════

        // i = current index, prevIndex = index of last included element (-1 if none)
        int LISRecursive(vector<int> &A, int i, int prevIndex, int N){
            // Base case: no more elements to consider
            if(i == N)
                return 0;

            // Exclude A[i]: skip it, move to next element
            int exclude = LISRecursive(A, i+1, prevIndex, N);

            // Include A[i]: only if it's greater than the previously included element
            int include = 0;
            if(prevIndex == -1 || A[i] > A[prevIndex])
                include = 1 + LISRecursive(A, i+1, i, N);   // make i as the prevIndex for i+1

            return max(include, exclude);
        }

        // ══════════════════════════════════════════════════════════════════
        // Approach 2: Top-Down Memoized — O(N²)
        // ══════════════════════════════════════════════════════════════════

        // States: (i, prevIndex). prevIndex shifted by +1 for indexing.
        // memo[i][prevIndex+1] = LIS length starting from index i with given prev
        int LISTopDown(vector<int> &A, int i, int prevIndex, int N, vector<vector<int>> &memo){
            // Base case: no more elements
            if(i == N)
                return 0;

            // Check memo: prevIndex shifted by +1 (so -1 maps to 0)
            if(memo[i][prevIndex + 1] != -1)
                return memo[i][prevIndex + 1];

            // Exclude A[i]
            int exclude = LISTopDown(A, i+1, prevIndex, N, memo);

            // Include A[i] if it maintains increasing order
            int include = 0;
            if(prevIndex == -1 || A[i] > A[prevIndex])
                include = 1 + LISTopDown(A, i+1, i, N, memo);   // make i as the prevIndex for i+1

            // Cache and return
            memo[i][prevIndex + 1] = max(include, exclude);
            return memo[i][prevIndex + 1];
        }

        // ══════════════════════════════════════════════════════════════════
        // Approach 3: Bottom-Up — O(N²)
        // ══════════════════════════════════════════════════════════════════

        // dp[i] = length of LIS ending at index i
        // For each i, check all j < i: if A[j] < A[i], then dp[i] = max(dp[i], dp[j] + 1)
        int LISBottomUp(vector<int> &A, int N){
            // Every element is a LIS of length 1 by itself
            vector<int> dp(N, 1);

            for(int i = 1; i < N; i++){
                // Check all previous elements
                for(int j = 0; j < i; j++){
                    // If A[j] < A[i], we can extend the LIS ending at j by including A[i]
                    if(A[j] < A[i]){
                        dp[i] = max(dp[i], dp[j] + 1);
                    }
                }
            }

            // Answer: maximum value in dp[], since LIS could end at any index
            return *max_element(dp.begin(), dp.end());
        }

        // ══════════════════════════════════════════════════════════════════
        // Bonus: Print LIS (Bottom-Up with path tracking)
        // ══════════════════════════════════════════════════════════════════

        // Instead of just storing length, store the actual subsequence ending at each index
        int printLIS(vector<int> &A, int N){
            // LIS[i] = the longest increasing subsequence ending at A[i]
            vector<vector<int>> LIS(N);
            LIS[0].push_back(A[0]);

            // For each element, find the longest LIS among previous elements
            // that it can extend
            for(int i = 1; i < N; i++){
                for(int j = 0; j < i; j++){
                    // A[i] can extend LIS ending at j if A[i] > A[j]
                    if(A[i] > A[j]){
                        // Pick the longest such LIS
                        if(LIS[j].size() > LIS[i].size())
                            LIS[i] = LIS[j];
                    }
                }
                // Append A[i] to form LIS ending at i
                LIS[i].push_back(A[i]);
            }

            // Find the index with the longest LIS
            int maxLISIndex = 0;
            for(int i = 1; i < N; i++){
                if(LIS[i].size() > LIS[maxLISIndex].size())
                    maxLISIndex = i;
            }

            // Print the LIS
            vector<int> ans = LIS[maxLISIndex];
            for(int i : ans)
                cout << i << " ";
            cout << endl;

            return ans.size();
        }

    public:
        int longestIncreasingSubsequence(vector<int> &A){
            int N = A.size();

            // Approach 1: Recursive
            // return LISRecursive(A, 0, -1, N);

            // Approach 2: Top-Down Memoized
            // memo[i][prevIndex+1], dimensions (N+1) x (N+1), initialized to -1
            // vector<vector<int>> memo(N, vector<int>(N+1, -1));
            // return LISTopDown(A, 0, -1, N, memo);

            // Approach 3: Bottom-Up
            return LISBottomUp(A, N);
        }
};

int main(){
    Solution obj;

    vector<int> A1 = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    cout << "LIS length: " << obj.longestIncreasingSubsequence(A1) << endl;  // 6

    vector<int> A2 = {3, 1, 5, 2, 6, 4, 9};
    cout << "LIS length: " << obj.longestIncreasingSubsequence(A2) << endl;  // 4

    vector<int> A3 = {5, 4, 3, 2, 1};
    cout << "LIS length: " << obj.longestIncreasingSubsequence(A3) << endl;  // 1 (decreasing)

    vector<int> A4 = {1, 2, 3, 4, 5};
    cout << "LIS length: " << obj.longestIncreasingSubsequence(A4) << endl;  // 5 (already sorted)

    return 0;
}
