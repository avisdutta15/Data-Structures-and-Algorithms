#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
    Problem
    -------
    Given a binary tree, return its zigzag level-order traversal.
    Nodes at the first level are read left-to-right, the next level
    right-to-left, alternating for each subsequent level.

    Example
    -------
    Input Tree:
            3
           / \
          9   20
             /  \
            15    7

    Output: [[3], [20, 9], [15, 7]]

    Level 0 (L->R): 3
    Level 1 (R->L): 20 9
    Level 2 (L->R): 15 7

    Approach
    --------
    Use BFS with a queue and a boolean flag (leftToRight):
    1. Push root into the queue, set leftToRight = true.
    2. For each level:
       a. Create a vector of size levelSize.
       b. If leftToRight, fill from index 0 forward; otherwise from index levelSize-1 backward.
       c. Pop nodes from the queue, place their value at the current index,
          and enqueue their children (always left then right).
       d. Flip the leftToRight flag after each level.
    Time Complexity:  O(n), every node is visited once.
    Space Complexity: O(n), for the queue and the result vectors.
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> answer;
        if (root == nullptr) return answer;

        bool leftToRight = true;
        vector<int> order;
        queue<TreeNode*> Q;
        Q.push(root);

        while (!Q.empty()) {
            int levelSize = Q.size();
            order.clear();
            order.resize(levelSize);
            int i = leftToRight == true ? 0 : levelSize -1;

            while (levelSize--) {
                auto root = Q.front();
                Q.pop();

                order[i] = root->val;
                if (leftToRight)       i++;
                else if (!leftToRight) i--;                
                
                if (root->left) Q.push(root->left);
                if (root->right) Q.push(root->right);
            }
            leftToRight = !leftToRight;
            answer.push_back(order);
        }
        return answer;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    Solution obj;
    auto order = obj.zigzagLevelOrder(root);
    for (auto level : order) {
        for (auto item : level)  cout << item << " ";
        cout << endl;
    }
    return 0;
}
