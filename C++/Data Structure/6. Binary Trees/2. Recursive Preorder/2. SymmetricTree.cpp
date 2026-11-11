#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
    Problem (LC 101. Symmetric Tree)
    -------
    Given the root of a binary tree, check whether it is a mirror of
    itself (i.e., symmetric around its center).

    Example
    -------
    Symmetric:
            1
           / \
          2    2
         / \  / \
        3  4  4  3
    Output: true

    Not symmetric:
            1
           / \
          2    2
           \    \
            3    3
    Output: false (both 3's are right children, so not mirrored)

    Approach
    --------
    A tree is symmetric if its left and right subtrees are mirror images.
    Use a recursive helper isMirror(p, q):
    1. If both p and q are null, they mirror — return true.
    2. If exactly one is null, return false.
    3. If their values differ, return false.
    4. Recurse crosswise: p->left with q->right (outer pair) and
       p->right with q->left (inner pair).
    5. Return true only if both the outer and inner pairs mirror.
    Time Complexity:  O(n), every node is visited once.
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
private:
    bool isSymmetricUtil(TreeNode* root1, TreeNode* root2) {
        if (root1 == nullptr && root2 == nullptr)   return true;   // both empty — same
        if (root1 == nullptr || root2 == nullptr)   return false;  // one empty, one not — mismatch

        if (root1->val != root2->val)    return false;             // values differ
        bool left = isSymmetricUtil(root1->left, root2->right);    // check left subtrees
        bool right = isSymmetricUtil(root1->right, root2->left);   // check right subtrees

        return left && right;                                      // both must match
    }
public:
    bool isSymmetric(TreeNode* root) {
        // 1. Tree has 1 node i.e. root
        if(root->left == nullptr && root->right == nullptr)
            return true;

        // 2. Tree has multiple nodes.
        return isSymmetricUtil(root->left, root->right);
    }
};

int main() {
    // Symmetric tree:
    //        1
    //       / \
    //      2    2
    //     / \  / \
    //    3  4  4  3
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);

    Solution obj;
    cout << (obj.isSymmetric(root) ? "true" : "false") << endl;
    return 0;
}
