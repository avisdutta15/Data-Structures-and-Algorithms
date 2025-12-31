#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array and a positive integer k, find the first negative integer for each window (contiguous subarray)
    of size k. If a window does not contain a negative integer, then print 0 for that window.

	Examples:
	---------
	Input: arr[] = [-8, 2, 3, -6, 1] , k = 2
    Output: [-8, 0, -6, -6]
    Explanation: First negative integer for each window of size 2
                            [-8, 2] = -8
                            [2, 3]= 0 (does not contain a negative integer)
                            [3, -6] = -6
                            [-6, 10] = -6

    Input: arr[] = [12, -1, -7, 8, -15, 30, 16, 28], k = 3
    Output: [-1, -1, -7, -15, -15, 0]
    Explanation: First negative integer for each window of size 3
                            [ 12, -1, -7] = -1
                            [-1,-7, 8] = -1
                            [-7, 8, -15] = -7
                            [8, -15, 30] = -15
                            [-15, 30, 16] = -15
                            [30, 16, 28] = 0

    Approach:
	---------
    Sliding window
*/

class Solution {
public:
    vector<int> firstNegativeOfWindowSizeK(vector<int>& A, int K) {

        vector<int> firstNegatives;
        queue<int> Q;
        //process the first window
        for (int i = 0; i < K; i++) {
            if (A[i] < 0)
                Q.push(i);
        }
        if (Q.size() == 0)
            firstNegatives.push_back(0);
        else
            firstNegatives.push_back(A[Q.front()]);

        //process rest of the windows
        for (int i = K; i < A.size(); i++) {
            //delete the element which is out of the window
            if (Q.size()!=0 && Q.front() == i - K)
                Q.pop();

            //insert new element into the window
            if (A[i] < 0)
                Q.push(i);

            //process the window ending at index i
            if (Q.size() == 0)
                firstNegatives.push_back(0);
            else
                firstNegatives.push_back(A[Q.front()]);
        }
        return firstNegatives;
    }
};

int main() {
    Solution obj;
    vector<int> A = { -8, 2, 3, -6, 1 };
    auto firstNegatives = obj.firstNegativeOfWindowSizeK(A, 2);
    for (auto i : firstNegatives) {
        cout << i << " ";
    }
    cout << endl; 
    A = { 12, -1, -7, 8, -15, 30, 16, 28 };
    firstNegatives = obj.firstNegativeOfWindowSizeK(A, 3);
    for (auto i : firstNegatives) {
        cout << i << " ";
    }
    cout << endl;
    A = { 2, 3 };
    firstNegatives = obj.firstNegativeOfWindowSizeK(A, 1);
    for (auto i : firstNegatives) {
        cout << i << " ";
    }

    return 0;
}