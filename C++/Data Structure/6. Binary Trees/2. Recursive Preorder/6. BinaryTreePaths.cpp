#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
    Problem (LC 257. Binary Tree Paths)
    -------
    Given the root of a binary tree, return all root-to-leaf paths in
    any order. A leaf is a node with no children.

    Example
    -------
    Input:
            1
           / \
          2   3
           \
            5

    Output: ["1->2->5", "1->3"]

    Path 1: 1 -> 2 -> 5  (leaf node 5)
    Path 2: 1 -> 3        (leaf node 3)

    Approach — Recursive DFS with path string
    --------
    Use a helper that carries the path-so-far as a string parameter.

    At each node:
        1. If it's a leaf (no left, no right):
           - Append the node's value to the path string.
           - Push the completed path into the result vector.
           - Return (this path is done).
        2. Otherwise (internal node):
           - Append the node's value followed by "->" to the path.
           - Recurse on the left child (if exists).
           - Recurse on the right child (if exists).

    Key detail: the path string is passed BY VALUE, not by reference.
    This means each recursive branch gets its own copy, so we don't
    need to manually undo (backtrack) the append when returning.
    The call stack handles the "undo" implicitly.

    Time:  O(n) — every node is visited once.
    Space: O(h * L) — recursion stack is O(h), and at each level we copy
           a path string of length up to L (the path length in characters).
           In the worst case (skewed tree), h = n.
*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    // path: the path string built so far (passed by value = implicit backtracking)
    // allPaths: collects all completed root-to-leaf paths
    void binaryTreePathsUtil(TreeNode* root, string path, vector<string>& allPaths) {
        if (root == nullptr) return;

        // leaf node — complete the path and store it
        if (root->left == nullptr && root->right == nullptr) {
            path += to_string(root->val);  // append leaf value
            allPaths.push_back(path);      // save completed path
            return;
        }

        // internal node — append value and arrow, then recurse
        path += to_string(root->val) + "->";
        binaryTreePathsUtil(root->left, path, allPaths);   // explore left subtree
        binaryTreePathsUtil(root->right, path, allPaths);  // explore right subtree
    }

public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> allPaths;
        binaryTreePathsUtil(root, "", allPaths);
        return allPaths;
    }
};

int main() {
    //        1
    //       / \
    //      2   3
    //       \
    //        5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);

    Solution sol;
    vector<string> paths = sol.binaryTreePaths(root);

    cout << "All root-to-leaf paths:" << endl;
    for (const string& p : paths) {
        cout << "  " << p << endl;
    }
    // Expected:
    //   1->2->5
    //   1->3

    return 0;
}
