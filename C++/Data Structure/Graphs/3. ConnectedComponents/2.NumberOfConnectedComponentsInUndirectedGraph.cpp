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
	You have an undirected graph of n nodes labeled from 0 to n - 1. 
	You are given an integer n and an array edges where edges[i] = [aᵢ, bᵢ] 
	indicates that there is an edge between aᵢ and bᵢ in the graph.
	
	Return the number of connected components in the graph.


	Example:
	--------
	Input: n = 5, edges = [[0,1],[1,2],[3,4]]
	Output: 2

	Input: n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
	Output: 1
	
	Approach:
	---------
	Traversal (DFS/BFS).

	Time Complexity:
	----------------
	O(V + E)
*/


// DFS
class Solution1 {
private:
	void DFS(int u, vector<vector<int>>& adj, vector<bool>& visited) {
		visited[u] = true;

		for (int v : adj[u]) {
			if (visited[v] == false) {
				DFS(v, adj, visited);
			}
		}
	}
public:
	int countComponents(int n, vector<vector<int>>& edges) {
		// Build adjacency list
		vector<vector<int>> adj(n);
		for (auto& e : edges) {
			adj[e[0]].push_back(e[1]);
			adj[e[1]].push_back(e[0]);
		}

		vector<bool> visited(n, false);
		int components = 0;

		// For each unvisited node, start a DFS — that's one new component
		for (int i = 0; i < n; i++) {
			if (visited[i] == false) {
				DFS(i, adj, visited);
				components++;
			}
		}

		return components;
	}
};


// BFS
class Solution {
private:
	void BFS(int src, vector<vector<int>>& adj, vector<bool>& visited) {
		queue<int> q;
		q.push(src);
		visited[src] = true;

		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int v : adj[u]) {
				if (!visited[v]) {
					visited[v] = true;
					q.push(v);
				}
			}
		}
	}
public:
	int countComponents(int n, vector<vector<int>>& edges) {
		// Build adjacency list
		vector<vector<int>> adj(n);
		for (auto& e : edges) {
			adj[e[0]].push_back(e[1]);
			adj[e[1]].push_back(e[0]);
		}

		vector<bool> visited(n, false);
		int components = 0;

		// For each unvisited node, start a BFS — that's one new component
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				BFS(i, adj, visited);
				components++;
			}
		}

		return components;
	}
};



int main() {
	

	return 0;
}