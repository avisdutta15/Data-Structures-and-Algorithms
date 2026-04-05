#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    You are given an integer finalSum. Split it into a sum of a maximum number of unique positive even integers.

    For example, given finalSum = 12, the following splits are valid (unique positive even integers summing up to finalSum):
    (12), (2 + 10), (2 + 4 + 6), and (4 + 8).
    Among them, (2 + 4 + 6) contains the maximum number of integers. 
    Note that finalSum cannot be split into (2 + 2 + 4 + 4) as all the numbers should be unique.

    Return a list of integers that represent a valid split containing a maximum number of integers. 
    If no valid split exists for finalSum, return an empty list. You may return the integers in any order.
    

    Examples:
    ---------
    Input: finalSum = 12
    Output: [2,4,6]
    Explanation: The following are valid splits: (12), (2 + 10), (2 + 4 + 6), and (4 + 8).
    (2 + 4 + 6) has the maximum number of integers, which is 3. Thus, we return [2,4,6].
    Note that [2,6,4], [6,2,4], etc. are also accepted.

    Input: finalSum = 7
    Output: []
    Explanation: There are no valid splits for the given finalSum.
    Thus, we return an empty array.

    Input: finalSum = 28
    Output: [6,8,2,12]
    Explanation: The following are valid splits: (2 + 26), (6 + 8 + 2 + 12), and (4 + 24). 
    (6 + 8 + 2 + 12) has the maximum number of integers, which is 4. Thus, we return [6,8,2,12].
    Note that [10,2,4,12], [6,2,4,16], etc. are also accepted.

    Constraints:
        1 <= finalSum <= 10^10

    Approach:
    ----------
    1. If we look closely, when we start recursion to explore all the subsets of even numbers,
    we can see that the recursion tree will go like this ->
        2
        2 + 4
        2 + 4 + 6
    
    and then it will backtrack as it reached the sum.
    So this is a skewed recursion tree. We dont need to explore other paths as this leaf has 
    the maximum size. Other nodes like 2+10, 4+8, 12 are smaller than this list.
    So we change the function signature from void to bool. Once the target is reached, return true.
    else return false.
*/

class Solution {
private:
    bool solve(long long i, vector<long long> &combination, long long target){
        if(target == 0)
            return true;
        
        //overshoot
        if(target < 0 || i>target)
            return false;

        if(target >= i){
            combination.push_back(i);
            bool include = solve(i+2, combination, target - i);
            if(include == true)
                return true;
            combination.pop_back();
        }        

        bool exclude = solve(i+2, combination, target);
        return exclude;
    }
public:
    vector<long long> maximumEvenSplit(long long finalSum) {
        if(finalSum%2!=0)
            return vector<long long>();

        vector<long long> combination;
        long long i = 2;
        solve(i, combination, finalSum);
        return combination;
    }
};

/*
LeetCode categorizes this as a backtracking problem sometimes to trick you, but this is actually a pure Greedy Math problem.
Think about the goal: We want the maximum possible number of even integers.

To get the most numbers, we must greedily use the smallest possible numbers.

The Greedy Strategy:
    1. Keep subtracting the smallest unique evens ($2, 4, 6, 8...$) from finalSum and adding them to your array.
    2. Stop when the remaining finalSum becomes smaller than the next even number you want to add.
    3. If you add the remaining finalSum as a brand new number, it would be a duplicate of something you already added. 
       So instead, just add whatever is left to the very last number in your array.
       
Example Walkthrough: 
    finalSum = 28
    1. Take 2. (Remaining: 26). Array: [2]
    2. Take 4. (Remaining: 22). Array: [2, 4]
    3. Take 6. (Remaining: 16). Array: [2, 4, 6]
    4. Take 8. (Remaining: 8). Array: [2, 4, 6, 8]
    5. Next even number is 10. 
    But our remaining sum is 8. We can't use 10!
    If we just append the remaining 8 as a new number, our array is [2, 4, 6, 8, 8] (Violates the unique rule!)
    
    The Trick: Add the remaining 8 to the last number in the array. 8 + 8 = 16.
    Final Array: [2, 4, 6, 16]. (Sums to 28, all unique, maximum possible splits).
*/

class Solution2 {
public:
    vector<long long> maximumEvenSplit(long long finalSum) {
        // A set of positive even integers cannot sum to an odd number
        if (finalSum % 2 != 0) {
            return {};
        }

        vector<long long> result;
        long long current_even = 2;

        // Keep taking the smallest available even number 
        // AS LONG AS what's left over is enough to be a larger, unique even number
        while (finalSum >= current_even) {
            result.push_back(current_even);
            finalSum -= current_even;
            current_even += 2;
        }

        // We broke the loop because the remaining finalSum is strictly less than 
        // our next required current_even. 
        // We must add the leftover sum to the LAST element in our result array 
        // to maintain uniqueness.
        if (finalSum > 0) {
            result.back() += finalSum;
        }

        return result;
    }
};