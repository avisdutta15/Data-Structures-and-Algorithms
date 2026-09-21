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
	https://www.youtube.com/watch?v=FYrl7iz9_ZU

	Problem Statement:
	------------------
	There are n computers numbered from 0 to n - 1 connected by ethernet cables connections 
	forming a network where connections[i] = [ai, bi] represents a connection between 
	computers ai and bi. Any computer can reach any other computer directly or indirectly 
	through the network.

	You are given an initial computer network connections. You can extract certain cables 
	between two directly connected computers, and place them between any pair of disconnected 
	computers to make them directly connected.

	Return the minimum number of times you need to do this in order to make all the computers 
	connected. If it is not possible, return -1.

 
    Example:
	--------
    Component 1:   Component 2:     All connected:
	  0 --- 1        3 --- 4          0 --- 1 --- 3 --- 4
	  |   /                           |
	  | /                             2 
	  2



	Approach: 
    ---------
	To connect C disconnected components into one, you need exactly C-1 edges (like a spanning tree across components). These edges must come from "extra" cables — edges within an already-connected component that are redundant (removing them doesn't disconnect anything).

	An edge is "extra" if both endpoints are already in the same component (it forms a cycle). We can repurpose these cables to bridge different components.

	Before:                          After (repurpose extra edge):

	Component 1:   Component 2:     All connected:
	  0 --- 1        3 --- 4          0 --- 1 --- 3 --- 4
	  |   /                           |
	  | /                             2 
	  2

	Before:											After (repurpose extra edge):

	Component 1:   Component 2:  Component 2:			All connected:
	  0 --- 1        3 --- 4		5----6          	0 --- 1 --- 3 --- 4       5---6
	  |   /												|
	  | /												2
	  2


	Extra edges = 1->2. 1 edge, Components = 3, Need 3-1 = 2 edge. x [Not possible]

	Approach:

	1. Process each edge with DSU:
		If both nodes share same root → it's an extra edge (count it)
		Otherwise → union them
	2. Count connected components (nodes where parent[i] == i)
	3. If extraEdges ≥ components - 1 → return components - 1 (minimum operations)
	   Otherwise → impossible, return -1
	
	Time: O(N + E · α(N)) ≈ O(N + E) Space: O(N)

*/

class DSU {
public:
	vector<int> parent;
	vector<int> rank;

	DSU(int N) {
		parent = vector<int>(N);
		rank = vector<int>(N, 0);
		for (int i = 0; i < N; i++) 
			parent[i] = i;
	}

	int find(int x) {
		if (parent[x] == x)
			return x;
		return parent[x] = find(parent[x]);
	}

	void Union(int x, int y) {
		int x_parent = find(x);
		int y_parent = find(y);
		if (x_parent == y_parent) return;

		if (rank[x_parent] > rank[y_parent]) {
			parent[y_parent] = x_parent;
		}
		else if (rank[y_parent] > rank[x_parent]) {
			parent[x_parent] = y_parent;
		}
		else {
			parent[y_parent] = x_parent;
			rank[x_parent]++;
		}
	}
};

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
		
		DSU disjointSet(n);
		
		int extraEdges = 0;
		int numberOfConnectedComponents = 0;

		// for every edge check if they belong to the same parent
		// if yes then it's an extraEdge else unite them
		for(auto connection : connections) {
			if(disjointSet.find(connection[0]) == disjointSet.find(connection[1])) {
				extraEdges++;
			}
			else {
				disjointSet.Union(connection[0], connection[1]);
			}
		}

		// find the number of components
		for (int i = 0; i < disjointSet.parent.size(); i++) {
			if(disjointSet.parent[i] == i)
				numberOfConnectedComponents++;
		}

		// We need components - 1 edges to connect all the components
		int requiredEdges = numberOfConnectedComponents - 1;
		if (extraEdges >= requiredEdges)
			return requiredEdges;

		// Else impossible to connect all computers with the extra edges
		return -1;
    }
};


int main() {

	return 0;
}