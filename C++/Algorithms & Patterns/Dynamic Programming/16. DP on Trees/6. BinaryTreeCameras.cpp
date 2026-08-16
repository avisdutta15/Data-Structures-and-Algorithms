#include <algorithm>
#include <iostream>
#include <climits>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement:
    ------------------
    You are given the root of a binary tree. We install cameras on the tree nodes where
    each camera at a node can monitor its parent, itself, and its immediate children.

    Return the minimum number of cameras needed to monitor all nodes of the tree.

    Examples:
    --------
    Input:
          0
         /
        0
       / \
      0    0
    Output: 1
    Explanation: One camera at the middle node monitors all 4 nodes.

    Input:
          0
         /
        0
       /
      0
     /
    0
    Output: 2
    Explanation: Need cameras at depth 1 and depth 3.

    Constraints:
    ------------
    - The number of nodes in the tree is in the range [1, 1000].
    - Node.val == 0

    Approach :
    ----------
    Greedy + post-order DFS. Each node can be in one of 3 states:
    - 0 = NOT monitored (needs a camera from parent)
    - 1 = HAS a camera
    - 2 = Monitored (covered by a child's camera)

    Strategy: Place cameras as low as possible (on parents of leaves), not on leaves.
    A camera on leaf covers 2 nodes (leaf + parent). 
    A camera on leaf's parent covers up to 4 nodes (2 leaf + node + node's parent).

    State transitions (post-order, leaves first):
    - If any child returns 0 (not monitored): MUST place camera here → return 1
    - If any child returns 1 (has camera): we are monitored → return 2
    - If all children return 2 (monitored): we are NOT monitored → return 0

    Special case: if root returns 0, add one more camera on root.
    This will happen then the root's children are monitored (returns 2 to root).
    In that case, root will rely on its parent to place the camera and monitor it.
    But root doesnot have any parent. So we need to place a camera on root.

    Example:
        1. single node tree: root 
            root's left and right are null
            → both return 2 (saying we are monitored)
            → root returns 0 (saying its parent to take care)
            → cameras++

        2. level 4 trees
        root
          \
           A
            \
             B
              \
               C (leaf)
        Trace:
            C (leaf): null→2, null→2. Both children 2 → returns 0
            B: right=0 → camera++, returns 1
            A: right=1 → returns 2 (monitored by B's camera)
            root: left=null(2), right=2 → all children state 2 → returns 0 ❗

    Null nodes return 2 (they don't need coverage and shouldn't force a camera).
    Why?
    If null returns 0:
          leaf: left=null(0), right=null(0)
            → child not monitored → place camera on leaf → return 1
        Every leaf gets a camera. Wasteful.

    If null returns 2 (what we actually do)
          leaf: left=null(2), right=null(2)
          → all children monitored → leaf is NOT monitored → return 0
          → leaf's PARENT will place the camera
        Camera goes on leaf's parent instead, covering more nodes.

    Recurrence:
        0 = not monitored, 1 = has camera, 2 = monitored
        dfs(node):
            if node == null: 
                return 2

            left  = dfs(node->left)
            right = dfs(node->right)

            // if any of the child is not monitored. place a camera here.
            if left == 0 or right == 0:
                cameras++
                return 1

            // if any of the child has camera, we are monitored
            if left == 1 or right == 1:
                return 2
            
            // both children are monitored (2,2) then we ask our parent to take care of us
            // and return not-monitored.
            return 0

        After DFS: 
            if dfs(root) == 0, 
                cameras++

    Time: O(N), 
    Space: O(H) where H = height of tree.
*/

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int val;
};

class Solution {
private:
    int cameras = 0;

    // Returns: 0 = not monitored, 1 = has camera, 2 = monitored
    int dfs(TreeNode* node) {
        if (!node) return 2; // null nodes are "monitored" (don't need coverage)

        int left = dfs(node->left);
        int right = dfs(node->right);

        // If any child is NOT monitored, we MUST place a camera here
        if (left == 0 || right == 0) {
            cameras++;
            return 1;
        }

        // If any child HAS a camera, this node is monitored
        if (left == 1 || right == 1) {
            return 2;
        }

        // Both children are monitored (state 2), we are NOT monitored
        // Let parent place a camera for us
        return 0;
    }

public:
    int minCameraCover(TreeNode* root) {
        // If root itself is not monitored after DFS, add one more camera
        if (dfs(root) == 0) 
            cameras++;
        return cameras;
    }
};


int main() {
    Solution obj;

    // Build tree:
    //        0
    //       /
    //      0
    //     / \
    //    0    0
    TreeNode* root = new TreeNode{nullptr, nullptr, 0};
    root->left = new TreeNode{nullptr, nullptr, 0};
    root->left->left = new TreeNode{nullptr, nullptr, 0};
    root->left->right = new TreeNode{nullptr, nullptr, 0};

    cout << "Min Cameras: " << obj.minCameraCover(root) << endl; // Expected: 1

    // Cleanup
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root;

    return 0;
}
