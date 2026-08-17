#include <algorithm>
#include <iostream>
#include <climits>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/*
    https://www.youtube.com/watch?v=vWW67t_a--8
    
    Problem Statement: (LeetCode 241 - Different Ways to Add Parentheses)
    ------------------
    Given a string expression of numbers and operators (+, -, *), return all
    possible results from computing all different ways to group numbers and operators.

    Examples:
    --------
    Input: expression = "2-1-1"
    Output: [0, 2]
    Explanation:
        ((2-1)-1) = 0
        (2-(1-1)) = 2

    Input: expression = "2*3-4*5"
    Output: [-34, -14, -10, -10, 10]
    Explanation:
        (2*(3-(4*5))) = -34
        ((2*3)-(4*5)) = -14
        ((2*(3-4))*5) = -10
        (2*((3-4)*5)) = -10
        (((2*3)-4)*5) = 10

    Constraints:
    ------------
    - 1 <= expression.length <= 20
    - expression consists of digits and '+', '-', '*'

    Approach:
    ---------
    This is a Divide and Conquer / MCM (Matrix Chain Multiplication) style problem.

    For each operator in the expression, split into:
    - Left sub-expression (everything before the operator)
    - Right sub-expression (everything after the operator)

    Recursively compute all results for left and right, then combine using the operator.

    Recurrence:
        solve(expr):
            if expr is a number: return [number]

            results = []
            for each operator at position i:
                leftResults  = solve(expr[0..i-1])
                rightResults = solve(expr[i+1..end])

                for each l in leftResults:
                    for each r in rightResults:
                        results.add(l op r)

            return results

    This is exactly the MCM pattern: try every possible split point.

    Recursion Tree for "2-1-1":
    ----------------------------
                                solve("2-1-1")
                        /                           \
              split at '-' (idx 1)              split at '-' (idx 3)
              /            \                    /            \
        solve("2")    solve("1-1")          solve("2-1")   solve("1")
          [2]          /       \                /       \       [1]
                 solve("1") solve("1")  solve("2") solve("1")
                   [1]        [1]         [2]        [1]
                   
        Left: [2], Right: [1-1=0]       Left: [2-1=1], Right: [1]
        Result: 2 - 0 = 2              Result: 1 - 1 = 0

    Final: [0, 2]

    Recursion Tree for "2*3-4*5" (partial — showing split points):
    ---------------------------------------------------------------
                           solve("2*3-4*5")
                     /           |            \
           split at '*'    split at '-'    split at '*'
             (idx 1)         (idx 3)         (idx 5)
            /      \        /      \        /      \
       solve("2") solve("3-4*5")  solve("2*3") solve("4*5")  solve("2*3-4") solve("5")
         [2]    [-17, -5]         [6]       [20]         [-2, 2]         [5]

       2*(-17)=-34              6-20=-14            (-2)*5=-10
       2*(-5)=-10                                    (2)*5=10

    Final: [-34, -10, -14, -10, 10]

    Time: O(Catalan(n)) where n = number of operators. Each split produces a binary tree.
    Space: O(Catalan(n)) for storing all results.
*/

// ============================================================================
// Solution 1: Recursion (Divide and Conquer)
// Time: O(Catalan(n) * n), Space: O(Catalan(n))
// ============================================================================
class Solution1 {
public:
    vector<int> diffWaysToCompute(string expression) {
        return solve(expression);
    }

private:
    vector<int> solve(string expr) {
        vector<int> results;

        for (int i = 0; i < expr.size(); i++) {
            char c = expr[i];

            // If it's an operator, split here
            if (c == '+' || c == '-' || c == '*') {
                // Divide: solve left and right sub-expressions
                vector<int> leftResults = solve(expr.substr(0, i));
                vector<int> rightResults = solve(expr.substr(i + 1));

                // Conquer: combine all left and right results with this operator
                for (int l : leftResults) {
                    for (int r : rightResults) {
                        if (c == '+') 
                            results.push_back(l + r);
                        else if (c == '-') 
                            results.push_back(l - r);
                        else 
                            results.push_back(l * r);
                    }
                }
            }
        }

        // Base case: no operator found → entire expr is a number
        if (results.empty()) {
            results.push_back(stoi(expr));
        }

        return results;
    }
};

// ============================================================================
// Solution 2: Memoization
// Time: O(Catalan(n) * n), Space: O(Catalan(n))
// ============================================================================
// Cache results for each sub-expression string to avoid recomputation.
class Solution2 {
private:
    vector<int> solve(string expr, unordered_map<string, vector<int>>& memo) {
        if (memo.find(expr) != memo.end()) return memo[expr];

        vector<int> results;

        for (int i = 0; i < expr.size(); i++) {
            char c = expr[i];

            if (c == '+' || c == '-' || c == '*') {
                vector<int> leftResults = solve(expr.substr(0, i), memo);
                vector<int> rightResults = solve(expr.substr(i + 1), memo);

                for (int l : leftResults) {
                    for (int r : rightResults) {
                        if (c == '+') results.push_back(l + r);
                        else if (c == '-') results.push_back(l - r);
                        else results.push_back(l * r);
                    }
                }
            }
        }

        if (results.empty()) {
            results.push_back(stoi(expr));
        }

        memo[expr] = results;
        return results;
    }

public:
    vector<int> diffWaysToCompute(string expression) {
        // map [expression -> results vector]
        unordered_map<string, vector<int>> memo;
        return solve(expression, memo);
    }

};


int main() {
    Solution1 recursion;
    Solution2 memo;

    string expr1 = "2-1-1";
    auto res1 = recursion.diffWaysToCompute(expr1);
    cout << "Recursion [2-1-1]: ";
    for (int x : res1) cout << x << " ";
    cout << endl; // 0 2

    auto res2 = memo.diffWaysToCompute(expr1);
    cout << "Memo [2-1-1]:      ";
    for (int x : res2) cout << x << " ";
    cout << endl; // 0 2

    string expr2 = "2*3-4*5";
    auto res3 = memo.diffWaysToCompute(expr2);
    cout << "Memo [2*3-4*5]:    ";
    for (int x : res3) cout << x << " ";
    cout << endl; // -34 -14 -10 -10 10

    return 0;
}
