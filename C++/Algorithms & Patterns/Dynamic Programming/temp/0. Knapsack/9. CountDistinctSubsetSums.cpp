#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

/*
    Given an array arr[] of size n, the task is to find a distinct sum that can be 
    generated from the subsets of the given sets and return them in increasing order. 
    It is given that the sum of array elements is small.

    Examples:  
    Input: arr[] = [1, 2]
    Output: [0, 1, 2, 3]
    Explanation: Four distinct sums can be calculated which are 0, 1, 2 and 3.
    0 if we do not choose any number.
    1 if we choose only 1.
    2 if we choose only 2.
    3 if we choose 1 and 2.

    Input: arr[] = [1, 2, 3]
    Output: [0, 1, 2, 3, 4, 5, 6]
    Explanation: Seven distinct sums can be calculated which are 0, 1, 2, 3, 4, 5 and 6.
    0 if we do not choose any number.
    1 if we choose only 1.
    2 if we choose only 2.
    3 if we choose only 3.
    4 if we choose 1 and 3.
    5 if we choose 2 and 3.
    6 if we choose 1, 2 and 3.

Approach:
    1. Recursive.
        a. Keep a hash set to rule out duplicates.
        b. each time you visit an element, we have 2 options.
            i. add it to the current sum.
            ii.exclude it from the current sum.
    
    2. TopDown
        If we observe carefully then we see, the max sum possible is the total sum of all elements.
        So we keep a lookup (N, current_sum) where current_sum ranges from 0 to total_sum.
        At each element, we check if the current_sum is already reached with N elements.
            If yes then return.(Do not go into recursion)
            else 
                goto recursion (include, exclude)
                mark this current_sum as visited.
    
    3.  Bottom up
        Create a 2D array (N+1, totalSum+1).
        dp[n][sum] denotes if sum is possible with n elements.

        if n=0 and sum = 0
            dp[n][sum] = true
        if sum = 0
            dp[n][sum] = true
        if n = 0
            dp[n][sum] = false
        else{
            include, exclude
            include = check if sum achieved by current_sum-A[n-1] is possible or not.
            exclude = check if sum achieved by excluding current element.
            dp[n][sum] = include || exclude
        }

        now check if dp[N][sum] = true for all 0<=sum<=totalSum.
        the last row denotes if distinct sum 'sum' can be achieved by N elements(either by including or excluding it).
*/

class Solution{
    void countDistinctSubsetSumsRecursive(vector<int> &A, int sum, int N, unordered_set<int> &sums){
        if(N == 0){
            sums.insert(sum);
            return;
        }

        //include
        countDistinctSubsetSumsRecursive(A, sum + A[N-1], N-1, sums);
        //exclude
        countDistinctSubsetSumsRecursive(A, sum, N-1, sums);
    }

    void countDistinctSubsetSumsTopDown(vector<int> &A, int sum, int N, unordered_set<int> &sums, vector<vector<bool>> &lookup){
        if(N == 0){
            sums.insert(sum);
            return;
        }
        
        //if we can make sum with N elements then return.
        if(lookup[N][sum] == true)
            return;

        //include
        countDistinctSubsetSumsTopDown(A, A[N-1] + sum, N-1, sums, lookup);
        //exclude
        countDistinctSubsetSumsTopDown(A, sum, N-1, sums, lookup);

        //sum can be made with N elements.
        lookup[N][sum] = true;
    }

    void countDistinctSubsetSumsBottomUp(vector<int> &A, int N, unordered_set<int> &sums){
        int totalSum = accumulate(A.begin(), A.end(), 0);
        vector<vector<bool>> dp(N+1, vector<bool>(totalSum+1, false));

        for(int n=0; n<=N; n++){
            for(int sum=0; sum<=totalSum; sum++){
                // we can make 0 sum with 0 elements
                if(n==0 && sum==0)
                    dp[n][sum] = true;
                // with n elements we can always make 0 sum by excluding those elements
                else if(sum == 0)
                    dp[n][sum] = true;
                // with no elements, we cannot make sum>1
                else if(n==0)
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

        //now dp[N][sum] has cells true or false.
        //if dp[N][sum] == true. it means sum can be reached with N elements.
        //if dp[N][sum] == false. it means sum cannot be reached with N elements.
        for(int sum=0; sum<=totalSum; sum++){
            if(dp[N][sum] == true)
                sums.insert(sum);
        }
    }

    public:
        vector<int> countDistinctSubsetSums(vector<int> &A){
            int N = A.size();
            unordered_set<int> sums;
            vector<int> distinctSums;
            int sum = 0;
            // countDistinctSubsetSumsRecursive(A, sum, N, sums);

            // int totalSum = accumulate(A.begin(), A.end(), 0);
            // vector<vector<bool>> lookup(N+1, vector<bool>(totalSum+1, false));
            // countDistinctSubsetSumsTopDown(A, sum, N, sums, lookup);

            countDistinctSubsetSumsBottomUp(A, N, sums);            

            for(int i: sums)
                distinctSums.push_back(i);

            //sort the ans for better readibility.
            sort(distinctSums.begin(), distinctSums.end());
            return distinctSums;
        }
};


int main(){
    Solution obj;
    vector<int> A = {1, 2};
    auto distinctSums = obj.countDistinctSubsetSums(A);
    for(int i: distinctSums)
        cout<<i<<" ";
    
    cout<<endl;
    A = {1, 2, 3};
    distinctSums = obj.countDistinctSubsetSums(A);
    for(int i: distinctSums)
        cout<<i<<" ";
        
    return 0;
}