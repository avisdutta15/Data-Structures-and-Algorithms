#include <bits/stdc++.h>
using namespace std;

/*
    https://www.youtube.com/watch?v=nNlRAJ_jv_Y

    Problem Statement:
    ------------------
    Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest 
    sum of any subarray is minimized.
    Return the minimized largest sum of the split.
    A subarray is a contiguous part of the array.

    Examples:
    ---------
    Example 1:

    Input: nums = [7,2,5,10,8], k = 2
    Output: 18
    Explanation: There are four ways to split nums into two subarrays.
    The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.

    Example 2:
    Input: nums = [1,2,3,4,5], k = 2
    Output: 9
    Explanation: There are four ways to split nums into two subarrays.
    The best way is to split it into [1,2,3] and [4,5], where the largest sum among the two subarrays is only 9.

    Approach:
    ---------
        We can use BINARY SEARCH on answer (largest sum)
        -   If we can split the array with "mid" as the largest sum -> we can also split with larger sum
                goto left to minimise the largest sum (this is what is asked)
        -   If we cannot split the array with "mid" as the largest sum -> we cannot split with smaller sum
                goto right to find a valid sum



        Same as Book Allocation

    SEARCH SPACE : MAX Number ..... SUM Of All Numbers
*/

class Solution{
    private:
        bool arraySplitPossibleWithMidSum(vector<int> &A, int K, int targetSum){
            int chuncks = 1;
            int currentSum = 0;
            
            for(int i=0; i<A.size(); i++){
                if(currentSum + A[i] > targetSum){
                    currentSum = A[i];
                    chuncks++;
                    if(chuncks > K)
                        return false;
                }else{
                    currentSum += A[i];
                }
            }
            return true;
        }

    public:
        int splitArrayLargestSum(vector<int> &A, int K){
            if(K > A.size())
                return -1;

            int lo = *max_element(A.begin(), A.end());
            int hi = accumulate(A.begin(), A.end(), 0);
            int mid = 0;
            int largetSum = 0;

            while(lo <= hi){
                mid = lo + (hi - lo) / 2;
                if(arraySplitPossibleWithMidSum(A, K, mid)){
                    largetSum = mid;
                    hi = mid - 1;                               //minimise the largest sum
                }else{
                    lo = mid + 1;
                }
            }
            return largetSum;
        }
};

int main(){
    Solution obj1;
    vector<int> books = {7,2,5,10,8};
    cout<<obj1.splitArrayLargestSum(books, 2)<<endl;        //18

    books = {1, 2, 3, 4, 5};
    cout<<obj1.splitArrayLargestSum(books, 5)<<endl;        //5

    books = {1, 2, 3, 4, 5};
    cout<<obj1.splitArrayLargestSum(books, 1)<<endl;        // 15

    return 0;
}

