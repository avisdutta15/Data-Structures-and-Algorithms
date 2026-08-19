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
        int maxSumSuchThatNo2ElementsAreAdjacentRecursive(vector<int> &A, int N){
            if(N==0)
                return 0;
            if(N==1)
                return A[N-1];

            int include = INT_MIN, exclude = INT_MIN;

            //Do N-2 as current element is included
            include = A[N-1] + maxSumSuchThatNo2ElementsAreAdjacentRecursive(A, N-2);
            
            //Do N-1 as current element is excluded 
            exclude = maxSumSuchThatNo2ElementsAreAdjacentRecursive(A, N-1);        
            return max(include, exclude);
        }

        int maxSumSuchThatNo2ElementsAreAdjacentTopDown(vector<int> &A, int N, unordered_map<int, int> &lookup){
            if(N==0)
                return 0;
            if(N==1)
                return A[N-1];

            if(lookup.find(N) != lookup.end())
                return lookup[N];
            
            int include = INT_MIN, exclude = INT_MIN;

            //Do N-2 as current element is included
            include = A[N-1] + maxSumSuchThatNo2ElementsAreAdjacentTopDown(A, N-2, lookup);
            
            //Do N-1 as current element is excluded 
            exclude = maxSumSuchThatNo2ElementsAreAdjacentTopDown(A, N-1, lookup);        
            return lookup[N] = max(include, exclude);
        }

        int maxSumSuchThatNo2ElementsAreAdjacentBottomUp(vector<int> &A, int N){
            vector<int> dp(N+1, 0);
            dp[0] = 0;
            dp[1] = A[0];

            for(int n=2; n<=N; n++){
                int include = A[n-1] + dp[n-2];
                int exclude = dp[n-1];
                dp[n] = max(include, exclude);
            }
            return dp[N];
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