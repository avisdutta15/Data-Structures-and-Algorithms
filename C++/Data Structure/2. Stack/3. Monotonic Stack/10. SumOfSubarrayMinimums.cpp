#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <string>

using namespace std;

/*
    https://www.youtube.com/watch?v=HRQB7-D2bi0
    Problem Statement:
    -----------------
    Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. 
    Since the answer may be large, return the answer modulo 10^9 + 7.

    Examples:
    --------- 
    Input: arr = [3,1,2,4]
    Output: 17
    Explanation: 
    Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
    Minimums are   3,   1,   2,   4,    1,     1,     2,      1,       1,        1.
    Sum is 17.

    Input: arr = [11,81,94,43,3]
    Output: 444

    Constraints:
    ------------
    1 <= arr.length <= 3 * 10^4
    1 <= arr[i] <= 3 * 10^4


    Approach 1: 
    ------------
    Find all subarrays.
        For each subarray, maintain the minimums.
        Sum them up.

    Approach 2:
    -----------
    For every element, find the number of subarrays for which this element is the minimum.
    This element contributes its value to the sum, exactly as many times as the number of such subarrays.
    To find the number of subarrays for which a particular element X is the minimum,
    we need to find the nearest smaller element to the left (PSER) and nearest smaller element to the right (NSER).

    How to handle duplicates?
    -------------------------
    If we for both PSEL and NSER, if the current element is < to the top of the stack, pop.
     0  1  2  3  4
    [2, 6, 2, 4, 2]
           i
    
    Left and Right Boundary is strictly smaller elements to the left and right : 
        while (!stack.empty() && A[i] < A[stack.top()])

    For the i = 0 A[i] = 2. PSEL = -1, NSER = 5. (no element).
    2 [6, 2, 4, 2]
    Subarrays with i=0 A[i] = 2 as minimum : 0-(-1) * (5-0) = 1 * 5 = 5:
    2
    2, 6
    2, 6, 2         <- Duplicate! (with above one i=2)
    2, 6, 2, 4      <- Duplicate! (with above one i=2)
    2, 6, 2, 4, 2   <- Duplicate! (with above one i=2)

    For the i = 2. A[i] = 2. PSEL = -1, NSER = 5. (no element). 
    [2, 6]  2 [4, 2]
    Subarrays with i=2 A[i] = 2 as minimum : 2-(-1) * (5-2) = 3 * 3 = 9:
    2, 6, 2         <- Duplicate! (with above one i=0)
    2, 6, 2, 4      <- Duplicate! (with above one i=0)
    2, 6, 2, 4, 2   <- Duplicate! (with above one i=0)
    6, 2
    6, 2, 4
    6, 2, 4, 2
    2
    2, 4
    2, 4, 2

    We find duplicate subarrays because we are considering the duplicate elements as well in our calculation.
    [2, 6, 2] 
    [2, 6, 2, 4]
    [2, 6, 2, 4, 2]
    All these are same subarrays with 2 as minimum. But they got counted twice.
    Once for i=0 and i=2.

    This is wrong.

    ------Fix!-------
    When we find the NSER, we should consider the current element to be < to the top of the stack.
    When we find the PSEL, we should consider the current element to be <= to the top of the stack.

    Left Boundary is strictly smaller or equal elements to the left:
        while (!stack.empty() && A[i] <= A[stack.top()])
        
    Right Boundary is strictly smaller elements to the left:
        while (!stack.empty() && A[i] < A[stack.top()])
    
    This ensures that we are counting the duplicate elements only once.

    For the i = 0 A[i] = 2. PSEL = -1, NSER = 2. (because A[2] is equal to 2. It acts as a hard boundary!).
    2 [6], 2, 4, 2
    Subarrays with i=0 A[i] = 2 as minimum : 0-(-1) * (2-0) = = 1 * 2 = 2:
    2
    2, 6

    For the i = 2. A[i] = 2. PSEL = -1, NSER = 4. (The loop stops at index 4 because A[4] is equal to 2. 
    It acts as a hard boundary!).
    [2 6] 2 [4, 2]
    Subarrays with i=2 A[i] = 2 as minimum : (2 - (-1)) * (4 - 2) = 3 * 2 = 6:
    [2, 6, 2]
    [2, 6, 2, 4]
    [6, 2]
    [6, 2, 4]
    [2] (The 2 at i=2)
    [2, 4]


    For i = 4, A[4] = 2. PSEL = -1 (Expands past i=2 and i=0 all the way to -1). NSER = 5 (End of array)
    Subarrays with i=4 as minimum: (4 - (-1)) * (5 - 4) = 5 * 1 = 5
    [2, 6, 2, 4, 2] 
    [6, 2, 4, 2] 
    [2, 4, 2] 
    [4, 2] 
    [2] (The 2 at i=4)
    
    The number of subarrays = (i - PSER) * (NSER - i)
    
    Time Complexity : O(n)    
*/

class Solution1 {
public:
    int sumSubarrayMins(vector<int>& A) {
        int sum = 0;
        int mod = 1e9 + 7;

        for (int i = 0; i < A.size(); i++) {
            int minVal = A[i];

            //subarray A[i:j]
            for(int j=i; j<A.size(); j++)
            {
                //update the minimum value of the subarray A[i:j]
                minVal = min(minVal, A[j]);

                //add it to the global sum
                sum = (sum + minVal) % mod;
            }
        }
        return sum;
    }
};

class Solution2 {
private:
    vector<int> getPreviousSmallerElementToLeft(vector<int>& A) {
        vector<int> psel(A.size(), -1);
        stack<int> stack;

        //left -> 0 -> n-1
        //smaller -> monotonically increasing stack
        for (int i = 0; i <= A.size() - 1; i++) {
            while (!stack.empty() && A[i] < A[stack.top()])
                stack.pop();

            if (stack.empty())
                psel[i] = -1;
            else
                psel[i] = stack.top();
            stack.push(i);
        }

        return psel;
    }

    vector<int> getNextSmallerElementToRight(vector<int>& A) {
        int N = A.size();
        vector<int> nser(N, -1);
        stack<int> stack;

        // right -> n-1 to 0
        // smaller -> monotonically increasing stack

        for (int i = N - 1; i >= 0; i--) {
            while (!stack.empty() && A[i] <= A[stack.top()])
                stack.pop();

            if (stack.empty())
                nser[i] = N;
            else
                nser[i] = stack.top();
            stack.push(i);
        }

        return nser;
    }

public:
    int sumSubarrayMins(vector<int>& A) {
        // For every element, ask the question,
        //  for how many subarrays will have this element as the minimum value?
        //  ans : left_bound * right_bound
        //        left_bound = number of contiguous elements > than this element to the left.   (i - PSEL)
        //        right_bound = number of contiguous elements > than this element to the right. (NSER - i)

        int sum = 0;
        int mod = 1e9 + 7;

        vector<int> PSEL = getPreviousSmallerElementToLeft(A);
        vector<int> NSER = getNextSmallerElementToRight(A);

        for (int i = 0; i < A.size(); i++) {
            int leftBound = i - PSEL[i];
            int rightBound = NSER[i] - i;

            long long totalWays = leftBound * rightBound;

            long long totalContribution = (A[i] * totalWays);
            sum = (sum + totalContribution) % (mod);
        }
        return sum;
    }
};

int main() {
    Solution2 obj;
    vector<int> A = { 3, 1, 2, 4 };
	cout << obj.sumSubarrayMins(A) << endl;
    return 0;
}