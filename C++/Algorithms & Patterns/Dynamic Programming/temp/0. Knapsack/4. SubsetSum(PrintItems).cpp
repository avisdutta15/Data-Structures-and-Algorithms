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

    This is because if we have an array like {1, -1, 24}
    Then there are 2 subsets possible (1, -1, 24) and (24).

    Now if we add add targetSum==0 ? return 1;
    Then it would not consider the case (1, -1, 24). It only considered (24).
    This would give a wrong result if wanted to count the number of subsets with given sum.

    i.e. at 
                     f(3, 24)
              inc A[2]/   \ excl A[2]
                f(2, 0)   f(2, 24)

    Now here if we return f(2,0) == returns 1 then we would not get the other subsets where 24 is 
    included but the sum of other elements are also included and their sum is 0.

    Draw a complete recursion tree to understand.      
*/

class Solution{
    void printMatrix(vector<vector<bool>> &lookup){
        for(int i=0; i<lookup.size(); i++){
            for(int j=0; j<lookup[0].size(); j++)
                lookup[i][j]==true ? cout<<" T " : cout<<" F ";
            cout<<endl;
        }
    }

    void printItems(vector<vector<bool>> &dp, vector<int> &A, int N, int targetSum){
        //For debugging
        //printMatrix(dp);

        int n = N, sum = targetSum;
        while(n>0 && sum>0){
            bool excluded = dp[n-1][sum];
            if(excluded == true)
                n = n-1;
            else{
                cout<<"Including item "<<A[n-1]<<endl;
                //once this item is included, goto the next item with reduced sum.
                sum = sum - A[n-1];
                n = n - 1; 
            }
        }
    }
    
    bool subsetSumBottomDown(vector<int> &A, int N, int targetSum){        
        vector<vector<bool>> dp(N+1, vector<bool>(targetSum+1, false));
        for(int n=0; n<=N; n++){
            for(int sum=0; sum<=targetSum; sum++){
                if(n == 0 && sum == 0)
                    dp[n][sum] = true;
                else if(n == 0 && sum!=0)
                    dp[n][sum] = false;
                else{
                    bool include = false, exclude = false;
                    if(A[n-1]<=sum){
                        include = dp[n-1][sum-A[n-1]];
                    }
                    exclude = dp[n-1][sum];
                    dp[n][sum] = include || exclude;
                }
            }
        }

        printItems(dp, A, N, targetSum);
        return dp[N][targetSum];
    }

public:    
    int subsetSum(vector<int> &A, int targetSum){
        int N = A.size();
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