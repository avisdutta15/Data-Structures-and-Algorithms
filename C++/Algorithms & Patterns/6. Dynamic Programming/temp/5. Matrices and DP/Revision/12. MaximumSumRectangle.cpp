#include <bits/stdc++.h>
using namespace std;

/*
    Given a 2D array, the task is to find the maximum sum sub-matrix in it.
    For example, in the following 2D array, the maximum sum sub-matrix is highlighted 
    with green rectangle and sum of all elements in this sub-matrix is 29.

    {{ 1,    2, -1, -4, -20}, 
     {-8,   -3,  4,  2,  1}, 
     { 3,    8, 10,  1,  3}, 
     {-4,   -1,  1,  7, -6}};

    Ans:    {-3,  4,  2}
            {8,  10,  1}
            {-1,  1,  7}
        Sum = 29

*/

class Solution{
        tuple<int, int, int> Kadane(vector<int> &A){
            int subarrayStart = 0, maxSumSubarrayStart = 0;
            int subarrayEnd = 0, maxSumSubarrayEnd = 0;
            int maxSubarraySumAtI = A[0];
            int maxSum = A[0];

            for(int i=1; i<A.size(); i++){
                //if we are extending by taking the current element then update the subarrayEnd
                if(maxSubarraySumAtI + A[i] > A[i]){
                    maxSubarraySumAtI = maxSubarraySumAtI + A[i];
                    subarrayEnd = i;
                }
                //if we creating a new subarray from i them update both start and end
                else if(maxSubarraySumAtI + A[i] < A[i]){
                    maxSubarraySumAtI = A[i];
                    subarrayStart = i;
                    subarrayEnd = i;
                }
                
                //update Global variables
                if(maxSubarraySumAtI > maxSum){
                    maxSumSubarrayStart = subarrayStart;
                    maxSumSubarrayEnd = subarrayEnd;
                    maxSum = maxSubarraySumAtI;
                }
            }

            return {maxSum, maxSumSubarrayStart, maxSumSubarrayEnd};
        }
    public:
        vector<int> maximumSumRectangle(vector<vector<int>> &A){
            int rows = A.size();
            int cols = A[0].size();

            vector<int> arr(rows, 0);
            int left = 0, right = 0, top = 0, bottom = 0;
            int maxSumRectangle = INT_MIN;

            for(int L=0; L<cols; L++){
                
                //make the temp array 0. to start the processing for all 
                //right pointers corresponding to this left pointer
                for(int i=0; i<rows; i++)
                    arr[i] = 0;

                for(int R=L; R<cols; R++){

                    //sum up the col R with existing L
                    for(int i=0; i<rows; i++)
                        arr[i] = arr[i] + A[i][R];

                    //send this arr to Kadane() 
                    auto [sumOfCurrentRectangle, currentTop, currentBottom] = Kadane(arr);
                    if(sumOfCurrentRectangle > maxSumRectangle){
                        left    = L;
                        right   = R;
                        top     = currentTop;
                        bottom  = currentBottom;
                        maxSumRectangle = sumOfCurrentRectangle;
                    }
                }
            }

            return vector<int>{left, right, top, bottom, maxSumRectangle};
        }
};


int main(){
    Solution obj;
    vector<vector<int>> A =   {{1, 2, -1, -4, -20}, 
                               {-8, -3, 4, 2, 1}, 
                               {3, 8, 10, 1, 3}, 
                               {-4, -1, 1, 7, -6}};
    
    auto ans = obj.maximumSumRectangle(A);
    for(auto i: ans){
        cout<<i<<" ";
    }

    return 0;
}