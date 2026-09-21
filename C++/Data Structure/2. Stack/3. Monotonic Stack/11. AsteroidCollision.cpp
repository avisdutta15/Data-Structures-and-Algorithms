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
    https://www.youtube.com/watch?v=_eYGqw_VDR4
    
    Problem Statement:
    -----------------
    We are given an array asteroids of integers representing asteroids in a row. 
    The indices of the asteroid in the array represent their relative position in space.
    
    For each asteroid, the absolute value represents its size, and the sign represents 
    its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.
    
    Find out the state of the asteroids after all collisions. If two asteroids meet, 
    the smaller one will explode. If both are the same size, both will explode. 
    Two asteroids moving in the same direction will never meet.

    Examples:
    --------- 
    Input: asteroids = [5,10,-5]
    Output: [5,10]
    Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.

    Input: asteroids = [8,-8]
    Output: []
    Explanation: The 8 and -8 collide exploding each other.

    Input: asteroids = [10,2,-5]
    Output: [10]
    Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.

    Input: asteroids = [3,5,-6,2,-1,4]​​​​​​​
    Output: [-6,2,4]
    Explanation: The asteroid -6 makes the asteroid 3 and 5 explode, and then continues 
    going left. On the other side, the asteroid 2 destroys -1. 
    Since 2 and 4 are both moving right, they never collide.

    Constraints:
    ------------
    2 <= asteroids.length <= 10^4
    -1000 <= asteroids[i] <= 1000
    asteroids[i] != 0


    Approach: 
    --------
    Use Stack for saving the final state.
    Time Complexity : O(n)
    Space Complexity : O(n)

*/

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        int N = asteroids.size();
        if (N == 0)
            return vector<int>();

        stack<int> stack;
        for (int i = 0; i < N; i++) {
            if (asteroids[i] > 0)
                stack.push(asteroids[i]);
            else {
                // if both are of different size then smaller will explode
                // Case 1: [5, 4, 2]  asteroids[i] = -3
                //         2 will explode
                while (!stack.empty() && stack.top() > 0 && stack.top() < abs(asteroids[i]))
                    stack.pop();

                // if both are of different size then smaller will explode
                // Case 2: [5, 4] asteroids[i] = -3
                //         -3 will explode
                if (!stack.empty() && stack.top() > 0 && stack.top() > abs(asteroids[i]))
                    continue;

                // if both are of same size then both will explode
                // Case 3: [5, 3] asteroids[i] = -3
                if (!stack.empty() && stack.top() > 0 && stack.top() >= abs(asteroids[i])) {
                    stack.pop();
                    continue;
                }

                // else they will survive the crash and be on the final state
                // Case 3: []   asteroids[i] = -3
                //    or   [-2] asteroids[i] = -3
                stack.push(asteroids[i]);
            }
        }

        vector<int> finalState;
        while (!stack.empty()) {
            finalState.push_back(stack.top());
            stack.pop();
        }

        reverse(finalState.begin(), finalState.end());

        return finalState;
    }
};

int main() {
    Solution obj;
    vector<int> A = { 3,5,-6,2,-1,4 };
	auto finalState = obj.asteroidCollision(A);
	for (auto i : finalState) cout << i << "";
    return 0;
}