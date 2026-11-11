#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
    Problem (LC 100. Same Tree)
    -------
    Given the roots of two binary trees p and q, check whether they are
    structurally identical and every corresponding node has the same value.

    Example
    -------
    Tree p:        Tree q:
        1              1
       / \            / \
      2    3         2    3

    Output: true  (both trees have the same structure and values)

    Tree p:        Tree q:
        1              1
       /                \
      2                  2

    Output: false (left child vs right child — different structure)

    Approach
    --------
    Use recursion:
    1. If both nodes are null, return true (both subtrees ended together).
    2. If only one is null, return false (structure mismatch).
    3. If values differ, return false.
    4. Recursively check left subtrees and right subtrees.
    5. Return true only if both left and right checks pass.
    Time Complexity:  O(n), where n = min(nodes in p, nodes in q).
    Space Complexity: O(h), recursion stack depth, where h is the tree height.
*/

struct TreeNode {
    int val;
    TreeNode* left, * right;
    TreeNode(int val, TreeNode* left = nullptr, TreeNode* right = nullptr) {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr)   return true;   // both empty — same
        if (p == nullptr || q == nullptr)   return false;  // one empty, one not — mismatch

        if (p->val != q->val)    return false;             // values differ
        bool left = isSameTree(p->left, q->left);          // check left subtrees
        bool right = isSameTree(p->right, q->right);       // check right subtrees

        return left && right;                              // both must match
    }
};

int main() {
    TreeNode* p = new TreeNode(1);
    p->left = new TreeNode(2);
    p->right = new TreeNode(3);

    TreeNode* q = new TreeNode(1);
    q->left = new TreeNode(2);
    q->right = new TreeNode(3);

    Solution obj;
    cout << (obj.isSameTree(p, q) ? "true" : "false") << endl;
    return 0;
}
