#include <bits/stdc++.h>
using namespace std;

/*
    Given an array of positive numbers, find the maximum sum of a subsequence such that 
    no two numbers in the subsequence should be adjacent in the array.

    Examples: 
    Input: arr[] = {5, 5, 10, 100, 10, 5}
    Output: 110
    Explanation: Pick the subsequence {5, 100, 5}.
    The sum is 110 and no two elements are adjacent. This is the highest possible sum.

    Input: arr[] = {3, 2, 7, 10}
    Output: 13
    Explanation: The subsequence is {3, 10}. This gives the highest possible sum = 13.

    Input: arr[] = {3, 2, 5, 10, 7}
    Output: 15
    Explanation: Pick the subsequence {3, 5, 7}. The sum is 15.
*/

class Solution{
        // Recursive: try all valid subsequences, pick the max sum
        // N = number of elements we're considering (first N elements of A)
        int maxSumSuchThatNo2ElementsAreAdjacentRecursive(vector<int> &A, int N){
            // No elements left to consider, sum is 0
            if(N==0)
                return 0;
            // Only one element, best we can do is take it
            if(N==1)
                return A[N-1];

            int include = INT_MIN, exclude = INT_MIN;

            // Include A[N-1]: add its value, skip adjacent A[N-2] by jumping to N-2
            include = A[N-1] + maxSumSuchThatNo2ElementsAreAdjacentRecursive(A, N-2);
            
            // Exclude A[N-1]: move to N-1 (A[N-2] is still eligible)
            exclude = maxSumSuchThatNo2ElementsAreAdjacentRecursive(A, N-1);        
            return max(include, exclude);
        }

        // Top-Down (memoized): same logic as recursive, but cache results by N
        // Only 1 changing variable (N), so lookup is a 1D map
        int maxSumSuchThatNo2ElementsAreAdjacentTopDown(vector<int> &A, int N, unordered_map<int, int> &lookup){
            if(N==0)
                return 0;
            if(N==1)
                return A[N-1];

            // If we've already solved for this N, return cached result
            if(lookup.find(N) != lookup.end())
                return lookup[N];
            
            int include = INT_MIN, exclude = INT_MIN;

            // Include A[N-1]: add its value, jump to N-2 (skip adjacent)
            include = A[N-1] + maxSumSuchThatNo2ElementsAreAdjacentTopDown(A, N-2, lookup);
            
            // Exclude A[N-1]: move to N-1
            exclude = maxSumSuchThatNo2ElementsAreAdjacentTopDown(A, N-1, lookup);

            // Cache and return the best of include/exclude
            return lookup[N] = max(include, exclude);
        }

        // Bottom-Up: fill dp[] iteratively from base cases up to N
        // dp[n] = max sum using first n elements with no two adjacent
        int maxSumSuchThatNo2ElementsAreAdjacentBottomUp(vector<int> &A, int N){
            vector<int> dp(N+1, 0);
            dp[0] = 0;       // No elements → sum is 0
            dp[1] = A[0];    // One element → take it

            for(int n=2; n<=N; n++){
                // Include A[n-1]: its value + best sum from first n-2 elements
                int include = A[n-1] + dp[n-2];
                // Exclude A[n-1]: best sum from first n-1 elements
                int exclude = dp[n-1];
                // Take the better option
                dp[n] = max(include, exclude);
            }
            return dp[N];  // Answer for all N elements
        }

    public:
        int maxSumSuchThatNo2ElementsAreAdjacent(vector<int> &A){
            int N = A.size();
            // return maxSumSuchThatNo2ElementsAreAdjacentRecursive(A, N);

            // unordered_map<int, int> lookup;
            // return maxSumSuchThatNo2ElementsAreAdjacentTopDown(A, N, lookup);

            return maxSumSuchThatNo2ElementsAreAdjacentBottomUp(A, N);
        }
};


int main(){
    Solution obj;
    vector<int> A = {5, 5, 10, 100, 10, 5};
    cout<<obj.maxSumSuchThatNo2ElementsAreAdjacent(A)<<endl;    //110 {5, 100, 5}

    A = {3, 2, 7, 10};
    cout<<obj.maxSumSuchThatNo2ElementsAreAdjacent(A)<<endl;    //13 {3, 10}
    
    A = {3, 2, 5, 10, 7};   
    cout<<obj.maxSumSuchThatNo2ElementsAreAdjacent(A)<<endl;    //15 {3, 5, 7}

    return 0;
}