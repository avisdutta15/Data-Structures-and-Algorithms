#include <bits/stdc++.h>
using namespace std;

/*
    We have given numbers in form of a triangle, by starting at the top of the 
    triangle and moving to adjacent numbers on the row below, find the maximum 
    total from top to bottom. 
    
    Examples : 
    Input : 
    3
    7 4
    2 4 6
    8 5 9 3
    Output : 23
    Explanation : 3 + 7 + 4 + 9 = 23 

    Input :
    8
    -4 4
    2 2 6
    1 1 1 1
    Output : 19
    Explanation : 8 + 4 + 6 + 1 = 19
*/

class Solution{
        int maxPathSumRecursive(vector<vector<int>> &triangle, int i, int j, int lastRow){
            if(i == lastRow-1)
                return triangle[i][j];
            
            if(i >= lastRow)
                return INT_MAX;
            
            int maxPathSumFromDown = maxPathSumRecursive(triangle, i+1, j, lastRow);
            int maxPathSumFromDiagonalBelow = maxPathSumRecursive(triangle, i+1, j+1, lastRow);
            
            return triangle[i][j] + max({maxPathSumFromDown, maxPathSumFromDiagonalBelow});
        }

        int maxPathSumTopDown(vector<vector<int>> &triangle, int i, int j, int lastRow, unordered_map<string, int> &lookup){
            if(i == lastRow-1)
                return triangle[i][j];
            
            if(i >= lastRow)
                return INT_MAX;
            
            string key = to_string(i) + " " + to_string(j);
            if(lookup.find(key) != lookup.end())
                return lookup[key];

            int maxPathSumFromDown = maxPathSumTopDown(triangle, i+1, j, lastRow, lookup);
            int maxPathSumFromDiagonalBelow = maxPathSumTopDown(triangle, i+1, j+1, lastRow, lookup);
            
            return lookup[key] = triangle[i][j] + max({maxPathSumFromDown, maxPathSumFromDiagonalBelow});
        }

        int maxPathSumBottomUp(vector<vector<int>> &triangle){
            int lastRow = triangle.size();
            vector<vector<int>> dp(lastRow+1, vector<int>(lastRow+1, 0));
            
            for(int i=lastRow; i>=0; i--){
                for(int j=0; j<=triangle[i].size(); j++){
                    if(i == lastRow-1)
                        dp[i][j] = triangle[i][j];
                    else if(i >= lastRow)
                        dp[i][j] = INT_MAX;
                    else{
                        int maxPathSumFromDown = dp[i+1][j];
                        int maxPathSumFromDiagonalBelow = dp[i+1][j+1];
                        
                        dp[i][j] = triangle[i][j] + max({maxPathSumFromDown, maxPathSumFromDiagonalBelow});
                    }
                }
            }
            return dp[0][0];
        }

    public:
        int maxPathSum(vector<vector<int>> &triangle){
            int lastRow = triangle.size();

            // return maxPathSumRecursive(triangle, 0, 0, lastRow);            
            
            // unordered_map<string, int> lookup;
            // return maxPathSumTopDown(triangle, 0, 0, lastRow, lookup);

            return maxPathSumBottomUp(triangle);
        }
};


int main(){
    Solution obj;
    vector<vector<int>> triangle = { {3}
                                    ,{7, 4}
                                    ,{2, 4, 6}
                                    ,{8, 5, 9, 3}};

    cout<<obj.maxPathSum(triangle)<<endl;       //23

    triangle = { {8}
                ,{-4, 4}
                ,{2, 2, 6}
                ,{1, 1, 1, 1}};

    cout<<obj.maxPathSum(triangle)<<endl;       //19
    return 0;
}