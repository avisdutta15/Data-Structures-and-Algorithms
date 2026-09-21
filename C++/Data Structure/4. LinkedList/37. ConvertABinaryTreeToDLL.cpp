#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

/*
	Problem Statement:
	-----------------
	
    Approach 1:
    Recursive Inorder + Build list from front

    Approach 2:
    Iterative Inorder   [TODO]

    Approach 3:
    Morris Inorder      [TODO]
*/

class ListNode {
public:
	int data;
	ListNode* next;
	ListNode() : data(0), next(nullptr) {}
	ListNode(int data) : data(data), next(nullptr) {}
	ListNode(int data, ListNode* next) : data(data), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    //TreeNode* tail = nullptr;
    void binaryTreeToDLLUtil(TreeNode* root, TreeNode*& head, TreeNode*& tail) {
        if (root == nullptr)
            return;
        binaryTreeToDLLUtil(root->left, head, tail);
        
        if (head == nullptr) {
            head = root;
            tail = root;
            root->left = nullptr;
        }
        else{
            tail->right = root;
            root->left = tail;
            tail = root;
        }

        binaryTreeToDLLUtil(root->right, head, tail);
    }
public:
    TreeNode* binaryTreeToDLL(TreeNode *root) {
        if (root == nullptr)
            return root;

        TreeNode* head = nullptr, *tail = nullptr;
        binaryTreeToDLLUtil(root, head, tail);
        return head;
    }
    
};

// Print the preorder traversal of the
// Orignal Binary Tree
void printInorder(TreeNode* root) {
    if (!root) {
        return;
    }    
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
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
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    Solution sol;

    cout << "Binary Tree Preorder: ";
    printInorder(root);
    cout << endl;

    root = sol.binaryTreeToDLL(root);

    cout << "Binary Tree After Flatten: ";
    printFlattenTree(root);
    cout << endl;
	return 0;
}

void printList(ListNode* node) {
    if (node == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    while (node != nullptr) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}
