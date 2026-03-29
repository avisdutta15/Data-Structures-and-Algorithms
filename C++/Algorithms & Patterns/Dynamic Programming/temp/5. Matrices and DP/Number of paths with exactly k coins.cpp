

/*
    Given a matrix where every cell has some number of coins. Count number of 
    ways to reach bottom right from top left with exactly k coins. We can move 
    to (i+1, j) and (i, j+1) from a cell (i, j).
    Example:

    Input:  k = 12
            mat[][] = { {1, 2, 3},
                        {4, 6, 5},
                        {3, 2, 1}
                    };
    Output:  2
    There are two paths with 12 coins
    1 -> 2 -> 6 -> 2 -> 1
    1 -> 2 -> 3 -> 5 -> 1

    Recurrence:
        pathCount(m, n, k):     Number of paths to reach mat[m][n] from mat[0][0] 
                                with exactly k coins
        If(k<0)
            return 0;
        If (m == 0 and n == 0)
            return 1 if mat[0][0] == k else return 0
        Else:
            pathCount(m, n, k) = pathCount(m-1, n, k - mat[m][n]) + pathCount(m, n-1, k - mat[m][n]) 

*/

class Solution{
        int pathCountUtil(vector<vector<int>> grid, int m, int n, int K){
            if(K<0)
                return 0;
            if(m==0 || n==0)
                return K==grid[m][n];
            return pathCountUtil(grid, m-1, n, K-grid[m][n]) + pathCountUtil(grid, m, n-1, K-grid[m][n]);
        }
        int pathCountDPRecDP(int mat[][C], int m, int n, int k){ 
            
            if (m < 0 || n < 0) return 0; 
            if (m==0 && n==0) return (k == mat[m][n]); 
        
            // If this subproblem is already solved 
            if (dp[m][n][k] != -1) return dp[m][n][k]; 
        
            // (m, n) can be reached either through (m-1, n) or through (m, n-1) 
            dp[m][n][k] = pathCountDPRecDP(mat, m-1, n, k-mat[m][n]) + 
                        pathCountDPRecDP(mat, m, n-1, k-mat[m][n]); 
        
            return dp[m][n][k]; 
        } 
    public:
        int pathCount(vector<vector<int>> grid, int K){
            int m = grid.size();
            int n = grid[0].size();

            return pathCountUtil(grid, m-1, n-1, K);
        }
        
        
};

int main(){
    Solution obj;
    vector<vector<int>> grid =  { {1, 2, 3},
                                {4, 6, 5},
                                {3, 2, 1}
                                };
    obj.pathCount(grid, 12);
}