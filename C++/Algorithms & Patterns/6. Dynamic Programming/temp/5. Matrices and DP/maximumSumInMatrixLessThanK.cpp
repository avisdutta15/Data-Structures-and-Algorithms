#include <bits/stdc++.h>
using namespace std;

/*
    Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix 
    such that its sum is no larger than k.

    Example:

    Input: matrix = [[1, 0,1],
                     [0,-2,3]
                    ], k = 2
    Output: 2 
    Explanation: Because the sum of rectangle [[0, 1], [-2, 3]] is 2,
             and 2 is the max number no larger than k (k = 2).

*/

/*
    Approach: maxSumRectangle(Kadane 2D) + subarray size closest to K
                Here we need to sum[i] - sum[j] <=K
                            =>     sum[i] - K <= sum[j]

                TC: O(col^2 * row * log(row)) 
*/

class Solution{
    int getMaxSum(vector<int> sums, int K){
        if(sums.size()==0)
            return 0;
        set<int> s;
        s.insert(0);
        int sum = 0;
        int result = INT_MIN;

        for(int i: sums){
            sum = sum + i;
            auto it = s.lower_bound(sum-K);
            if(it!=s.end()){
                result = max(result, sum-(*it));        
            }
            s.insert(sum);
        }
        return result;
    }
    public:
        int maximumSumInMatrixLessThanK(vector<vector<int>> matrix, int K){
            int rows = matrix.size();
            if(rows==0)
                return 0;
            int cols = matrix[0].size();
            int ans = INT_MIN;
            vector<int> sum(rows, 0);

            for(int left = 0; left<cols; left++){

                fill(sum.begin(), sum.end(), 0);
                for(int right = left; right<cols; right++){
                    for(int row = 0; row<rows; row++){
                        sum[row] = sum[row] + matrix[row][right];
                    }

                    //once you get a column sum, find the max sum<=K
                    ans = max(ans, getMaxSum(sum, K));
                }
            }

            return ans;
        }
};

int main(){
    vector<vector<int>> matrix = {{1,0,1},
                                  {0,-2,3}};
    Solution obj;
    cout<<obj.maximumSumInMatrixLessThanK(matrix, 2);
}