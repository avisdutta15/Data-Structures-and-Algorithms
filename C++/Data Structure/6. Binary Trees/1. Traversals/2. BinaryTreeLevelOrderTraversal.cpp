#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
    Problem
    -------
    Given a binary tree, return its level-order traversal as a 2D vector,
    where each inner vector contains the node values at that depth level
    (left to right).

    Example
    -------
    Input Tree:
            10
           /  \
         20    50
        /  \
      30    40

    Output: [[10], [20, 50], [30, 40]]

    Printed:
        10
        20 50
        30 40

    Approach
    --------
    Use BFS with a queue:
    1. Push the root into the queue.
    2. While the queue is not empty:
       a. Record the current queue size (= number of nodes at this level).
       b. Pop that many nodes, collecting their values into a level vector.
       c. For each popped node, push its left and right children (if they exist).
       d. Append the level vector to the result.
    Time Complexity:  O(n), every node is visited once.
    Space Complexity: O(n), the queue can hold up to n/2 nodes at the widest level.
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> order;
        if (root == nullptr) return order;

        queue<TreeNode*> Q;
        vector<int> level;
        Q.push(root);

        while (!Q.empty()) {
            int levelSize = Q.size();
            level.clear();

            while (levelSize--) {
                auto u = Q.front();
                Q.pop();

                level.push_back(u->val);

                if (u->left) Q.push(u->left);
                if (u->right) Q.push(u->right);
            }
            order.push_back(level);
        }
        return order;
    }
};

int main() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(20);
    root->left->left = new TreeNode(30);
    root->left->right = new TreeNode(40);
    root->right = new TreeNode(50);

    Solution obj;
    auto order = obj.levelOrder(root);
    for (auto level : order) {
        for (auto item : level)  cout << item << " ";
        cout << endl;
    }
    return 0;
}
