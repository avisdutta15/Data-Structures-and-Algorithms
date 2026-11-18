#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: (LeetCode 256 - Paint House)
    ------------------
    There are n houses in a row. Each house can be painted with one of 3 colors:
    Red (0), Blue (1), Green (2).
    The cost of painting each house with each color is given in costs[][].
    No two adjacent houses can have the same color.

    Find the minimum cost to paint all houses.

    Examples:
    --------
    Input: costs = [[17,2,17],[16,16,5],[14,3,19]]
    Output: 10
    Explanation: Paint house 0 Blue(2), house 1 Green(5), house 2 Blue(3) = 2+5+3 = 10.

    Input: costs = [[7,6,2]]
    Output: 2

    Constraints:
    ------------
    - costs.length == n
    - costs[i].length == 3
    - 1 <= n <= 100
    - 1 <= costs[i][j] <= 20

    Approach:
    ---------
    State: (house index, color of this house).
    Constraint: color of house i != color of house i-1.

    Intuition:
    ----------
    "If I decide to paint house i with color C, what's the cheapest way to 
    paint all houses 0..i?"

    The answer: cost of painting house i with C + cheapest way to paint houses 0..i-1,
    given that house i-1 must NOT be color C.

    So for house i painted Red:
      dp[i][Red] = costs[i][Red] + min(dp[i-1][Blue], dp[i-1][Green])
    
    For house i painted Blue:
      dp[i][Blue] = costs[i][Blue] + min(dp[i-1][Red], dp[i-1][Green])

    For house i painted Green:
      dp[i][Green] = costs[i][Green] + min(dp[i-1][Red], dp[i-1][Blue])

    We ask: "what's the cheapest color for the previous house, given that 
    it can't be the same as my current color?" That's the min of the other 
    two colors' dp values.

    Walkthrough with costs = [[17,2,17],
                              [16,16,5],
                              [14,3,19]]:
    -----------------------------------------------------------
    House 0 (base case — no previous house, just pay the cost):
      dp[0][R] = 17,  dp[0][B] = 2,  dp[0][G] = 17

    House 1 (look at all options for house 0 with different color):
      dp[1][R] = 16 + min(dp[0][B], dp[0][G]) = 16 + min(2, 17) = 18
      dp[1][B] = 16 + min(dp[0][R], dp[0][G]) = 16 + min(17, 17) = 33
      dp[1][G] = 5  + min(dp[0][R], dp[0][B]) = 5  + min(17, 2) = 7

    House 2 (look at all options for house 1 with different color):
      dp[2][R] = 14 + min(dp[1][B], dp[1][G]) = 14 + min(33, 7) = 21
      dp[2][B] = 3  + min(dp[1][R], dp[1][G]) = 3  + min(18, 7) = 10  ← MIN
      dp[2][G] = 19 + min(dp[1][R], dp[1][B]) = 19 + min(18, 33) = 37

    Answer = min(dp[2][R], dp[2][B], dp[2][G]) = min(21, 10, 37) = 10 ✓

    Path: house 2 Blue(3) ← house 1 Green(5) ← house 0 Blue(2) = 3+5+2 = 10

    Recurrence:
        solve(i, color):
            if i == n: return 0      // no more houses
            // Try all colors for next house that are different from current color
            return costs[i][color] + min(solve(i+1, otherColor1), solve(i+1, otherColor2))

        Answer: min(solve(0, 0), solve(0, 1), solve(0, 2))

    Alternatively (backwards):
        solve(i, color):
            if i == 0: return costs[0][color]   // base case: first house
            // This house is painted 'color'. Previous house must be different.
            return costs[i][color] + min(solve(i-1, otherColor1), solve(i-1, otherColor2))

        Answer: min(solve(n-1, 0), solve(n-1, 1), solve(n-1, 2))

    Walkthrough with matrix diagrams:
    -----------------------------------------------------------
    costs = [[17,2,17],[16,16,5],[14,3,19]]

    Cost Matrix:          DP Matrix (dp[i][color] = min cost to paint houses 0..i):
          R   B   G              R    B    G
    H0 [ 17,  2, 17 ]     H0 [ 17,   2,  17 ]   ← base case: just the cost itself
    H1 [ 16, 16,  5 ]     H1 [ 18,  33,   7 ]   ← explained below
    H2 [ 14,  3, 19 ]     H2 [ 21,  10,  37 ]   ← answer = min of this row = 10

    How dp[1][R] = 18:
      Paint house 1 Red(16). Previous house can be Blue(2) or Green(17).
      dp[1][R] = 16 + min(dp[0][B], dp[0][G]) = 16 + min(2, 17) = 18

    How dp[1][B] = 33:
      Paint house 1 Blue(16). Previous house can be Red(17) or Green(17).
      dp[1][B] = 16 + min(dp[0][R], dp[0][G]) = 16 + min(17, 17) = 33

    How dp[1][G] = 7:
      Paint house 1 Green(5). Previous house can be Red(17) or Blue(2).
      dp[1][G] = 5 + min(dp[0][R], dp[0][B]) = 5 + min(17, 2) = 7

    How dp[2][R] = 21:
      dp[2][R] = 14 + min(dp[1][B], dp[1][G]) = 14 + min(33, 7) = 21

    How dp[2][B] = 10:
      dp[2][B] = 3 + min(dp[1][R], dp[1][G]) = 3 + min(18, 7) = 10  ← ANSWER

    How dp[2][G] = 37:
      dp[2][G] = 19 + min(dp[1][R], dp[1][B]) = 19 + min(18, 33) = 37

    Answer = min(dp[2][R], dp[2][B], dp[2][G]) = min(21, 10, 37) = 10
    Path: house 2 Blue(3) ← house 1 Green(5) ← house 0 Blue(2) = 3+5+2 = 10

    Time: O(n * 3) = O(n)
    Space: O(n * 3) for memo, O(1) for space-optimized.
*/

// ============================================================================
// Solution 1: Recursion
// Time: O(2^n), Space: O(n)
// ============================================================================
class Solution1 {
private:
    int solve(vector<vector<int>>& costs, int i, int color, int n) {
        // Base case: first house
        if (i == 0) 
            return costs[0][color];

        // Try all colors for previous house that differ from current
        int minPrev = INT_MAX;
        for (int prevColor = 0; prevColor < 3; prevColor++) {
            if (prevColor != color) {
                minPrev = min(minPrev, solve(costs, i - 1, prevColor, n));
            }
        }

        // cost to color this house + min cost of previous house with different color
        return costs[i][color] + minPrev;
    }

public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        return min({solve(costs, n - 1, 0, n),      // last house colored with RED
                    solve(costs, n - 1, 1, n),      // last house colored with GREEN
                    solve(costs, n - 1, 2, n)});    // last house colored with BLUE
    }
};

// ============================================================================
// Solution 2: Memoization
// Time: O(n * 3), Space: O(n * 3)
// ============================================================================
class Solution2 {
private:
    int solve(vector<vector<int>>& costs, int i, int color, int n,
              vector<vector<int>>& dp) {
        if (i == 0) 
            return costs[0][color];
        if (dp[i][color] != -1) 
            return dp[i][color];

        int minPrev = INT_MAX;
        for (int prevColor = 0; prevColor < 3; prevColor++) {
            if (prevColor != color) {
                minPrev = min(minPrev, solve(costs, i - 1, prevColor, n, dp));
            }
        }

        dp[i][color] = costs[i][color] + minPrev;
        return dp[i][color];
    }

public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();

        // State: house index, color of that house
        vector<vector<int>> dp(n, vector<int>(3, -1));
        return min({solve(costs, n - 1, 0, n, dp),      // last house colored with RED
                    solve(costs, n - 1, 1, n, dp),      // last house colored with GREEN
                    solve(costs, n - 1, 2, n, dp)});    // last house colored with BLUE
    }
};

// ============================================================================
// Solution 3: Bottom-Up
// Time: O(n * 3), Space: O(n * 3)
// ============================================================================
// Direct translation:
//   solve(i, color):
//     if i == 0: return costs[0][color]
//     return costs[i][color] + min(solve(i-1, otherColor1), solve(i-1, otherColor2))
//
// Fill from house 0 to house n-1 (each house depends on previous house).
class Solution3 {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        vector<vector<int>> dp(n, vector<int>(3, 0));

        for (int i = 0; i < n; i++) {
            for (int color = 0; color < 3; color++) {
                // Base case: first house
                if (i == 0) {
                    dp[i][color] = costs[0][color];
                }
                // Recursive case: costs[i][color] + min of previous house with different color
                else {
                    int minPrev;
                    if (color == 0)      
                        minPrev = min(dp[i-1][1], dp[i-1][2]);
                    else if (color == 1) 
                        minPrev = min(dp[i-1][0], dp[i-1][2]);
                    else                 
                        minPrev = min(dp[i-1][0], dp[i-1][1]);

                    dp[i][color] = costs[i][color] + minPrev;
                }
            }
        }

        // Answer: min(dp[n-1][0], dp[n-1][1], dp[n-1][2])
        return min({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
    }
};

// ============================================================================
// Solution 4: Space Optimized O(1) extra space
// Time: O(n * 3), Space: O(1)
// ============================================================================
// dp[i] only depends on dp[i-1]. Just keep 3 variables for previous row.
class Solution4 {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        int prevR = costs[0][0], prevB = costs[0][1], prevG = costs[0][2];

        for (int i = 1; i < n; i++) {
            int currR = costs[i][0] + min(prevB, prevG);
            int currB = costs[i][1] + min(prevR, prevG);
            int currG = costs[i][2] + min(prevR, prevB);
            prevR = currR;
            prevB = currB;
            prevG = currG;
        }

        return min({prevR, prevB, prevG});
    }
};


int main() {
    Solution1 recursion;
    Solution2 memo;
    Solution3 bottomUp;
    Solution4 optimized;

    vector<vector<int>> costs = {
        {17, 2, 17},
        {16, 16, 5},
        {14, 3, 19}
    };

    cout << "Recursion:       " << recursion.minCost(costs) << endl;  // 10
    cout << "Memoization:     " << memo.minCost(costs) << endl;       // 10
    cout << "Bottom-Up:       " << bottomUp.minCost(costs) << endl;   // 10
    cout << "Space Optimized: " << optimized.minCost(costs) << endl;  // 10

    return 0;
}
