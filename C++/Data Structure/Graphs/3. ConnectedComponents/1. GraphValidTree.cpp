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
	Problem Statement:
	------------------
	Given n nodes labeled from 0 to n - 1 and a list of undirected edges 
	(each edge is a pair of nodes), write a function to check whether these 
	edges make up a valid tree.


	Example:
	--------
	Input: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
	Output: true

	Input: n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
	Output: false
	
	Approach:
	---------
	A graph is a valid tree if and only if:
	1. It is connected (all nodes reachable from any node)
	2. It has no cycles

	A quick property: a tree with N nodes always has exactly N-1 edges. So we can check:
	- If edges ≠ N-1 → not a tree (too few = disconnected, too many = has cycle)
	- If edges == N-1 → just verify connectivity (BFS/DFS from any node visits all nodes)

	Another approach. Do DFS from 0 and parent node as -1.
	DFS returns if cycle exists in the undirected graph.
	at last check if all the nodes were visited or not for connectivity.

	Time Complexity:
	----------------
	O(V + E)
	- Each node is visited exactly once (visited[u] = true prevents re-entry) → O(V)
	- Each edge is examined exactly twice (once from each endpoint in the undirected adjacency list) → O(2E) = O(E)
	- The connectivity check at the end iterates the visited array → O(V)
*/

class Solution {
private:
	bool DFS(unordered_map<int, vector<int>>& graph, int u, int parent, vector<bool>& visited) {
		visited[u] = true;

		for(auto v: graph[u]) {
			// if the neighbor is not visited
			if (!visited[v]) {
				// recursively visit the neighbor
				if (DFS(graph, v, u, visited) == true)
					return true;
			}
			// if the neighbor is parent, then skip it
			else if (v == parent){
				continue;
			} 
			// if the neighbor is already visited and is not parent then its a back edge.
			// i.e. there is a cycle
			else if (v != parent) {
				return true;
			}
		}
		return false;
	}

public:
	bool validTree(int n, vector<vector<int>>& edges) {
		
		// build the graph
		unordered_map<int, vector<int>> graph;
		for(auto edge: edges) {
			graph[edge[0]].push_back(edge[1]);
			graph[edge[1]].push_back(edge[0]);
		}

		vector<bool> visited(n, false);

		// DFS tells if the graph has loop. parent of 0 is -1
		if (DFS(graph, 0, -1, visited) == true)
			return false;

		for (auto x : visited) {
			if (x == false)
				return false;
		}
		return true;
	}
};

int main() {
	

	return 0;
}