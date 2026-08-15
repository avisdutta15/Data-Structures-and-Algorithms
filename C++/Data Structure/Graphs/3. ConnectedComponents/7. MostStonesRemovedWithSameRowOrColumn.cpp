#include <algorithm>
#include <iostream>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

/*
	https://www.youtube.com/watch?v=ZsGTpXm966E (DFS)
    https://www.youtube.com/watch?v=OwMNX8SPavM (DSU)

	Problem Statement:
	------------------
	On a 2D plane, we place n stones at some integer coordinate points.
    Each coordinate point may have at most one stone.

    A stone can be removed if it shares either the same row or the same column 
    as another stone that has not been removed.

    Given an array stones of length n where stones[i] = [xi, yi] represents the 
    location of the ith stone, return the largest possible number of stones that can be removed.
	
    Example:
	--------
    Example 1:

    Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
    Output: 5
    Explanation: One way to remove 5 stones is as follows:
    1. Remove stone [2,2] because it shares the same row as [2,1].
    2. Remove stone [2,1] because it shares the same column as [0,1].
    3. Remove stone [1,2] because it shares the same row as [1,0].
    4. Remove stone [1,0] because it shares the same column as [0,0].
    5. Remove stone [0,1] because it shares the same row as [0,0].
    Stone [0,0] cannot be removed since it does not share a row/column with another stone still on the plane.
    
    Example 2:

    Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
    Output: 3
    Explanation: One way to make 3 moves is as follows:
    1. Remove stone [2,2] because it shares the same row as [2,0].
    2. Remove stone [2,0] because it shares the same column as [0,0].
    3. Remove stone [0,2] because it shares the same row as [0,0].
    Stones [0,0] and [1,1] cannot be removed since they do not share a row/column with another stone still on the plane.
    
    Example 3:

    Input: stones = [[0,0]]
    Output: 0
    Explanation: [0,0] is the only stone on the plane, so you cannot remove it.

	Approach: 
    ---------
    A stone can be removed if there exists at least one other stone in the same row or same column. 
    In other words, you can remove a stone as long as it's not the last one in its connected group.

    Component 1: size K₁ → remove K₁ - 1
    Component 2: size K₂ → remove K₂ - 1
    ...
    Component C: size Kc → remove Kc - 1

    Total removed = (K₁-1) + (K₂-1) + ... + (Kc-1)
                 = (K₁ + K₂ + ... + Kc) + (-1 + -1 + ... + -1)
                 = (K₁ + K₂ + ... + Kc) - (1 + 1 + ... + 1)
                 = N - C
    Where N = total stones, C = number of connected components.
    How K₁ + K₂ + ... + Kc = N ? 
    Because each stone belongs to exactly one component.

    How many 1s ? 
    Exactly C (number of connected components), because we have C connected components 
    and we are subtracting one for each component.
    
    Time Complexity = O(N²)
    Space Complexity = O(N)

*/

class Solution {
public:
    int n;
    void DFS(vector<vector<int>>& stones, int index, vector<bool>& visited) {
        visited[index] = true;

        // current stone coordinates
        int r = stones[index][0];
        int c = stones[index][1];

        // Traverse all the nodes and find nodes with same row or column
        for (int i = 0; i < n; i++) {
            if (!visited[i] && ((stones[i][0] == r || (stones[i][1] == c)))) {
                DFS(stones, i, visited);
            }
        }
    }
    int removeStones(vector<vector<int>>& stones) {
        n = stones.size();
        vector<bool> visited(n, false);

        int components = 0;
        for (int i = 0; i < n; i++) {
            if (visited[i] == false) {
                DFS(stones, i, visited);
                components++;
            }            
        }

        return n - components;
    }
};

int main() {


	return 0;
}