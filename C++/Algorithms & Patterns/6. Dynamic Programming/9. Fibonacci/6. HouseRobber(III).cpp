#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <string>

using namespace std;

/*
	https://www.youtube.com/watch?v=Nt0IqkcxG80
	Problem Statement:
	------------------
	The thief has found himself a new place for his thievery again. There is only one entrance to this area, called root.
	Besides the root, each house has one and only one parent house. 
	After a tour, the smart thief realized that all houses in this place form a binary tree. 
	It will automatically contact the police if two directly-linked houses were broken into on the same night.

	Given the root of the binary tree, return the maximum amount of money the thief can rob without alerting the police.

	Examples:
	---------
	Input: 
			     3
				/ \
			   2   3
			  / \   \
			 1   3   1
	Output: 7
	Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.

	Input: 
			     3
				/ \
			   4   5
			  / \   \
			 1   3   1
	Output: 9
	Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.

	
	Constraints:
	------------
	

	Approach:
	--------
	Recursive
	---------
	If we rob the current house, we get its money but we're forced to skip its direct children 
	(to avoid alerting the police). However, we can still rob the grandchildren and beyond.
	
	If we don't rob the current house, we're free to make the optimal choice for each child - 
	we can rob them or not, whatever gives us more money.

		rob()
			if root is nullptr
				return 0;

			// Option 1: Rob current house
			int robCurrentHouse = root->val;
			//also rob the grandchildren
			if(root->left!=nullptr)
				robCurrentHouse += rob(root->left->left) + rob(root->left->right);
			if(root->right!=nullptr)
				robCurrentHouse += rob(root->right->left) + rob(root->right->right);

			// Option 2: Donot Rob the current house
			// So we can rob its children
			int dontRobCurrentHouse = rob(root->left) + rob(root->right);

			return max(robCurrentHouse, dontRobCurrentHouse);

	Time Complexity = O(4^N) 


	Memoization:
	-----------
	To fix the overlapping subproblems, we can cache the result of each TreeNode* once it is calculated. 
	Since tree nodes don't have integer indices, we use a Hash Map (unordered_map<TreeNode*, int>) 
	to store the max money we can extract starting from any given node.

	Time Complexity: O(N) because every node is calculated exactly once.
	Space Complexity: O(N) for the recursion stack and the unordered_map.


	Bottom Up:
	----------
	Instead of calculating from the top down, we can use a Post-Order Traversal to calculate 
	from the leaves bubbling up to the root (the Tree equivalent of "Bottom-Up").

	For every node, we return an array/pair of two integers:
		[0] = The max money if we DO NOT rob this node.
		[1] = The max money if we DO rob this node.
	By returning both states simultaneously, a parent node instantly knows exactly what it needs 
	from its children without ever needing to look at its grandchildren!

	The State Transitions for a Parent Node:
		rob_parent = parent.val + left_child.not_robbed + right_child.not_robbed
		skip_parent = max(left_child.robbed, left_child.not_robbed) + max(right_child.robbed, right_child.not_robbed)
*/

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// Recursive
class Solution1 {
public:
	int rob(TreeNode* root) {
		if (root == nullptr)
			return 0;

		// Two Options:
		// Option 1: Rob root and add the maximum recieved by robLeftChildChildren and robRightChildChildren
		int robLeftChildChildren = 0;
		int robRightChildChildren = 0;

		// rob the left child
		if (root->left != nullptr) {
			robLeftChildChildren = rob(root->left->left) + rob(root->left->right);
		}
		if (root->right != nullptr) {
			robRightChildChildren = rob(root->right->left) + rob(root->right->right);
		}
		
		int robRoot = root->val + robLeftChildChildren + robRightChildChildren;

		// Option 2: Donot rob root and add the maximum recieved by robLeftChildChildren and robRightChildChildren
		int donotRobRoot = rob(root->left) + rob(root->right);

		return max(robRoot, donotRobRoot);
	}
};

// Top Down: Memoization
class Solution2 {
	unordered_map<TreeNode*, int> memo;
public:
	int rob(TreeNode* root) {
		if (root == nullptr)
			return 0;

		if (memo.find(root) != memo.end())
			return memo[root];

		// Two Options:
		// Option 1: Rob root and add the maximum recieved by robLeftChildChildren and robRightChildChildren
		int robLeftChildChildren = 0;
		int robRightChildChildren = 0;

		// rob the left child
		if (root->left != nullptr) {
			robLeftChildChildren = rob(root->left->left) + rob(root->left->right);
		}
		if (root->right != nullptr) {
			robRightChildChildren = rob(root->right->left) + rob(root->right->right);
		}

		int robRoot = root->val + robLeftChildChildren + robRightChildChildren;

		// Option 2: Donot rob root and add the maximum recieved by robLeftChildChildren and robRightChildChildren
		int donotRobRoot = rob(root->left) + rob(root->right);

		return memo[root] = max(robRoot, donotRobRoot);
	}
};

// Bottom Up
class Solution3 {
private:
	// at node root, what is the max value i can get by {robbing it and not robbin it}.
	// {max value by robbing root, max value by not robbing root}
	pair<int, int> solve(TreeNode* root) {
		// If the root is empty then I cannot rob
		if (root == nullptr) {
			return { 0, 0 };
		}

		// If the node is leaf then I can get 
		// {max value by robbing root : root->value, max value by not robbing root : 0}
		if (root->left == nullptr && root->right == nullptr) {
			return { root->val, 0 };
		}

		// Traverse the left and right subtrees
		auto [robLeft, donotRobLeft] = solve(root->left);
		auto [robRight, donotRobRight] = solve(root->right);

		// 2 Cases:
		// 1. Rob Root
		int robRoot = root->val + donotRobLeft + donotRobRight;

		// 2. If I donot rob the root. Then I can rob either of the following.
		//	rob left
		//	donot rob left
		//	rob right
		//	donot rob right
		// I will choose the maximum loot value out of these 2 children
		int donotRobRoot = max(robLeft, donotRobLeft) + max(robRight, donotRobRight);

		return { robRoot, donotRobRoot };
	}
public:
	int rob(TreeNode* root) {
		auto [robRoot, donotRobRoot] = solve(root);

		// return the max amount i can get by
		// {robbing root, not robbing root}
		return max(robRoot, donotRobRoot);
	}
};

int main() {
    Solution3 obj;
	TreeNode *root = new TreeNode(3);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->right = new TreeNode(3);
	root->right->right = new TreeNode(1);
	cout << obj.rob(root) << endl;

	return 0;
}