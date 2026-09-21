#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

/*
    Problem Statement:
    ------------------
    Merge K Sorted Arrays (variation of LeetCode 23)

    Given a 2D array `mat` where each row is sorted in ascending order,
    merge all rows into one sorted array.

    This is the array version of "Merge K Sorted Lists" (LC 23).
    Same K-way merge pattern, but with arrays instead of linked lists.

    Examples:
    ---------

    Example 1:
        Input:  mat = [[1, 4, 5],
                       [1, 3, 4],
                       [2, 6]]
        Output: [1, 1, 2, 3, 4, 4, 5, 6]

    Example 2:
        Input:  mat = [[1, 2],
                       [3, 4],
                       [5, 6]]
        Output: [1, 2, 3, 4, 5, 6]

    Approach: Min-Heap (K-way Merge)
    ----------------------------------
    Same idea as merging K sorted linked lists:
        - Each row is a "sorted list."
        - Start with the first element of each row in a min-heap.
        - Pop the smallest, add to result.
        - Push the next element from the same row (col+1).
        - Repeat until the heap is empty.

    The Node struct tracks (value, row, col) so we know which row
    the popped element came from and where to get the next one.

    Why track (row, col) instead of just the value?
    -------------------------------------------------
    After popping a value, we need to know "which row did this come
    from?" and "what's the next element in that row?" Without row/col,
    we'd have no way to advance to the next element.

    Dry Run (mat = [[1,4,5],[1,3,4],[2,6]]):
    ------------------------------------------

    Heap (min): [(1,r=0,c=0), (1,r=1,c=0), (2,r=2,c=0)]

    Pop (1,r=0,c=0) → result=[1].     Push (4,r=0,c=1).
    Pop (1,r=1,c=0) → result=[1,1].   Push (3,r=1,c=1).
    Pop (2,r=2,c=0) → result=[1,1,2]. Push (6,r=2,c=1).
    Pop (3,r=1,c=1) → result=[...,3]. Push (4,r=1,c=2).
    Pop (4,r=0,c=1) → result=[...,4]. Push (5,r=0,c=2).
    Pop (4,r=1,c=2) → result=[...,4]. No next (col+1=3 >= row size 3).
    Pop (5,r=0,c=2) → result=[...,5]. No next.
    Pop (6,r=2,c=1) → result=[...,6]. No next (col+1=2 >= row size 2).

    Result: [1, 1, 2, 3, 4, 4, 5, 6] ✓

    Important: rows can have different lengths. Use mat[row].size()
    for the bounds check, not a global cols variable.

    Complexity Analysis:
    --------------------
    Time:  O(N log K) — N = total elements across all rows,
                         K = number of rows. Each push/pop is O(log K).
    Space: O(K) — heap holds at most K elements (one per row).

*/



class Solution {
private:
	struct Node {
		int num;
		int i, j;
		Node(int num, int i, int j) {
			this->num = num;
			this->i = i;
			this->j = j;
		}
	};

public:
	vector<int> mergeArrays(vector<vector<int>>& mat) {
		int rows = mat.size();
		int cols = mat[0].size();

		auto cmp = [](Node*& a, Node*& b) {
			return a->num > b->num;
		};
		priority_queue<Node*, vector<Node*>, decltype(cmp)> pq;     // min-heap

		for (int row = 0; row < rows; row++) {
			pq.push(new Node(mat[row][0], row, 0));
		}

		vector<int> result;
		while (!pq.empty()) {
			// 1. Extract the minimum element from the heap
			Node* node = pq.top();
			pq.pop();

			// 2. Add the minimum element to the result
			result.push_back(node->num);

			// 3. Insert the next element from the same row into the heap
			int row = node->i;
			int col = node->j;

			// Check if there is a next element in the same row
			if (col + 1 < mat[row].size()) {
				auto nextNode = new Node(mat[row][col + 1], row, col + 1);
				pq.push(nextNode);
			}
		}

		return result;
	}
};
int main() {
    Solution obj;

    // Example 1: rows of different lengths
    vector<vector<int>> mat1 = {
        {1, 4, 5},
        {1, 3, 4},
        {2, 6}
    };
    auto result1 = obj.mergeArrays(mat1);
    cout << "Example 1: ";
    for (int i : result1) cout << i << " ";
    cout << endl;
    // Expected: 1 1 2 3 4 4 5 6

    // Example 2: all same length
    vector<vector<int>> mat2 = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    auto result2 = obj.mergeArrays(mat2);
    cout << "Example 2: ";
    for (int i : result2) cout << i << " ";
    cout << endl;
    // Expected: 1 2 3 4 5 6

    // Example 3: single row
    vector<vector<int>> mat3 = {
        {10, 20, 30}
    };
    auto result3 = obj.mergeArrays(mat3);
    cout << "Example 3: ";
    for (int i : result3) cout << i << " ";
    cout << endl;
    // Expected: 10 20 30

    return 0;
}