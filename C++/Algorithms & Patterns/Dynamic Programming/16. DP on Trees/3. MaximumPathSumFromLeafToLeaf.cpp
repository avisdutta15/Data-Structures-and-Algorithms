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
    Given the root of a binary tree, find the maximum path sum between any two leaf nodes.
    The path must start at a leaf and end at a leaf.

    Examples:
    --------
    Input:
           -10
           /  \
          9    20
              /  \
             15   7
    Output: 42
    Explanation: Path 15 -> 20 -> 7 = 42

    Input:
            1
           / \
          2   3
    Output: 6
    Explanation: Path 2 -> 1 -> 3 = 6

    Input:
           -5
           / \
         -2   -3
    Output: -10
    Explanation: Path -2 -> -5 -> -3 = -10 (must go leaf to leaf, can't skip negatives)

    Constraints:
    ------------
    - The number of nodes in the tree is in the range [2, 10^4].
    - -1000 <= Node.val <= 1000
    - Tree has at least 2 leaves.

    Approach :
    ----------
    Same DP on Trees pattern as LC 124, but:
    - Path MUST start and end at leaf nodes.
    - Cannot use max(0, branch) since we must reach leaves (even through negatives).
    - Only update global max when node has BOTH children (only then is it a valid leaf-to-leaf path).
    - If node has one child, just pass through (can't be an endpoint).

    Recurrence:
        maxGain(node, maxSum):
            if node == null: return 0
            if node is leaf: return node->val

            L = maxGain(node->left, maxSum)
            R = maxGain(node->right, maxSum)

            if both children exist:
                maxSumViaThisNode = val + L + R;
                maxSum = max(maxSum, maxSumViaThisNode)   // leaf-to-leaf through this node
                return val + max(L, R)              // return better branch

            if only left:  return val + L
            if only right: return val + R

    Time: O(N), Space: O(H) where H = height of tree.
*/

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int val;
};

class Solution {
private:
    int maxPathSumLeafToLeafUtil(TreeNode* node, int& maxSum) {
        if (node == nullptr) 
            return 0;

        // Leaf node: return its value
        if (!node->left && !node->right) 
            return node->val;

        int leftGain = maxPathSumLeafToLeafUtil(node->left, maxSum);
        int rightGain = maxPathSumLeafToLeafUtil(node->right, maxSum);

        // There can be 2 types of non-lead nodes:
        // 1. have 2 children -> calculate the path through this node. Update max if needed. return the val + best branch
        // 2. have 1 child -> return the gain from that child

        // If node has both children, consider the leaf-to-leaf path through it
        if (node->left && node->right) {

            int maxSumViaThisNode = node->val + leftGain + rightGain;
            maxSum = max(maxSum, maxSumViaThisNode);

            // Return the better single branch to parent
            return node->val + max(leftGain, rightGain);
        }

        // If only one child exists, must go through that child (can't be an endpoint)
        if(node->left == nullptr)
            return node->val + rightGain;
        else
            return node->val + leftGain;
    }

public:
    int maxPathSumLeafToLeaf(TreeNode* root) {
        int maxSum = INT_MIN;
        maxPathSumLeafToLeafUtil(root, maxSum);
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

    cout << "Max Leaf-to-Leaf Path Sum: " << obj.maxPathSumLeafToLeaf(root) << endl; // Expected: 42

    // Cleanup
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
