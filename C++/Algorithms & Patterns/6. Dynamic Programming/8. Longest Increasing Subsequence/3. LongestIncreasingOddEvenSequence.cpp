#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Longest Increasing Odd Even Subsequence
    ─────────────────────────────────────────────────

    Find the length of the longest increasing subsequence such that
    consecutive elements alternate between odd and even.

    i.e. if A[j] is odd, the next element A[i] must be even (and vice versa),
    AND A[i] > A[j] (increasing).

    Examples:
    ---------
    Input:  [5, 6, 9, 4, 7, 8]
    Output: 3  → e.g. [5, 6, 9] or [5, 8] ... let's check:
            [5(odd), 6(even), 9(odd)] → alternating, increasing → length 3

    Input:  [1, 12, 2, 22, 5, 30, 31, 14, 17, 11]
    Output: 5  → e.g. [1, 12, 5, 30, 31] ... checking:
            [1(o), 12(e), 5?] 5 < 12, not increasing.
            [1(o), 2(e), 5(o), 30(e), 31(o)] → alternating, increasing → length 5

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT
    ════════════════════════════════════════════════════════════════════════

    This is LIS with one extra constraint:
        A[j] < A[i]  AND  A[j] and A[i] have different parity (one odd, one even)

    Trick to check opposite parity:
        odd + even = odd  →  (A[i] + A[j]) % 2 == 1 means they alternate

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE
    ════════════════════════════════════════════════════════════════════════

    Same as LIS, but include condition adds parity check:
        Include A[i] if: A[i] > A[prevIndex]  AND  (A[i] + A[prevIndex]) % 2 == 1

    Recursive:
        f(i, prevIndex) = longest increasing odd-even subsequence from index i

        Base: i == N → return 0

        Exclude: f(i+1, prevIndex)
        Include: if prevIndex == -1 OR (A[i] > A[prevIndex] AND alternating parity)
                 then 1 + f(i+1, i)

        return max(include, exclude)

    Bottom-Up:
        dp[i] = length of longest increasing odd-even subsequence ending at i

        For each j < i:
            if A[j] < A[i] AND (A[i] + A[j]) % 2 == 1:
                dp[i] = max(dp[i], dp[j] + 1)

        Answer: max(dp[0..N-1])

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    private:

        // ══════════════════════════════════════════════════════════════════
        // Approach 1: Recursive — O(2^N)
        // ══════════════════════════════════════════════════════════════════

        // i = current index, prevIndex = index of last included element (-1 if none)
        int LIOESRecursive(vector<int> &A, int i, int prevIndex, int N){
            // Base case: no more elements
            if(i == N)
                return 0;

            // Exclude A[i]
            int exclude = LIOESRecursive(A, i+1, prevIndex, N);

            // Include A[i] if:
            //   - first element (prevIndex == -1), OR
            //   - A[i] > A[prevIndex] AND they have opposite parity
            int include = 0;
            if(prevIndex == -1 || (A[i] > A[prevIndex] && (A[i] + A[prevIndex]) % 2 == 1))
                include = 1 + LIOESRecursive(A, i+1, i, N);

            return max(include, exclude);
        }

        // ══════════════════════════════════════════════════════════════════
        // Approach 2: Top-Down Memoized — O(N²)
        // ══════════════════════════════════════════════════════════════════

        // memo[i][prevIndex+1]: longest odd-even subseq from index i with given prev
        // prevIndex shifted by +1 so -1 maps to index 0
        int LIOESTopDown(vector<int> &A, int i, int prevIndex, int N, vector<vector<int>> &memo){
            if(i == N)
                return 0;

            // Check memo
            if(memo[i][prevIndex + 1] != -1)
                return memo[i][prevIndex + 1];

            // Exclude A[i]
            int exclude = LIOESTopDown(A, i+1, prevIndex, N, memo);

            // Include A[i] if valid (increasing + alternating parity)
            int include = 0;
            if(prevIndex == -1 || (A[i] > A[prevIndex] && (A[i] + A[prevIndex]) % 2 == 1))
                include = 1 + LIOESTopDown(A, i+1, i, N, memo);

            // Cache and return
            memo[i][prevIndex + 1] = max(include, exclude);
            return memo[i][prevIndex + 1];
        }

        // ══════════════════════════════════════════════════════════════════
        // Approach 3: Bottom-Up — O(N²)
        // ══════════════════════════════════════════════════════════════════

        // dp[i] = length of longest increasing odd-even subsequence ending at index i
        int LIOESBottomUp(vector<int> &A, int N){
            // Every element is a valid subsequence of length 1 by itself
            vector<int> dp(N, 1);

            for(int i = 1; i < N; i++){
                for(int j = 0; j < i; j++){
                    // A[j] < A[i]: increasing
                    // (A[i] + A[j]) % 2 == 1: one is odd, one is even (alternating parity)
                    if(A[j] < A[i] && (A[i] + A[j]) % 2 == 1){
                        dp[i] = max(dp[i], dp[j] + 1);
                    }
                }
            }

            // Answer: maximum value in dp[]
            return *max_element(dp.begin(), dp.end());
        }

    public:
        int longestIncreasingOddEvenSubsequence(vector<int> &A){
            int N = A.size();
            if(N == 0) return 0;

            // Approach 1: Recursive
            // return LIOESRecursive(A, 0, -1, N);

            // Approach 2: Top-Down
            // vector<vector<int>> memo(N, vector<int>(N+1, -1));
            // return LIOESTopDown(A, 0, -1, N, memo);

            // Approach 3: Bottom-Up
            return LIOESBottomUp(A, N);
        }
};

int main(){
    Solution obj;

    vector<int> A1 = {5, 6, 9, 4, 7, 8};
    cout << "LIOES length: " << obj.longestIncreasingOddEvenSubsequence(A1) << endl;
    // [5(o), 6(e), 9(o)] → 3

    vector<int> A2 = {1, 12, 2, 22, 5, 30, 31, 14, 17, 11};
    cout << "LIOES length: " << obj.longestIncreasingOddEvenSubsequence(A2) << endl;
    // [1(o), 2(e), 5(o), 30(e), 31(o)] → 5

    vector<int> A3 = {2, 4, 6, 8};
    cout << "LIOES length: " << obj.longestIncreasingOddEvenSubsequence(A3) << endl;
    // All even, no alternating possible → 1

    vector<int> A4 = {1, 2, 3, 4, 5};
    cout << "LIOES length: " << obj.longestIncreasingOddEvenSubsequence(A4) << endl;
    // [1(o), 2(e), 3(o), 4(e), 5(o)] → 5

    return 0;
}
