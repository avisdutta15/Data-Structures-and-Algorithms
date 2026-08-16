#include <algorithm>
#include <iostream>
#include <climits>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement:
    ------------------
    The thief has found himself a new place for his thievery again. All houses in this place
    form a binary tree. If two directly-linked houses were broken into on the same night,
    it will automatically contact the police.

    Given the root of the binary tree, return the maximum amount of money the thief can rob
    without alerting the police.

    Examples:
    --------
    Input:
            3
           / \
          2   3
           \   \
            3   1
    Output: 7
    Explanation: Rob 3 (root) + 3 (left grandchild) + 1 (right grandchild) = 7

    Input:
            3
           / \
          4   5
         / \   \
        1   3   1
    Output: 9
    Explanation: Rob 4 + 5 = 9 (skip root, rob both children)

    Constraints:
    ------------
    - The number of nodes in the tree is in the range [1, 10^4].
    - 0 <= Node.val <= 10^4

    Approach 1 (Naive - TLE):
    -------------------------
    At each node, two choices:
    - Rob this node: take val + rob grandchildren (skip children)
    - Don't rob this node: rob left child + rob right child

    Problem: Exponential time O(2^N). Overlapping subproblems — rob(node->left) is computed
    both when we "skip this node" AND when we "rob this node" (as part of grandchild calc).
    Same subtrees get solved repeatedly.

    Approach 2 (Optimal - Pair return):
    ------------------------------------
    Instead of recomputing subtrees, return a pair {rob, skip} from each node in one pass.
    - robThis: rob this node + skip both children (take their "skip" values)
    - skipThis: don't rob this node, take the best choice from each child

    This eliminates overlapping subproblems — each node is visited exactly once.

    Recurrence:
        dfs(node):
            if node == null: return {0, 0}

            {leftRob, leftSkip}   = dfs(node->left)
            {rightRob, rightSkip} = dfs(node->right)

            robThis  = node->val + leftSkip + rightSkip
            skipThis = max(leftRob, leftSkip) + max(rightRob, rightSkip)

            return {robThis, skipThis}

    Time: O(N), Space: O(H) where H = height of tree.
*/

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int val;
};

// Solution 1: Naive Recursion (TLE for large inputs)
// At each node: rob this + grandchildren OR skip this + rob children
// Problem: overlapping subproblems, exponential time O(2^N)
class Solution1 {
public:
    int rob(TreeNode* node) {
        if (!node) return 0;

        // Option 1: Rob this node, skip children, take grandchildren
        int robThis = node->val;
        if (node->left)
            robThis += rob(node->left->left) + rob(node->left->right);
        if (node->right)
            robThis += rob(node->right->left) + rob(node->right->right);

        // Option 2: Don't rob this node, take best from children
        int skipThis = rob(node->left) + rob(node->right);

        // return the maximum by either robbing or skipping this node
        return max(robThis, skipThis);
    }
};

// Solution 2: Optimal — return {rob, skip} pair from each node
// Each node visited exactly once. O(N) time.
class Solution2 {
private:
    // Returns {rob this node, don't rob this node}
    pair<int, int> dfs(TreeNode* node) {
        if (!node) return {0, 0};

        auto [leftRob, leftSkip] = dfs(node->left);
        auto [rightRob, rightSkip] = dfs(node->right);

        // Rob this node: can't rob children, take their "skip" values
        int robThis = node->val + leftSkip + rightSkip;

        // Don't rob this node: take the best choice from each child
        int skipThis = max(leftRob, leftSkip) + max(rightRob, rightSkip);

        return {robThis, skipThis};
    }

public:
    int rob(TreeNode* root) {
        auto [robbed, notRobbed] = dfs(root);
        return max(robbed, notRobbed);
    }
};


int main() {
    Solution1 naive;
    Solution2 optimal;

    // Build tree:
    //        3
    //       / \
    //      2   3
    //       \   \
    //        3   1
    TreeNode* root = new TreeNode{nullptr, nullptr, 3};
    root->left = new TreeNode{nullptr, nullptr, 2};
    root->right = new TreeNode{nullptr, nullptr, 3};
    root->left->right = new TreeNode{nullptr, nullptr, 3};
    root->right->right = new TreeNode{nullptr, nullptr, 1};

    cout << "Naive - Max Rob: " << naive.rob(root) << endl;    // Expected: 7
    cout << "Optimal - Max Rob: " << optimal.rob(root) << endl; // Expected: 7

    // Cleanup
    delete root->left->right;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
