#include <bits/stdc++.h>
using namespace std;

/*
    Given a 2D matrix of dimension n x m, the task is to find the area 
    of largest submatrix whose sum is 0.

    Examples: 

    Input: mat[][] = [[9,  7, 16,  5], 
                      [1, -6, -7,  3], 
                      [1,  8,  7,  9], 
                      [7, -2,  0, 10]]
    Output: 6
    Explanation:
        Sum = -6 + -7 + 8 + 7 + -2 + 0 = 0
*/

class Solution{
    tuple<int, int, bool> subarraySum0(vector<int> &A){
        int preSumI = 0;
        unordered_map<int, int> map;
        int start = 0, end = 0, maxSubarraySize = -1;
        bool subarrayExists = false;

        for(int i=0; i<A.size(); i++){
            preSumI = preSumI + A[i];

            if(preSumI == 0){
                start = 0;
                end   = i;
                maxSubarraySize = i + 1;
                subarrayExists = true;
            }

            if(map.find(preSumI - 0)!= map.end()){
                int j = map[preSumI - 0];
                subarrayExists = true;
                if(maxSubarraySize < (i - (j + 1)) + 1){
                    maxSubarraySize =  (i - (j + 1)) + 1;
                    start = j+1;
                    end = i;
                }
            }

            map[preSumI] = i;
        }
        return {start, end, subarrayExists};
    }

public:
    int largestRectangularSubMatrixWithSum0(vector<vector<int>> &A){
        int rows = A.size();
        int cols = A[0].size();

        vector<int> arr(rows, 0);
        int left = 0, right = 0, top = 0, bottom = 0;
        int maxSumRectangleArea = 0;

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
                auto [currentTop, currentBottom, subarrayExists] = subarraySum0(arr);
                if(subarrayExists){
                    //area = Length * Breadth
                    int currentRectangleArea = (R - L + 1) * (currentBottom - currentTop + 1);
                    if(currentRectangleArea > maxSumRectangleArea){
                        left    = L;
                        right   = R;
                        top     = currentTop;
                        bottom  = currentBottom;
                        maxSumRectangleArea = currentRectangleArea;
                    }
                }
            }
        }

        return maxSumRectangleArea;
    }
};


int main(){
    Solution obj;
    vector<vector<int>> grid = {{9,  7, 16,  5}, 
                                {1, -6, -7,  3}, 
                                {1,  8,  7,  9}, 
                                {7, -2,  0, 10}};

    cout<<obj.largestRectangularSubMatrixWithSum0(grid)<<endl;

    grid = {
            {1,  2,  3}, 
            {-3, -2, -1}, 
            {1,  7,  5}
        };
    
    cout<<obj.largestRectangularSubMatrixWithSum0(grid)<<endl;

    grid = {
            {1, -1}, 
            {-1, 1}
        };

    cout<<obj.largestRectangularSubMatrixWithSum0(grid)<<endl;
    return 0;
}