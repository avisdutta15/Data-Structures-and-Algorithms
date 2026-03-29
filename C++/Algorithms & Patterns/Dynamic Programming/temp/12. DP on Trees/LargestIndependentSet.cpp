#include <bits/stdc++.h>
using namespace std;

struct Node{
    Node *left;
    int data;
    Node *right;
    Node(int x): left(NULL), data(x), right(NULL){}
};

class Solution{
    public:
        int sizeOfLargestIndependentSet(Node *root){
            if(!root)
                return 0;

            int sizeExclude = sizeOfLargestIndependentSet(root->left) + sizeOfLargestIndependentSet(root->right);
            int sizeInclude = 1;

            if(root->left)
                sizeInclude = sizeInclude + sizeOfLargestIndependentSet(root->left->left)
                                          + sizeOfLargestIndependentSet(root->left->right);
            if(root->right) 
                sizeInclude = sizeInclude + sizeOfLargestIndependentSet(root->right->left)
                                          + sizeOfLargestIndependentSet(root->right->right);
                                          
            return max(sizeInclude, sizeExclude);
        }
};

int main(){
    Node *root = new Node(20);  
    root->left = new Node(8);  
    root->left->left = new Node(4);  
    root->left->right = new Node(12);  
    root->left->right->left = new Node(10);  
    root->left->right->right = new Node(14);  
    root->right = new Node(22);  
    root->right->right = new Node(25);

    Solution obj;
    cout<<obj.sizeOfLargestIndependentSet(root);
}