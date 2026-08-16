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
    Given the root of an N-ary tree, return the length of the diameter of the tree.
    The diameter is the length of the longest path between any two nodes (in edges).

    Examples:
    --------
    Input:
              1
           /  |  \
          2   3   4
         / \      |
        5   6     7

    Output: 4
    Explanation: Path 5 -> 2 -> 1 -> 4 -> 7 (or 6 -> 2 -> 1 -> 4 -> 7), 4 edges.

    Constraints:
    ------------
    - The number of nodes is in the range [1, 10^4].

    Approach :
    ----------
    Same pattern as binary tree diameter:
              1
            / | \
           2  3  4
          /|     |
         5  6    7

    At node 1: heights from children = [2(→2→5), 1(→3), 2(→4→7)]
      Two tallest: 2 and 2
      Diameter through node 1 = 2 + 2 = 4 (path: 5→2→1→4→7)

    - At each node, the diameter through it = sum of its TWO tallest child heights.
    - Return to parent: 1 + tallest child height (single branch).
    - Track two tallest heights among all children to avoid sorting.

    Recurrence:
        height(node):
            if node == null: return 0

            maxHeight1 = 0, maxHeight2 = 0   // two tallest children
            for each child in node->children:
                h = height(child)
                update maxHeight1, maxHeight2 with h

            diameter = max(diameter, maxHeight1 + maxHeight2)   // global update
            return 1 + maxHeight1                               // return to parent

    Time: O(N), Space: O(H) where H = height of tree.
*/

// N-ary tree node
struct Node {
    int val;
    vector<Node*> children;
    Node(int v) : val(v) {}
};

class Solution {
private:
    int diameter = 0;

    int height(Node* node) {
        if (!node) return 0;

        int maxHeight1 = 0; // tallest child
        int maxHeight2 = 0; // second tallest child

        for (Node* child : node->children) {
            int h = height(child);

            // Track the two tallest heights
            if (h >= maxHeight1) {
                maxHeight2 = maxHeight1;
                maxHeight1 = h;
            } else if (h > maxHeight2) {
                maxHeight2 = h;
            }
        }

        // Diameter through this node = two tallest branches
        diameter = max(diameter, maxHeight1 + maxHeight2);

        // Return height to parent
        return 1 + maxHeight1;
    }

public:
    int diameterOfNaryTree(Node* root) {
        height(root);
        return diameter;
    }
};


int main() {
    Solution obj;

    // Build tree:
    //        1
    //      / | \
    //     2  3  4
    //    / \    |
    //   5   6  7
    Node* root = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);

    root->children = {n2, n3, n4};
    n2->children = {n5, n6};
    n4->children = {n7};

    cout << "Diameter of N-ary Tree: " << obj.diameterOfNaryTree(root) << endl; // Expected: 4

    // Cleanup
    delete n5; delete n6; delete n7;
    delete n2; delete n3; delete n4;
    delete root;

    return 0;
}
