#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array of integers arr[] and an integer k, find the maximum possible sum among all contiguous 
    subarrays of size exactly k.
    A subarray is a sequence of consecutive elements from the original array. Return the maximum sum that 
    can be obtained from any such subarray of length k.

	Examples:
	---------
	Input  : arr[] = [100, 200, 300, 400],  k = 2
    Output : 700
    Explanation: We get maximum sum by adding subarray [300,400] of size 2

    Input  : arr[] = [1, 4, 2, 10, 23, 3, 1, 0, 20], k = 4 
    Output : 39
    Explanation: We get maximum sum by adding subarray [4, 2, 10, 23] of size 4.

    Input  : arr[] = [2, 3], k = 1
    Output : 3
    Explanation: The subarrays of size 1 are [2] and [3]. The maximum sum is 3.

    Approach:
	---------
    Sliding window
*/

class Solution {
public:
    int maxSumSubArrayOfSizeKType1(vector<int>& A, int K) {

        int maxSum = INT_MIN;
        int subarraySum = 0;
        
        int start = 0, end = 0;
        while(end < A.size()){
            subarraySum = subarraySum + A[end];

            if (end - start + 1 < K) {
                end++;
            }
            else if (end - start + 1 == K) {
                maxSum = max(maxSum, subarraySum);
                subarraySum = subarraySum - A[start];
                start++;
                end++;
            }
        }
        return maxSum;
    }

    int maxSumSubArrayOfSizeKType2(vector<int>& A, int K) {
        if (A.size() == 0) return 0;

        int maxSum = INT_MIN;
        int subarraySum = 0;

        //process the first window
        for (int i = 0; i < K; i++) {
            subarraySum = subarraySum + A[i];
        }
        maxSum = max(maxSum, subarraySum);

        //process rest of the array
        for (int i = K; i < A.size(); i++) {
            subarraySum = subarraySum - A[i - K];
            subarraySum = subarraySum + A[i];
            maxSum = max(maxSum, subarraySum);
        }
        return maxSum;
    }
};

int main() {
    Solution obj;
    vector<int> A = { 100, 200, 300, 400 };
    cout << obj.maxSumSubArrayOfSizeKType2(A, 2) << endl;

    A = { 1, 4, 2, 10, 23, 3, 1, 0, 20 };
    cout << obj.maxSumSubArrayOfSizeKType2(A, 4) << endl;

    A = { 2, 3 };
    cout << obj.maxSumSubArrayOfSizeKType2(A, 1) <<endl;
    return 0;
}