#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
    Problem (LC 199. Binary Tree Right Side View)
    -------
    Given the root of a binary tree, return the values of the nodes you
    can see when looking at the tree from the right side, ordered from
    top to bottom.

    Example
    -------
    Input Tree:
            1
           / \
          3    2
         / \    \
        5    3    9

    Right Side View: [1, 2, 9]

    Level 0: rightmost = 1
    Level 1: rightmost = 2
    Level 2: rightmost = 9

    Approach
    --------
    Use BFS with a queue, enqueuing right child before left:
    1. Push root into the queue.
    2. For each level:
       a. The front of the queue is the rightmost node (since right children
          were enqueued first). Add it to the result.
       b. Pop all nodes at that level, enqueuing each node's right child
          first, then left child.
    3. Return the result vector.
    Time Complexity:  O(n), every node is visited once.
    Space Complexity: O(n), for the queue.
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
    vector<int> rightSideView(TreeNode* root) {
        if (root == nullptr) return vector<int>();

        vector<int> view;
        queue<TreeNode*> Q;
        Q.push(root);

        while (!Q.empty()) {
            int levelSize = Q.size();
            view.push_back(Q.front()->val);     // new level starts so push the first element to result.
                                                // since Q has right child then left child, so right child
                                                // comes first and then left child.
            while (levelSize--) {
                auto node = Q.front();
                Q.pop();

                if (node->right) Q.push(node->right);
                if (node->left) Q.push(node->left);
            }  
        }
        return view;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(9);

    Solution obj;
    auto view = obj.rightSideView(root);
    for (auto item : view) cout << item << " ";
    cout << endl;
    return 0;
}
