#include <iostream>
#include <stack>
using namespace std;

/*
    Problem (LC 114. Flatten Binary Tree to Linked List)
    -------
    Given the root of a binary tree, flatten it into a "linked list" in-place:
    - Use the same TreeNode class.
    - Every node's left pointer must be null.
    - Every node's right pointer points to the next node in pre-order.

    Example
    -------
    Input:                      Output (right-only chain):
            1                       1
           / \                       \
          2   5                       2
         / \   \                       \
        3   4   6                       3
                                         \
                                          4
                                           \
                                            5
                                             \
                                              6

    Pre-order: 1 -> 2 -> 3 -> 4 -> 5 -> 6
    The flattened list follows this exact order using right pointers.

    =========================================================================
    Approach 1 — Reverse Post-order (build list from the tail)
    =========================================================================
    Key insight: pre-order is Root → Left → Right.
    If we traverse in reverse (Right → Left → Root), the FIRST node we
    visit is the LAST node of the flattened list. So we can build the
    list backwards, always prepending the current node to the chain
    we've built so far.

    Steps:
        1. Recurse into right subtree first.
        2. Recurse into left subtree.
        3. Set current node's right = tail (the chain built so far).
        4. Set current node's left = nullptr.
        5. Update tail = current node.

    Time:  O(n)    Space: O(h) — recursion stack

    =========================================================================
    Approach 2 — Recursive Pre-order (build list from the head)
    =========================================================================
    Standard pre-order: visit Root, then Left, then Right.
    We maintain a head and tail pointer passed by reference.
    Each visited node is detached and appended to the tail.

    Steps:
        1. Save left and right children (they'll be overwritten).
        2. Set node's left = nullptr, right = nullptr (detach it).
        3. If head is null, this node is the head and tail.
           Otherwise, tail->right = node, tail = node.
        4. Recurse on saved left child, then saved right child.

    Time:  O(n)    Space: O(h) — recursion stack

    =========================================================================
    Approach 3 — Iterative Pre-order using a Stack
    =========================================================================
    Simulate pre-order with a stack. At each step, the next node in
    pre-order is at the top of the stack, so we wire current->right
    to stack.top().

    Steps:
        1. Push root onto the stack.
        2. Pop a node (current).
        3. Push current->right then current->left (LIFO, so left is
           popped first = visited first = pre-order).
        4. current->right = stack.top() (next node in pre-order).
        5. current->left  = nullptr.
        6. Repeat until stack is empty.

    Time:  O(n)    Space: O(h) — stack holds at most h nodes

    =========================================================================
    Approach 4 — Morris Traversal (O(1) extra space)
    =========================================================================
    Uses the tree's own null pointers to thread nodes, avoiding a stack.

    For each node with a left child:
        1. Find the in-order predecessor of the right subtree within the
           left subtree (the rightmost node of the left subtree).
        2. Attach the current node's original right subtree to that
           predecessor's right pointer (temporary storage).
        3. Move the left subtree to the right: current->right = current->left.
        4. Set current->left = nullptr.
        5. Advance: current = current->right.

    If no left child, just advance right.

    Effect: the left subtree is "inserted" between the current node and
    its original right subtree, achieving pre-order without extra space.

    Time:  O(n)    Space: O(1) — no stack or recursion
*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// =========================================================================
// Solution1: Reverse Post-order (Right → Left → Root), build from tail
// =========================================================================
class Solution1 {
    TreeNode* tail = nullptr;  // tracks the head of the chain built so far
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) return;

        flatten(root->right);   // process right subtree first
        flatten(root->left);    // then left subtree

        // now attach current node to the front of the chain
        root->right = tail;     // current node points to the chain
        root->left = nullptr;   // flatten requirement: left must be null
        tail = root;            // current node becomes the new head of chain
    }
};

// =========================================================================
// Solution2: Recursive Pre-order (Root → Left → Right), build from head
// =========================================================================
class Solution2 {
    // helper: visits nodes in pre-order, appends each to the tail of list
    void preorder(TreeNode* root, TreeNode*& head, TreeNode*& tail) {
        if (root == nullptr) return;

        TreeNode* leftChild = root->left;    // save before overwriting
        TreeNode* rightChild = root->right;  // save before overwriting

        root->left = nullptr;   // detach node
        root->right = nullptr;

        if (head == nullptr) {
            head = root;        // first node becomes head
            tail = root;
        } else {
            tail->right = root; // append to end of list
            tail = root;        // update tail
        }

        preorder(leftChild, head, tail);   // recurse left
        preorder(rightChild, head, tail);  // recurse right
    }
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        TreeNode* head = nullptr;
        TreeNode* tail = nullptr;
        preorder(root, head, tail);
    }
};

// =========================================================================
// Solution3: Iterative Pre-order with a Stack
// =========================================================================
class Solution3 {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) return;

        stack<TreeNode*> stack;
        stack.push(root);

        while (!stack.empty()) {
            TreeNode* current = stack.top();
            stack.pop();

            // push right first so left is on top (processed first = pre-order)
            if (current->right != nullptr)
                stack.push(current->right);
            if (current->left != nullptr)
                stack.push(current->left);

            // wire current node to the next node in pre-order
            if (!stack.empty())
                current->right = stack.top();  // next pre-order node
            else
                current->right = nullptr;    // last node in the list

            current->left = nullptr;         // flatten requirement
        }
    }
};

// =========================================================================
// Solution4: Morris Traversal — O(1) space
// =========================================================================
class Solution4 {
    // find the rightmost node of root's left subtree (the predecessor)
    TreeNode* getPredecessor(TreeNode* root) {
        TreeNode* pred = root->left;
        while (pred->right != nullptr)  // go as far right as possible
            pred = pred->right;
        return pred;
    }
public:
    void flatten(TreeNode* root) {
        TreeNode* current = root;

        while (current != nullptr) {
            if (current->left == nullptr) {
                // no left subtree — already in correct order, move right
                current = current->right;
            } else {
                // find rightmost node of left subtree
                TreeNode* pred = getPredecessor(current);

                // attach original right subtree after the predecessor
                pred->right = current->right;

                // move left subtree to the right
                current->right = current->left;
                current->left = nullptr;   // flatten requirement

                // advance to the next node (old left child, now right child)
                current = current->right;
            }
        }
    }
};

// =========================================================================
// Helpers
// =========================================================================

// Build a fresh copy of the test tree each time (since flatten is in-place)
TreeNode* buildTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(6);
    return root;
}

// Print the flattened list (right pointers only)
void printFlattenedList(TreeNode* root) {
    while (root != nullptr) {
        cout << root->val;
        if (root->right) cout << " -> ";
        root = root->right;
    }
    cout << endl;
}

int main() {
    TreeNode* t1 = buildTree();
    Solution1 s1;
    s1.flatten(t1);
    cout << "Solution1 (Reverse Post-order): ";
    printFlattenedList(t1);

    TreeNode* t2 = buildTree();
    Solution2 s2;
    s2.flatten(t2);
    cout << "Solution2 (Recursive Preorder): ";
    printFlattenedList(t2);

    TreeNode* t3 = buildTree();
    Solution3 s3;
    s3.flatten(t3);
    cout << "Solution3 (Iterative Stack):    ";
    printFlattenedList(t3);

    TreeNode* t4 = buildTree();
    Solution4 s4;
    s4.flatten(t4);
    cout << "Solution4 (Morris Traversal):   ";
    printFlattenedList(t4);

    return 0;
}
