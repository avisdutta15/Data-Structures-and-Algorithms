#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
    Problem
    -------
    Given a binary tree, find the largest value in each row (i.e., each
    depth level) and return them as a vector.

    Example
    -------
    Input Tree:
            1
           / \
          3    2
         / \    \
        5    3    9

    Output: [1, 3, 9]

    Level 0: max(1)       = 1
    Level 1: max(3, 2)    = 3
    Level 2: max(5, 3, 9) = 9

    Approach
    --------
    Use BFS with a queue:
    1. Push root into the queue.
    2. For each level:
       a. Initialize largest = INT_MIN.
       b. Pop all nodes at that level, updating largest with each node's value.
       c. Enqueue children of each popped node.
       d. After the level is processed, push largest into the result vector.
    Time Complexity:  O(n), every node is visited once.
    Space Complexity: O(n), for the queue (worst case the widest level holds ~n/2 nodes).
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
    vector<int> largestValues(TreeNode* root) {
        if (root == nullptr) return vector<int>();

        queue<TreeNode*> Q;
        Q.push(root);

        vector<int> levelLargestValues;

        while (!Q.empty()) {
            int largest = INT_MIN;
            int levelSize = Q.size();
            while (levelSize--) {
                auto root = Q.front();
                Q.pop();

                largest = max(largest, root->val);
                if (root->left) Q.push(root->left);
                if (root->right) Q.push(root->right);
            }
            levelLargestValues.push_back(largest);
        }

        return levelLargestValues;
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
    auto order = obj.largestValues(root);
    for (auto item : order) {
        cout << item << " ";
    }
    return 0;
}
