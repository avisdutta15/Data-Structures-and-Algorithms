#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given the root of a binary tree, flatten the tree into a "linked list":

    The "linked list" should use the same TreeNode class where the right child pointer points to the next 
    node in the list and the left child pointer is always null.
    The "linked list" should be in the same order as a pre-order traversal of the binary tree.

    Input:
                        1
                     /    \
                    2      5
                  /   \     \
                 3    4      6

    Output:
                    1
                     \
                      2
                       \
                        3
                         \
                          4
                           \
                            5
                             \
                              6

    Approach:
    1. Build the linked list from behind. To build it from behind, you need to traverse right subtree first, then left subtree and then root.
       Because the preorder traversal is root->leftSubtree->rightSubtree
       flatten (root):
            if(root == null)
                return root
            flatten root->right;
            flatten root->left;
            if(tail == nullptr)
                tail = root;
            else
                root->right = tail;
                root->left = nullptr;
                tail = root;

    2. Build the linked list from front. 
       Use a helper function (preorder) that accepts references to the head and tail of the list being built.
       The root is visited first (Preorder).
       The root is attached to the current tail, and tail is updated.
       The left and right children are saved before the current node's pointers are reset.
       Recursively call on the saved leftChild, then the rightChild.

    3. Iterative preorder.
        stack.push(root);
        while(!stack.empty()){
            //stack is LIFO so first push right then left
            current = stack.top(); stack.pop();
            stack.push(current->right);
            stack.push(current->left);
            if(!stack.empty())
                current->right = stack.top();
            else
                current->right = nullptr;
            current->left = nullptr;
        }
    4. Morris Preorder
            if left subtree doesnot exists
                goto right subtree

            else
                if(predecessor->right == nullptr) => this means we are visiting root node for the first time.
                    predecessor->right = root->right;
                    root->right = root->left;
                    root->left  = nullptr; //the condition of flattening
                    now the left child is at the right of the node
                    root = root->right
*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    TreeNode* tail = nullptr;
    TreeNode* getPredecessor(TreeNode* root) {
        TreeNode* predecessor = root->left;
        while (predecessor->right != nullptr && predecessor->right != root) {
            predecessor = predecessor->right;
        }
        return predecessor;
    }
    void preorder(TreeNode* root, TreeNode*& head, TreeNode*& tail) {
        if (root == nullptr)
            return;

        //Save the left and right child. This is needed to call preorder recursively.
        TreeNode* leftChild = root->left;
        TreeNode* rightChild = root->right;

        //make the left and right child as null
        root->left = nullptr, root->right = nullptr;

        //set the head and tail
        if (head == nullptr) {
            head = root;
            tail = root;
        }
        else {
            tail->right = root;
            tail = root;
        }

        //call the preorder
        preorder(leftChild, head, tail);
        preorder(rightChild, head, tail);
    }

public:
    //Build the list from back
    void flatten1(TreeNode* root) {
        if (root == nullptr)
            return;

        flatten1(root->right);
        flatten1(root->left);

        if (tail == nullptr)
            tail = root;
        else {
            root->right = tail;
            root->left = nullptr;
            tail = root;
        }        
    }

    //Build the list from head
    void flatten2(TreeNode* root) {
        if (root == nullptr)
            return;
        TreeNode* head = nullptr, * tail = nullptr;
        preorder(root, head, tail);
        root = head;
    }

    //Iterative approach : https://www.youtube.com/watch?v=cyOME3y3i70
    void flatten3(TreeNode* root) {
        stack<TreeNode*> stack;
        stack.push(root);
        while (!stack.empty()) {
            TreeNode* current = stack.top();
            stack.pop();

            if (current->right != nullptr)
                stack.push(current->right);

            if (current->left != nullptr)
                stack.push(current->left);

            if (!stack.empty())
                current->right = stack.top();
            else
                current->right = nullptr;

            current->left = nullptr;
        }
    }

    //Using Morris PreOrder Traversal : O(N) time and O(1) space
    //https://www.youtube.com/watch?v=sWf7k1x9XR4
    void flatten4(TreeNode* root) {
        if (root == nullptr) return;

        TreeNode* current = root;
        TreeNode* predecessor = nullptr;

        while (current != nullptr) {
            // Case 1: The current node has no left child (or left subtree is processed).
            // This is the simplest path.
            if (current->left == nullptr) {
                // If the left child is null, we are already in the correct preorder sequence
                // relative to the current node (Root -> Right).
                current = current->right;
            }
            // Case 2: The current node has a left child.
            else {
                // Find the true Preorder Predecessor (the rightmost node in the left subtree).
                predecessor = getPredecessor(current);

                // Subcase 2A: Link Creation (First visit to the current node)
                if (predecessor->right == nullptr) {
                    // 1. Thread the predecessor's right pointer to the current node's right child.
                    //    (This link is specific to Preorder Flattening for the new list structure).
                    //    The current node's RIGHT child (the original one) becomes the right child
                    //    of the original LEFT subtree's last node.

                    // The standard approach (more intuitive for flattening):

                    // 1. Thread the predecessor's right to the node's original RIGHT child (for temporary storage)
                    //    *The key insight for PREORDER flattening is that the rightmost node of the left subtree
                    //    will be the node that precedes the current node's original right subtree.*

                    // 1. Save the original right subtree
                    TreeNode* tempRight = current->right;

                    // 2. Set the current node's right child to its left child.
                    current->right = current->left;

                    // 3. Find the end of the new (flattened) right chain (which was the old left subtree).
                    //    The predecessor found previously is actually the *end* of the old left subtree.

                    // 4. Attach the original right subtree to the end of the new chain.
                    predecessor->right = tempRight;

                    // 5. Set the left child to nullptr (as per flattening requirement).
                    current->left = nullptr;

                    // 6. Move to the new right child (the old left child)
                    current = current->right;
                }
                // Subcase 2B: Link Breakage (Second visit to the current node - This is unnecessary for PREORDER flattening)
                // In Preorder Traversal, once the thread is created, we never need to return to 'current'
                // through the predecessor's pointer. We only visit the node once, restructure, and move on.
                // Therefore, the 'else if' block for breaking the thread is REMOVED/simplified.

                /*
                // If you MUST use the thread-breaking pattern for an IN-PLACE modification structure:
                else if (predecessor->right == current) {
                    // Break the thread. In Preorder, we don't need to process the node here.
                    predecessor->right = nullptr;
                    current = current->right;
                }
                */
            }
        }
    }
};

// Print the preorder traversal of the
// Orignal Binary Tree
void printPreorder(TreeNode* root) {
    if (!root) {
        return;
    }
    cout << root->val << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

// Print the Binary Tree along the 
// Right Pointers after Flattening
void printFlattenTree(TreeNode* root) {
    if (!root) {
        return;
    }
    cout << root->val << " ";
    printFlattenTree(root->right);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->right = new TreeNode(6);
    root->right->right = new TreeNode(7);
    root->right->left = new TreeNode(8);

    Solution sol;

    cout << "Binary Tree Preorder: ";
    printPreorder(root);
    cout << endl;

    sol.flatten3(root);

    cout << "Binary Tree After Flatten: ";
    printFlattenTree(root);
    cout << endl;
	return 0;
}
