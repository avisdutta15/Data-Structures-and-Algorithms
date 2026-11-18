#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
    Problem (LC 988. Smallest String Starting From Leaf)
    -------
    Each node in a binary tree holds a value 0–25, representing 'a'–'z'.
    A "string starting from leaf" is built by reading characters from a
    leaf up to the root (leaf-to-root order).
    Return the lexicographically smallest such string among all leaves.

    Example
    -------
    Input (values shown as letters):
              a (0)
             / \
            b   c (1, 2)
           / \   \
          d   e   d (3, 4, 3)

    Leaf-to-root paths:
        d -> b -> a  =>  "dba"
        e -> b -> a  =>  "eba"
        d -> c -> a  =>  "dca"

    Output: "dba"  (lexicographically smallest)

    =========================================================================
    Approach 1 — DFS, append + reverse at leaf
    =========================================================================
    We build the path string top-down (root-to-leaf) as we recurse.
    At each node, prepend or append its character to a running string.

    Here we APPEND during traversal (root-to-leaf order), then REVERSE
    the string only when we reach a leaf to get the required leaf-to-root
    order. We then compare against the current best.

    Steps:
        1. Convert node value to a char: 'a' + val.
        2. Append the char to the current path string.
           (current is passed by VALUE, so each branch has its own copy —
            implicit backtracking, no manual undo needed.)
        3. At a leaf node:
           a. Reverse the current string → now it's leaf-to-root.
           b. If smallest is empty OR current < smallest, update smallest.
        4. Recurse on left and right children.

    Why compare with '<' directly?
        std::string's '<' operator does lexicographic comparison, which
        handles both different-length and same-length strings correctly:
        "abc" < "abd", "ab" < "abc", etc.

    Time:  O(n * L) — visit every node; at each leaf, reversing and
           comparing costs O(L) where L is the path length.
    Space: O(h * L) — recursion stack of depth h, each frame holds a
           path string copy of up to length L. Worst case h = n.

    =========================================================================
    Approach 2 — DFS, prepend at each node (no reverse needed)
    =========================================================================
    Instead of appending and reversing at the leaf, PREPEND the current
    node's character to the running string at each step:
        current = char + current

    Since we traverse top-down (root → leaf), prepending builds the
    string in leaf-to-root order on the fly. By the time we reach a
    leaf, the string is already correct — just compare directly.

    Trade-off: prepending to a std::string is O(L) per node (shifts all
    existing characters), so overall it's the same O(n * L) time as
    Approach 1. But it's simpler — no reverse call needed.

    Time:  O(n * L) — prepend is O(L) at each of n nodes.
    Space: O(h * L) — same as Approach 1.
*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// =========================================================================
// Solution1: Append + reverse at leaf
// =========================================================================
class Solution1 {
private:
    // current: root-to-node path built so far (passed by value = implicit backtrack)
    // smallest: best leaf-to-root string found so far (passed by reference)
    void smallestFromLeafUtil(TreeNode* root, string current, string& smallest) {
        if (root == nullptr) return;

        current += (char)('a' + root->val);  // append this node's character

        // leaf node — finalize this path
        if (root->left == nullptr && root->right == nullptr) {
            reverse(current.begin(), current.end());  // flip to leaf-to-root order

            // update smallest if this path is better (or first path found)
            if (smallest.empty() || current < smallest)
                smallest = current;
            return;
        }

        // recurse into children
        smallestFromLeafUtil(root->left, current, smallest);
        smallestFromLeafUtil(root->right, current, smallest);
    }

public:
    string smallestFromLeaf(TreeNode* root) {
        string smallest = "";
        smallestFromLeafUtil(root, "", smallest);
        return smallest;
    }
};

// =========================================================================
// Solution2: Prepend at each node (no reverse needed)
// =========================================================================
class Solution2 {
private:
    // current: leaf-to-root path built so far (passed by value = implicit backtrack)
    // smallest: best string found so far (passed by reference)
    void smallestFromLeafUtil(TreeNode* root, string current, string& smallest) {
        if (root == nullptr) return;

        current = (char)('a' + root->val) + current;  // prepend this node's char

        // leaf node — string is already in leaf-to-root order
        if (root->left == nullptr && root->right == nullptr) {
            if (smallest.empty() || current < smallest)
                smallest = current;  // update if better
            return;
        }

        // recurse into children
        smallestFromLeafUtil(root->left, current, smallest);
        smallestFromLeafUtil(root->right, current, smallest);
    }

public:
    string smallestFromLeaf(TreeNode* root) {
        string smallest = "";
        smallestFromLeafUtil(root, "", smallest);
        return smallest;
    }
};

int main() {
    //          a (0)
    //         / \
    //        b   c (1, 2)
    //       / \   \
    //      d   e   d (3, 4, 3)
    TreeNode* root = new TreeNode(0);       // 'a'
    root->left = new TreeNode(1);           // 'b'
    root->right = new TreeNode(2);          // 'c'
    root->left->left = new TreeNode(3);     // 'd'
    root->left->right = new TreeNode(4);    // 'e'
    root->right->right = new TreeNode(3);   // 'd'

    Solution1 s1;
    string r1 = s1.smallestFromLeaf(root);
    cout << "Solution1 (append + reverse): " << r1 << endl;

    Solution2 s2;
    string r2 = s2.smallestFromLeaf(root);
    cout << "Solution2 (prepend):          " << r2 << endl;
    // Expected: "dba" for both

    return 0;
}
