#include <bits/stdc++.h>
using namespace std;

/*
    Given a linear equation of n variables, find number of non-negative integer solutions of it. 
    Input:  coeff[] = {1, 2}, rhs = 5
    Output: 3
    The equation "x + 2y = 5" has 3 solutions.
    (x=3,y=1), (x=1,y=2), (x=5,y=0)

    This problem can be simply thought as a coin change problem.
    rhs is the sum.
    coeffients are the coin values.
    variables are the no of coins.

*/



class Solution{
        int LinearEquationSolutionsCountUtil(vector<int> coeffs, int rhs, int n){
            if(rhs==0)
                return 1;
                
            if(rhs!=0 && n<0)
                return 0;

            int include = 0;
            if(rhs-coeffs[n]>=0)
                include = LinearEquationSolutionsCountUtil(coeffs, rhs-coeffs[n], n);
            int exclude = LinearEquationSolutionsCountUtil(coeffs, rhs, n-1);

            return include + exclude;
        }
    public:
        int LinearEquationSolutionsCount(vector<int> coeffs, int rhs){
            int n = coeffs.size();
            return LinearEquationSolutionsCountUtil(coeffs, rhs, n-1);
        }

        int LinearEquationSolutionsCountDP(vector<int> coeffs, int rhs){
            int n = coeffs.size();
            int m = rhs;
            
            int DP[n+1][m+1]={0};

            for(int i=0; i<=n; i++)
                DP[i][0] = 1;
            
            for(int i=1; i<=m; i++)
                DP[0][i] = 0;
            
            for(int i=1; i<=n; i++){
                for(int j=1; j<=m; j++){
                    int include = 0;
                    if(j-coeffs[i-1]>=0)
                        include = DP[i][j-coeffs[i-1]];
                    int exclude = DP[i-1][j];
                    DP[i][j] = include + exclude;
                }
            }
            
            return DP[n][m];
        }

};

int main(){
    Solution obj;
    vector<int> coeffs = {2, 2, 5};
    cout<<obj.LinearEquationSolutionsCount(coeffs, 4)<<endl;

    cout<<obj.LinearEquationSolutionsCountDP(coeffs, 4)<<endl;
}