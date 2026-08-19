#include <bits/stdc++.h>
using namespace std;

/*
    We are given a Triangular matrix. We need to find the minimum path sum 
    from the first row to the last row.

    At every cell we can move in only two directions: either to the 
    bottom cell (↓) or to the bottom-right cell(↘).

    Examples: 
    Input: triangle[][] =  [[2],
                            [3, 7],
                            [8, 5, 6],
                            [6, 1, 9, 3]]
    Output: 11 
    Explanation : The path is 2 → 3 → 5 → 1, which results in a minimum sum of 2 + 3 + 5 + 1 = 11.

    Input: triangle[][] =  [[3],
                            [6, 9],
                            [8, 7, 1],
                            [9, 6, 8, 2]]
    Output: 15
    Explanation: The path is 3 → 9 → 1 → 2, which results in a minimum sum of 3 + 9 + 1 + 2 = 15.

    Approach:
    Here we will start the recursion from (0,0) and check what is the min path sum to reach the last row.
    Base Case:
        When at last row,
            return the cost here.
        Else
            minPathSumFromDown = goto down(i+1, j) and get the min path
            minPathSumFromDiagonalBelow = goto diagonallyrightdown(i+1, j+1) and get the min path
            minPathSumfromThisCell(i, j) = cost[i][j] + min({minPathSumFromDown, minPathSumFromDiagonalBelow});

    Why we started from (0,0) but not from (n-1) like the grid sum?
    Reason, for each cell in the last row, we would have to find and store the min path sum to reach (0,0) in a vector.
    Atlast return the minimum from that vector. This is computationally bigger.
*/

class Solution{
        int minPathSumNaive(vector<vector<int>> &triangle, int i, int j){
            if(i==0 && j==0)
                return triangle[i][j];
            
            if(i<0 || j<0)
                return INT_MAX;
            
            int minCostFromAbove = minPathSumNaive(triangle, i-1, j);
            int minCostFromDiagonallyLeftAbove = minPathSumNaive(triangle, i-1, j-1);
            
            int minCostFromIJ = triangle[i][j] + min({minCostFromAbove, minCostFromDiagonallyLeftAbove});
            return minCostFromIJ;
        }

        int minPathSumRecursive(vector<vector<int>> &triangle, int i, int j, int &lastRow){
            if(i==lastRow-1){
                return triangle[i][j];
            }
            
            if(i>=lastRow)
                return INT_MAX;

            int minPathSumFromDown = minPathSumRecursive(triangle, i+1, j, lastRow);
            int minPathSumFromDiagonalBelow = minPathSumRecursive(triangle, i+1, j+1, lastRow);
            
            return triangle[i][j] + min({minPathSumFromDown, minPathSumFromDiagonalBelow});
        }
        
        int minPathSumTopDown(vector<vector<int>> &triangle, int i, int j, int &lastRow, unordered_map<string, int> &lookup){
            if(i==lastRow-1){
                return triangle[i][j];
            }
            
            if(i>=lastRow)
                return INT_MAX;
            
            string key = to_string(i) + " " + to_string(j);
            if(lookup.find(key) != lookup.end())
                return lookup[key];

            int minPathSumFromDown = minPathSumTopDown(triangle, i+1, j, lastRow, lookup);
            int minPathSumFromDiagonalBelow = minPathSumTopDown(triangle, i+1, j+1, lastRow, lookup);
            
            return lookup[key] = triangle[i][j] + min({minPathSumFromDown, minPathSumFromDiagonalBelow});
        }

        int minPathSumBottomUp(vector<vector<int>> &triangle, int &lastRow){
            vector<vector<int>> dp(lastRow+1, vector<int>(lastRow+1, 0));

            for(int i=lastRow; i>=0; i--){
                for(int j=0; j<triangle[i].size(); j++){
                    if(i==lastRow-1)
                        dp[i][j] = triangle[i][j];
                    else if(i>=lastRow)
                        dp[i][j] = INT_MAX;     //denotes not possible
                    else{
                        int minPathSumFromDown = dp[i+1][j];
                        int minPathSumFromDiagonalBelow = dp[i+1][j+1];
                        dp[i][j] = triangle[i][j] + min({minPathSumFromDown, minPathSumFromDiagonalBelow});
                    }
                }
            }

            return dp[0][0];
        }

    public:
        int minPathSum(vector<vector<int>> &triangle){
            int lastRow = triangle.size();

            /* Naive Approach */
            // int colsInLastRow = triangle[lastRow-1].size();
            // vector<int> lastRowCost(colsInLastRow);

            // for(int j=0; j<colsInLastRow; j++){
            //     lastRowCost[j] = minPathSumNaive(triangle, lastRow-1, j);
            // }
            // return *min_element(lastRowCost.begin(), lastRowCost.end());

            //Recursive Optimal Approach
            // return minPathSumRecursive(triangle, 0, 0, lastRow);

            //Top Down
            // unordered_map<string, int> lookup;            
            // return minPathSumTopDown(triangle, 0, 0, lastRow, lookup);
            
            //BottomUp
            //return minPathSumBottomUp(triangle, lastRow);
        }
};


int main(){
    Solution obj;
    vector<vector<int>> triangle=  
                            {{2},
                            {3, 7},
                            {8, 5, 6},
                            {6, 1, 9, 3}};

    cout<<obj.minPathSum(triangle)<<endl;   //11        
    
    triangle=               {{3},
                            {6, 9},
                            {8, 7, 1},
                            {9, 6, 8, 2}};
    cout<<obj.minPathSum(triangle)<<endl;   //15
    return 0;
}