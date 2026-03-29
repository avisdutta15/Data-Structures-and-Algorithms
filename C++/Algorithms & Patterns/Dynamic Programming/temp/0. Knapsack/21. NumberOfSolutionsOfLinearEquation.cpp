#include <bits/stdc++.h>
using namespace std;

/*
    Given a linear equation of n variables, find number of non-negative integer solutions of it. 
    Input:  coeff[] = {1, 2}, rhs = 5
    Output: 3
    The equation "x + 2y = 5" has 3 solutions.
    (x=3,y=1), (x=1,y=2), (x=5,y=0)

    Input:  coeff[] = {2, 2, 3}, rhs = 4
    Output: 3
    The equation "2x + 2y + 3z = 4"  has 3 solutions.
    (x=0,y=2,z=0), (x=2,y=0,z=0), (x=1,y=1,z=0)

    Input: coeff[] = {3, 1}, rhs = 9
    Output: 4
    The equation "3x + 1y = 9" has 4 solutions.
    (x=0, y=9), (x=1, y=6), (x=2, y=3) and (x=3, y=0)

    Approach:
        This approach allows repeated use of coefficients (like coin denominations).
        The base case ensures recursion stops when the sum equals the target constant.
        The function explores all possible combinations and sums them up.

        This recursive function essentially explores all ordered sequences of coefficients 
        that sum up to the given constant. The problem is similar to finding the total number 
        of ways to get the denomination of coins. Here, coefficients of an equation can be 
        considered coins denominations, and the RHS of an equation can be considered the 
        desired change..

        Each time we pick a coefficient, we "use up" part of the total sum (constant).
        By subtracting coefficients[i], we reduce the problem to finding how many ways we can sum 
        the remaining coefficients to reach the new smaller constant.
*/

class Solution{
        int numberOfSolutionsRecursive(vector<int> &coefficient, int N, int rhs){
            // if rhs become 0, return 1 (solution found)
            if(rhs == 0)
                return 1;
            
            // return 0 (solution does not exist) if rhs becomes negative or
            // no coefficient is left            
                if(N == 0 || rhs < 0)
                return 0;

            int include = 0, exclude = 0;
            if(coefficient[N-1] <= rhs)
                include = numberOfSolutionsRecursive(coefficient, N, rhs - coefficient[N-1]);
            exclude = numberOfSolutionsRecursive(coefficient, N-1, rhs);
            return include + exclude;
        }

        int numberOfSolutionsTopDown(vector<int> &coefficient, int N, int rhs, unordered_map<string, int> &lookup){
            if(rhs == 0)
                return 1;

            if(N == 0 || rhs < 0)
                return 0;

            string key = to_string(N) + " " + to_string(rhs);
            if(lookup.find(key) != lookup.end())
                return lookup[key];

            int include = 0, exclude = 0;
            if(coefficient[N-1] <= rhs)
                include = numberOfSolutionsTopDown(coefficient, N, rhs - coefficient[N-1], lookup);
            exclude = numberOfSolutionsTopDown(coefficient, N-1, rhs, lookup);
            return lookup[key]= include + exclude;
        }

        int numberOfSolutionsBottomUp(vector<int> &coefficient, int N, int rhs){
            vector<vector<int>> dp(N+1, vector<int>(rhs+1, 0));

            for(int n=0; n<=N; n++){
                for(int sum=0; sum<=rhs; sum++){
                    if(sum == 0)
                        dp[n][sum] = 1;
                    else if(n == 0 || sum < 0)
                        dp[n][sum] = 0;
                    else{
                        int include = 0, exclude = 0;
                        if(coefficient[n-1] <= sum)
                            include = dp[n][sum - coefficient[n-1]];
                        exclude = dp[n-1][sum];
                        dp[n][sum] = include + exclude;
                    }
                }
            }
            return dp[N][rhs];
        }
    public:
        int numberOfSolutions(vector<int> &coefficient, int N, int rhs){
            // return numberOfSolutionsRecursive(coefficient, N, rhs);

            // unordered_map<string, int> lookup;
            // return numberOfSolutionsTopDown(coefficient, N, rhs, lookup);
            return numberOfSolutionsBottomUp(coefficient, N, rhs);
        }
};


int main(){
    Solution obj;
    vector<int> coefficient = {1, 2};
    cout<<obj.numberOfSolutions(coefficient, 2, 5)<<endl;

    coefficient = {2, 2, 3};
    cout<<obj.numberOfSolutions(coefficient, 3, 4)<<endl;

    coefficient = {3, 1};
    cout<<obj.numberOfSolutions(coefficient, 2, 9)<<endl;

    return 0;
}