#include <bits/stdc++.h>
using namespace std;

//Ref: https://www.youtube.com/watch?v=hQn61BjdA7M

/*
        1             1           2          3        3
         \             \         / \        /        /
          2             3       1   3      2        1
           \           /                  /          \
            3         2                  1            2

        5             5          6           7       7
         \             \        / \         /       /
          6             7      5   7       6       5
           \           /                  /         \
            7         6                  5           6
    
    Suppose we have 1,2,3,4,5,6,7. We are at 4.
    We generated all the subtress using {1,2,3} and {5,6,7}
    Now we have to attach 4 as the root of all the possiblities.
    So with 4 as root and 1->2->3 [first tree above] as left subtree,
    we can have all the 4 trees(2nd row) as the right subtree.
    Similarly with 4 as root and 1->3->2 [second tree above] as left subtree,
    we can have all the 4 trees(2nd row) as the right subtree.

    for(auto l : leftsubtrees){
        for(auto r : rightsubtrees){
            TreeNode root = new TreeNode(i);
            root->left = l;
            root->right = r;
            trees.push_back(root);
        }
    }  

    return root;

*/
struct TreeNode{
    TreeNode *left;
    TreeNode *right;
    int data;
    TreeNode(int x): left(NULL), right(NULL), data(x){}
};

//Naive: Recursive
class Solution{
    public:
    vector<TreeNode *> generateTreesUtil(int start, int end){
        vector<TreeNode *> trees;
        if(start>end){
            trees.push_back(NULL);
            return trees;
        }
        
        /*  iterating through all values from start to end  for constructing 
            left and right subtree recursively with i as the root node
        */
        for(int i=start; i<=end; i++){
            vector<TreeNode *> left = generateTreesUtil(start, i-1);
            vector<TreeNode *> right = generateTreesUtil(i+1, end);
            
            /*  now looping through all left and right subtrees and connecting 
                them to ith root  below  remember T[i] = T[j] * T[i-j-1] where j=0 to i
            */
            for(auto l : left){
                for(auto r : right){
                    TreeNode *root = new TreeNode(i);
                    root->left = l;
                    root->right = r;
                    trees.push_back(root);
                }
            }
        }
        return trees;
    }

    vector<TreeNode *> generateTrees(int n){
        if(n==0)
            return vector<TreeNode*>();

        return generateTreesUtil(1, n);
    }
};

void preorder(TreeNode *root){
    if(!root)
        return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

//Recursive +  Memoization - top down DP
class Solution2 {
    unordered_map<string, vector<TreeNode *>> Map;
public:
    vector<TreeNode *> generateTreesUtil(int start, int end){
        vector<TreeNode *> trees;
        if(start>end){
            trees.push_back(NULL);
            return trees;
        }
        
        string key = to_string(start) + "|" + to_string(end);
        if(Map.count(key)>0)
            return Map[key];
        
        /*  iterating through all values from start to end  for constructing 
            left and right subtree recursively with i as the root node
        */
        for(int i=start; i<=end; i++){
            vector<TreeNode *> left = generateTreesUtil(start, i-1);
            vector<TreeNode *> right = generateTreesUtil(i+1, end);
            
            /*  now looping through all left and right subtrees and connecting 
                them to ith root  below  remember T[i] = T[j] * T[i-j-1] where j=0 to i
            */
            for(auto l : left){
                for(auto r : right){
                    TreeNode *root = new TreeNode(i);
                    root->left = l;
                    root->right = r;
                    trees.push_back(root);
                }
            }
        }
        return Map[key] = trees;
    }
    
    vector<TreeNode*> generateTrees(int n) {
        return generateTreesUtil(1, n);
    }
};

int main(){
    Solution obj;
    vector<TreeNode*> trees = obj.generateTrees(3);
    for(auto root : trees){
        preorder(root);
        cout<<endl;
    }
}