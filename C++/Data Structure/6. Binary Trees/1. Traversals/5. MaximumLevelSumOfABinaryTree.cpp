#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
    Problem (LC 1161. Maximum Level Sum of a Binary Tree)
    -------
    Given the root of a binary tree, return the smallest level (1-indexed)
    whose nodes have the maximum sum among all levels. If there is a tie,
    return the smallest level number.

    Example
    -------
    Input Tree:
            1
           / \
          3    2
         / \    \
        5    3    9

    Level 1: sum = 1
    Level 2: sum = 3 + 2 = 5
    Level 3: sum = 5 + 3 + 9 = 17

    Output: 3  (level 3 has the maximum sum of 17)

    Approach
    --------
    Use BFS with a queue:
    1. Push root into the queue, set level = 1.
    2. For each level:
       a. Sum all node values at that level.
       b. If the sum exceeds the current maximum, update the maximum and
          record the level number.
       c. Enqueue children of each popped node.
       d. Increment level.
    3. Return the recorded level with the largest sum.
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
    int maxLevelSum(TreeNode* root) {
        if(root == nullptr) return -1;

        queue<TreeNode*> Q;
        int level = 1;
        int largestLevelSum = INT_MIN;
        int minLevel = level;
        Q.push(root);

        while(!Q.empty()){
            int levelSize = Q.size();
            int levelSum = 0;
            while(levelSize--){
                auto node = Q.front();
                Q.pop();
                
                levelSum = levelSum + node->val;

                if(node->left) Q.push(node->left);
                if(node->right) Q.push(node->right);
            }
            if(levelSum > largestLevelSum){
                minLevel = level;
                largestLevelSum = levelSum;
            }
            level++;
        }
        return minLevel;
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
    cout << obj.maxLevelSum(root) << endl;
    return 0;
}
