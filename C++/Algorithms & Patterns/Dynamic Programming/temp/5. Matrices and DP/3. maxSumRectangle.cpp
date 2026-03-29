#include <bits/stdc++.h>
using namespace std;

/*
    Given a 2D array, find the maximum sum subarray in it.

    Kadane’s algorithm for 1D array can be used to reduce the time complexity to O(n^3). 
    The idea is to fix the left and right columns one by one and find the maximum sum 
    contiguous rows for every left and right column pair. We basically find top and bottom 
    row numbers (which have maximum sum) for every fixed left and right column pair. To 
    find the top and bottom row numbers, calculate sun of elements in every row from left
    to right and store these sums in an array say temp[]. So temp[i] indicates sum of 
    elements from left to right in row i. If we apply Kadane’s 1D algorithm on temp[], 
    and get the maximum sum subarray of temp, this maximum sum would be the maximum possible 
    sum with left and right as boundary columns. To get the overall maximum sum, we compare 
    this sum with the maximum sum so far.

    Ref: Tushar Roy

*/


struct KadaneResult{
    int maxSum;
    int start;
    int end;
};

class KadaneSum{    
    public:
        KadaneResult findMaxSum(int A[], int N){
            KadaneResult kd;
            kd.start = 0;
            kd.end   = 0;
            int beg  = 0;
            int max_ending_here = A[0];
            kd.maxSum = A[0];

            for(int i=1; i<N; i++){
                max_ending_here = max_ending_here + A[i];
                if(max_ending_here < A[i]){
                    max_ending_here = A[i];
                    beg = i;
                }
                if(kd.maxSum < max_ending_here){
                    kd.maxSum = max_ending_here;
                    kd.start  = beg;
                    kd.end    = i;
                }
            }
            return kd;
        }
};

class Solution{
    struct Result{
        int maxSum;
        int left;
        int right;
        int top;
        int down;
    };
    public:
        void SubRectangularMatrixWithMaximumSum(vector<vector<int>>A){
            int rows = A.size();
            int cols = A[0].size();

            Result result;
            result.maxSum = INT_MIN;
            int temp[rows];

            //preprocess the aux array : inititalize with 0
            for(int i=0; i<rows; i++)
                temp[i] = 0;
            
            //fix left and right pointers
            for(int left=0; left<cols; left++){
                
                //make the temp array 0. to start the processing for all right pointers corresponding to this left pointer
                for(int i=0; i<rows; i++)
                    temp[i] = 0;
                
                for(int right=left; right<cols; right++){
                    
                    // Calculate sum between current left and right for every row 'i' 
                    for(int i=0; i < rows; i++){
                        temp[i] += A[i][right];
                    }
                    
                    KadaneSum ks;
                    KadaneResult kd = ks.findMaxSum(temp, rows);
                    if(result.maxSum < kd.maxSum){
                        result.maxSum = kd.maxSum;
                        result.left   = left;
                        result.right  = right;
                        result.top    = kd.start;
                        result.down   = kd.end;
                    }
                }

            }
            cout<<"left: "<<result.left<<" right: "<<result.right<<" top: "<<result.top<<" bottom: "<<result.down<<" maxSum: "<<result.maxSum;
        }
};

//Time Complexity : left moves Col times, right moves Col times and Kadene takes row time.
//                  O(col * col * row)

int main(){
    vector<vector<int>> A = {
        { 2,  1, -3, -4,  5},
        { 0,  6,  3,  4,  1},
        { 2, -2, -1,  4, -5},
        {-3,  3,  1,  0,  3}
    };

    Solution obj;
    obj.SubRectangularMatrixWithMaximumSum(A);

}   