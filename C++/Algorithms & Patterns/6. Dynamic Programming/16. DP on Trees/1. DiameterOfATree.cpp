#include <algorithm>
#include <iostream>
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
    Given the root of a binary tree, return the length of the diameter of the tree.

    The diameter of a binary tree is the length of the longest path between any two nodes in a tree. 
    This path may or may not pass through the root.

    The length of a path between two nodes is represented by the number of edges between them.

    Examples:
    --------
    Input: root = [1,2,3,4,5]
            1
           / \
          2   3
         / \
        4   5
    Output: 3
    Explanation: The longest path is 4 -> 2 -> 1 -> 3 (or 5 -> 2 -> 1 -> 3), which has 3 edges.

    Input: root = [1,2]
            1
           /
          2
    Output: 1

    Constraints:
    ------------
    - The number of nodes in the tree is in the range [1, 10^4].
    - -100 <= Node.val <= 100

    Approach :
    ----------
    At each node, compute left and right subtree heights.
    The path through this node = leftHeight + rightHeight (in edges).
    Update global diameter if this path is longer.
    Return 1 + max(leftHeight, rightHeight) to parent (single branch height).

    Recurrence:
        height(node):
            if node == null: 
                return 0

            L = height(left), 
            R = height(right)

            diameter = max(diameter, L + R)     // we don't do L + R + 1 since we are counting edges not nodes
            return 1 + max(L, R)

    Time: O(N), Space: O(H) where H = height of tree.
*/

struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    int val;
};

class Solution {
public:
    int diameter = 0;

    int diameterOfBinaryTree(TreeNode* root) {
        height(root);
        return diameter;
    }

private:
    int height(TreeNode* node) {
        if (node == nullptr) return 0;

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        // Update diameter: path through this node
        diameter = max(diameter, leftHeight + rightHeight);

        // Return height to parent: longest single path from this node downward
        return 1 + max(leftHeight, rightHeight);
    }
};


int main() {
    Solution obj;

    // Build tree:
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    TreeNode* root = new TreeNode{nullptr, nullptr, 1};
    root->left = new TreeNode{nullptr, nullptr, 2};
    root->right = new TreeNode{nullptr, nullptr, 3};
    root->left->left = new TreeNode{nullptr, nullptr, 4};
    root->left->right = new TreeNode{nullptr, nullptr, 5};

    cout << "Diameter: " << obj.diameterOfBinaryTree(root) << endl; // Expected: 3

    // Cleanup
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}