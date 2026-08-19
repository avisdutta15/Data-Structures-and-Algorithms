#include <bits/stdc++.h>
using namespace std;

class Solution{
    int vertices;
    public:
        int countPathsWithKEdgesUtil(vector<vector<int>> &matrix, int u, int v, int K){
            if(K==0 && u==v)    
                return 1;

            if(K<=0)
                return 0;

            int count = 0;
            //for all the adjacent vertices of u
            for(int i=0; i<vertices; i++){
                if(matrix[u][i]==1)
                    count += countPathsWithKEdgesUtil(matrix, i, v, K-1);
            }
            return count;
        }

        int countPathsWithKEdges(vector<vector<int>> matrix, int u, int v, int K){
            vertices = matrix.size();
            return countPathsWithKEdgesUtil(matrix, u, v, K);
        }
};

int main(){
    vector<vector<int>> matrix = {  {0, 1, 1, 1}, 
                                    {0, 0, 0, 1}, 
                                    {0, 0, 0, 1}, 
                                    {0, 0, 0, 0} 
                                }; 
    Solution obj;
    cout<<obj.countPathsWithKEdges(matrix, 0, 3, 2);
}