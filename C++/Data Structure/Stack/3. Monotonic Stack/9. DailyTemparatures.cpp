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
	Problem Statement:
	-----------------
	Given an array of integers temperatures represents the daily temperatures, return an array answer 
    such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. 
    
    If there is no future day for which this is possible, keep answer[i] == 0 instead.


	Examples:
	---------
	Input: temperatures = [73,74,75,71,69,72,76,73]
    Output: [1,1,4,2,1,1,0,0]

	Input: temperatures = [30,40,50,60]
    Output: [1,1,1,0]

    Input: temperatures = [30,60,90]
    Output: [1,1,0]

    Constraints:
    -----------
    1 <= temperatures.length <= 10^5
    30 <= temperatures[i] <= 100

	Approach:
	--------
    keep a stack. (monotonic decreasing)    [69, 72, 76]
    stack stores the indices.   
    Start from n-1 to 0
        while temp > temp[stack.top()]
            pop
        for a day with temp < temp[stack.top()]
            the number of days = stack.top() - i;
        push i to stack       
*/

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int N = temperatures.size();
        if(N == 0)
            return vector<int>();

        vector<int> daysToWaitForWarmerTemparature(temperatures.size(), 0);
        stack<int> stack; //monotonic decreasing stack. stack has indices

        for(int i = N-1; i>=0; i--){
            while(!stack.empty() && temperatures[i] >= temperatures[stack.top()])
                stack.pop();
            
            if(stack.empty())
                daysToWaitForWarmerTemparature[i] = 0;
            else
                daysToWaitForWarmerTemparature[i] = stack.top() - i;
            stack.push(i);
        }

        return daysToWaitForWarmerTemparature;
    }
};