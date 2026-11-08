#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    Problem
    -------
    Given a binary tree, perform three types of depth-first traversals:
    1. Preorder  (Root -> Left -> Right)
    2. Inorder   (Left -> Root -> Right)
    3. Postorder (Left -> Right -> Root)

    Example
    -------
    Input Tree:
            10
           /  \
         20    50
        /  \
      30    40

    Preorder:  10 20 30 40 50
    Inorder:   30 20 40 10 50
    Postorder: 30 40 20 50 10

    Approach
    --------
    Use simple recursion for each traversal:
    - Base case: if the node is null, return.
    - Preorder:  visit the node, then recurse left, then recurse right.
    - Inorder:   recurse left, visit the node, then recurse right.
    - Postorder: recurse left, recurse right, then visit the node.
    Time Complexity:  O(n) for each traversal, where n is the number of nodes.
    Space Complexity: O(h) due to the recursion stack, where h is the height of the tree.
*/

struct TreeNode {
    int data;
    TreeNode* left, * right;
    TreeNode(int data, TreeNode* left = nullptr, TreeNode* right = nullptr) {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

class Solution {
public:
    void preorder(TreeNode* root) {
        if (root == nullptr) return;

        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);        
    }

    void inorder(TreeNode* root) {
        if (root == nullptr) return;

        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    void postorder(TreeNode* root) {
        if (root == nullptr) return;

        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
};

int main() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(20);
    root->left->left = new TreeNode(30);
    root->left->right = new TreeNode(40);
    root->right = new TreeNode(50);

    Solution obj;
    obj.inorder(root);
    cout << endl;
    obj.preorder(root);
    cout << endl;
    obj.postorder(root);
    return 0;
}
