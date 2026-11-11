#include <iostream>
#include <queue>
using namespace std;

/*
    Problem (LC 226. Invert Binary Tree)
    -------
    Given the root of a binary tree, invert it — swap every node's left
    and right children — and return the root.

    Example
    -------
    Input:               Output:
          4                   4
         / \                 / \
        2   7               7   2
       / \ / \             / \ / \
      1  3 6  9           9  6 3  1

    Every pair of siblings is mirrored at every level.

    =========================================================================
    Approach 1 — Recursive DFS
    =========================================================================
    At each node:
        1. Swap its left and right children.
        2. Recurse on the (now swapped) left subtree.
        3. Recurse on the (now swapped) right subtree.
    Base case: if root is null, return.

    Why it works: by swapping at every node top-down, each subtree is
    recursively mirrored. The order of recursion (pre-order, post-order,
    or in-order with care) doesn't matter as long as every node is visited
    exactly once and its children are swapped.

    Time:  O(n) — visit every node once.
    Space: O(h) — recursion stack, h = tree height (O(log n) balanced,
                  O(n) worst-case skewed).

    =========================================================================
    Approach 2 — Iterative BFS (Level-order)
    =========================================================================
    Use a queue to traverse the tree level by level.
    At each node:
        1. Swap its left and right children.
        2. Enqueue the non-null children.
    Continue until the queue is empty.

    Why it works: every node is visited exactly once and its children are
    swapped, just like the recursive version, but using a queue instead
    of the call stack.

    Time:  O(n) — visit every node once.
    Space: O(n) — the queue can hold up to n/2 nodes at the widest level.
*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Solution1: Recursive DFS
class Solution1 {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;  // base case

        // swap left and right children
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;

        invertTree(root->left);   // recurse on left subtree
        invertTree(root->right);  // recurse on right subtree

        return root;
    }
};

// Solution2: Iterative BFS (Level-order)
class Solution2 {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;

        queue<TreeNode*> Q;
        Q.push(root);

        while (!Q.empty()) {
            TreeNode* node = Q.front();  // current node
            Q.pop();

            // swap left and right children
            TreeNode* temp = node->left;
            node->left = node->right;
            node->right = temp;

            if (node->left)  Q.push(node->left);   // enqueue left child
            if (node->right) Q.push(node->right);  // enqueue right child
        }
        return root;
    }
};

// Print tree in-order to verify inversion
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

TreeNode* buildTree() {
    //        4
    //       / \
    //      2   7
    //     / \ / \
    //    1  3 6  9
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(9);
    return root;
}

int main() {
    TreeNode* t1 = buildTree();
    cout << "Before inversion (inorder): ";
    printInorder(t1);  // 1 2 3 4 6 7 9
    cout << endl;

    Solution1 s1;
    s1.invertTree(t1);
    cout << "Solution1 — Recursive DFS:  ";
    printInorder(t1);  // 9 7 6 4 3 2 1
    cout << endl;

    TreeNode* t2 = buildTree();
    Solution2 s2;
    s2.invertTree(t2);
    cout << "Solution2 — Iterative BFS:  ";
    printInorder(t2);  // 9 7 6 4 3 2 1
    cout << endl;

    return 0;
}
