#include <bits/stdc++.h>
using namespace std;

/*
    Given an array arr[] of length n and an integer target, the task is to find 
    the number of subsets with a sum equal to target.

    Examples: 
    Input: arr[] = [1, 2, 3, 3], target = 6 
    Output: 3 
    Explanation: All the possible subsets are [1, 2, 3], [1, 2, 3] and [3, 3]

    Input: arr[] = [1, 1, 1, 1], target = 1 
    Output: 4 
    Explanation: All the possible subsets are [1], [1], [1] and [1]
*/

class Solution{
    int countNumberOfSubsetsWithGivenSumRecursive(vector<int> &A, int N, int target){
        if(N == 0 && target== 0)
            return 1;
        if(N == 0 && target!= 0)
            return 0;

        int include = 0, exclude = 0;
        if(A[N-1]<=target)
            include = countNumberOfSubsetsWithGivenSumRecursive(A, N-1, target-A[N-1]);
        exclude = countNumberOfSubsetsWithGivenSumRecursive(A, N-1, target);

        return include + exclude;
    }

    int countNumberOfSubsetsWithGivenSumTopDown(vector<int> &A, int N, int target, unordered_map<string, int> &lookup){
        if(N == 0 && target== 0)
            return 1;
        if(N == 0 && target!= 0)
            return 0;

        string key = to_string(N) + " " + to_string(target);
        if(lookup.find(key)!=lookup.end())
            return lookup[key];

        int include = 0, exclude = 0;
        if(A[N-1]<=target)
            include = countNumberOfSubsetsWithGivenSumTopDown(A, N-1, target-A[N-1], lookup);
        exclude = countNumberOfSubsetsWithGivenSumTopDown(A, N-1, target, lookup);

        lookup[key] = include + exclude;
        return lookup[key];
    }

    int countNumberOfSubsetsWithGivenSumBottomUp(vector<int> &A, int N, int target){
        vector<vector<int>>dp(N+1, vector<int>(target+1, 0));

        for(int n=0; n<=N; n++){
            for(int sum=0; sum<=target; sum++){
                if(n == 0 && sum == 0)
                    dp[n][sum] = 1;
                else if(n == 0 && sum!=0)
                    dp[n][sum] = 0;
                else{
                    bool include = 0, exclude = 0;
                    if(A[n-1]<=sum){
                        include = dp[n-1][sum-A[n-1]];
                    }
                    exclude = dp[n-1][sum];
                    dp[n][sum] = include + exclude;
                }
            }
        }
        
        printMatrix(dp);
        return dp[N][target];
    }
    
    void printMatrix(const vector<vector<int>>& matrix) {
        for (const auto& row : matrix) { // Loop through each row
            for (const auto& element : row) { // Loop through each element in the row
                cout << element << " "; // Print element with space
            }
            cout << endl; // Move to the next line after each row
        }
    }
public:
    int countNumberOfSubsetsWithGivenSum(vector<int> &A, int target){
        int N = A.size();
        return countNumberOfSubsetsWithGivenSumRecursive(A, N, target);
        // unordered_map<string, int> lookup;
        // return countNumberOfSubsetsWithGivenSumTopDown(A, N, target, lookup);
        // return countNumberOfSubsetsWithGivenSumBottomUp(A, N, target);
    }
};

int main(){
    Solution obj;
    vector<int> A = {1, -1, 24};
    cout<<obj.countNumberOfSubsetsWithGivenSum(A, 24)<<endl;
}