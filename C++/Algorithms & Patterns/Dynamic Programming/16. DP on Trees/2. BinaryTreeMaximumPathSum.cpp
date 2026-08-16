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
    Given the root of a binary tree, return the maximum path sum of any non-empty path.

    A path is a sequence of nodes where each pair of adjacent nodes has an edge connecting them.
    A node can only appear in the path at most once. The path does not need to pass through the root.

    Examples:
    --------
    Input: root = [1,2,3]
            1
           / \
          2   3
    Output: 6
    Explanation: The optimal path is 2 -> 1 -> 3 with sum 2 + 1 + 3 = 6.

    Input: root = [-10,9,20,null,null,15,7]
           -10
           /  \
          9    20
              /  \
             15   7
    Output: 42
    Explanation: The optimal path is 15 -> 20 -> 7 with sum 15 + 20 + 7 = 42.

    Constraints:
    ------------
    - The number of nodes in the tree is in the range [1, 3 * 10^4].
    - -1000 <= Node.val <= 1000

    Approach :
    ----------
    Same DP on Trees pattern as Diameter:
    - At each node, compute the max gain from left and right subtrees.
    - Only take a branch if it contributes positively (max(0, branch)).
    - Global update: val + leftGain + rightGain (path using both branches through this node).
    - Return to parent: val + max(leftGain, rightGain) (can only extend one direction upward).

    Recurrence:
        maxGain(node):
            if node == null: return 0
            L = max(0, maxGain(node->left))
            R = max(0, maxGain(node->right))

            pathThroughNode = node->val + L + R;
            maxSum = max(maxSum, pathThroughNode)   // global update (both branches)
            return node->val + max(L, R)            // return to parent (one branch only)

    Time: O(N), Space: O(H) where H = height of tree.
*/

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int val;
};

class Solution {
private:
    int maxPathSumUtil(TreeNode* node, int &maxSum) {
        if (node == nullptr) return 0;

        // Only take branch if it contributes positively
        int leftGain = max(0, maxPathSumUtil(node->left, maxSum));
        int rightGain = max(0, maxPathSumUtil(node->right, maxSum));

        // Path through this node using both branches
        int pathThroughNode = node->val + leftGain + rightGain;

        // Update global max
        maxSum = max(maxSum, pathThroughNode);

        // Return to parent: can only go one direction
        return node->val + max(leftGain, rightGain);
    }

public:
    int maxPathSum(TreeNode* root) {
        int maxSum = INT_MIN;
        maxPathSumUtil(root, maxSum);
        return maxSum;
    }

};


int main() {
    Solution obj;

    // Build tree:
    //       -10
    //       /  \
    //      9    20
    //          /  \
    //         15   7
    TreeNode* root = new TreeNode{nullptr, nullptr, -10};
    root->left = new TreeNode{nullptr, nullptr, 9};
    root->right = new TreeNode{nullptr, nullptr, 20};
    root->right->left = new TreeNode{nullptr, nullptr, 15};
    root->right->right = new TreeNode{nullptr, nullptr, 7};

    cout << "Max Path Sum: " << obj.maxPathSum(root) << endl; // Expected: 42

    // Cleanup
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
