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
	You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional 
	roads between some intersections. The inputs are generated such that you can reach any intersection 
	from any other intersection and that there is at most one road between any two intersections.

	You are given an integer n and a 2D integer array roads where roads[i] = [ui, vi, timei] means 
	that there is a road between intersections ui and vi that takes timei minutes to travel. 
	You want to know in how many ways you can travel from intersection 0 to intersection n - 1 
	in the shortest amount of time.

	Return the number of ways you can arrive at your destination in the shortest amount of time. 
	Since the answer may be large, return it modulo 109 + 7.

	Example:
	--------
	Input: n = 7, roads = [[0,6,7],
						   [0,1,2],
						   [1,2,3],
						   [1,3,3],
						   [6,3,3],
						   [3,5,1],
						   [6,5,1],
						   [2,5,1],
						   [0,4,5],
						   [4,6,2]]
	Output: 4
	Explanation: The shortest amount of time it takes to go from intersection 0 to 
	intersection 6 is 7 minutes. The four ways to get there in 7 minutes are:
	- 0 ➝ 6
	- 0 ➝ 4 ➝ 6
	- 0 ➝ 1 ➝ 2 ➝ 5 ➝ 6
	- 0 ➝ 1 ➝ 3 ➝ 5 ➝ 6
	
	Approach 1: DFS with Backtracking
	---------------------------------
	Enumerate all possible paths from src to dst using DFS with backtracking. 
	Track the minimum cost found so far and count how many paths achieve it.

	Time Complexity : O(V!)

	Approach 2: Dijkstra's Algorithm
	----------------------
	Since we need to find the number of ways to reach from source to destination
	with minimum cost, we can modify the standard dijkstra algorithm.

	We use a ways[] array to keep track of number of ways to reach a node with minimum cost. 
	While doing standard dijkstra, 
		if we find a path 
			with lesser distance to a node, 
			we update the distance and also update the ways[] array with the ways to reach the parent node. 
		If we find a path 
			with equal distance to a node, 
			we simply add the ways to reach the parent node to the ways[] array for current node.

	The logic during relaxation:

		if (dist[u] + w < dist[v]) {
			// Found a SHORTER path to v — reset count
			dist[v] = dist[u] + w;
			ways[v] = ways[u];           // all ways to reach u can now reach v via this shorter path
		} else if (dist[u] + w == dist[v]) {
			// Found an EQUALLY short path to v — add more ways
			ways[v] += ways[u];          // ways through u are additional shortest paths to v
		}

	We return ways[destination];

	Example: 
		(2)          (3)
		+----> 1 -------->+
		|                  |
		|      (5)         v      (1)
   0 ---+----------------> 3 ----------> 4
		|                  ^
		|(10)         (3)  |
		+----> 2 ---------+

	Three paths from 0 to 4:

	0 →(5)→ 3 →(1)→ 4 = cost 6
	0 →(2)→ 1 →(3)→ 3 →(1)→ 4 = cost 6
	0 →(10)→ 2 →(3)→ 3 →(1)→ 4 = cost 14 (not shortest)
	
	Initialization:

	dist[]  = [0,   INF, INF, INF, INF]
	ways[]  = [1,   0,   0,   0,   0  ]
	
	Step 1: Pop node 0 (dist=0, ways=1)

	Relax 0→3: dist[3] = 0+5 = 5 < INF → shorter! dist[3]=5, ways[3] = ways[0] = 1
	Relax 0→1: dist[1] = 0+2 = 2 < INF → shorter! dist[1]=2, ways[1] = ways[0] = 1
	Relax 0→2: dist[2] = 0+10 = 10 < INF → shorter! dist[2]=10, ways[2] = ways[0] = 1
	dist[]  = [0, 2, 10, 5, INF]
	ways[]  = [1, 1, 1,  1, 0  ]
	
	Step 2: Pop node 1 (dist=2, ways=1) — smallest in PQ

	Relax 1→3: cost = 2+3 = 5. dist[3] = 5. Equal! → ways[3] += ways[1] = 1+1 = 2
	dist[]  = [0, 2, 10, 5, INF]
	ways[]  = [1, 1, 1,  2, 0  ]
	Node 3 now has 2 shortest paths (0→3 and 0→1→3), both cost 5.

	Step 3: Pop node 3 (dist=5, ways=2) — next smallest

	Relax 3→4: cost = 5+1 = 6 < INF → shorter! dist[4]=6, ways[4] = ways[3] = 2
	dist[]  = [0, 2, 10, 5, 6]
	ways[]  = [1, 1, 1,  2, 2]
	This is the key moment. When we relax 3→4, we don't just say "1 path to 4". 
	We say ways[4] = ways[3] = 2, because ALL shortest paths that reach node 3 can 
	extend to node 4 via edge 3→4. Since there are 2 shortest paths to node 3, there 
	are 2 shortest paths to node 4.

	Time Complexity : O(E * logV)
	
*/

// DFS : BruteForce
class Solution1 {
private:
	void DFS(unordered_map<int, vector<vector<int>>>& graph, int u, int destination, vector<bool> &visited, int currentPathCost, int& minPathCost, int& countOfPathWithMinCost) {
		visited[u] = true;

		if (u == destination) {
			if(currentPathCost < minPathCost) {
				minPathCost = currentPathCost;
				countOfPathWithMinCost = 1;
			} else if (currentPathCost == minPathCost) {
				countOfPathWithMinCost++;
			}
			visited[u] = false;
			return;
		}

		for (auto neighbour : graph[u]) {
			int v = neighbour[0];
			int time = neighbour[1];

			// early pruning. Traverse the path only if it can contribute to get the min cost.
			if (visited[v] == false && currentPathCost + time <= minPathCost) {
				DFS(graph, v, destination, visited, currentPathCost + time, minPathCost, countOfPathWithMinCost);
			}
		}

		visited[u] = false;
	}
public:
	int countPaths(int n, vector<vector<int>>& roads) {
		
		// Build the graph
		unordered_map<int, vector<vector<int>>> graph;
		for (auto road : roads) {
			int u = road[0];
			int v = road[1];
			int time = road[2];
			graph[u].push_back({ v, time });
			graph[v].push_back({ u, time });
		}

		int currentPathCost = 0;
		int minPathCost = INT_MAX;
		int countOfPathWithMinCost = 0;
		vector<bool> visited(n, false);

		DFS(graph, 0, n - 1, visited, currentPathCost, minPathCost, countOfPathWithMinCost);

		return countOfPathWithMinCost;
	}
};

// Dijkstra Algorithm
class Solution2 {
private:
	int mod = 1e9 + 7;
	int dijkstra(unordered_map<int, vector<vector<int>>>& graph, int source, int destination) {

		// Min Heap {distance, node}
		priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;

		// To store minimum cost to reach a node
		vector<long long> dist(100001, LLONG_MAX);

		// To store count of number of ways to reach a node with minimum cost
		vector<long long> countPath(100001, 0);

		// Initialize
		dist[source] = 0;
		countPath[source] = 1;
		pq.push({ 0, source });

		while (!pq.empty()) {
			auto current = pq.top();
			pq.pop();

			auto u = current.second;
			auto weight = current.first;

			// pruning
			if (weight > dist[u])
				continue;

			for (auto neighbour : graph[u]) {
				long long v = neighbour[0];
				long long edgeWeight = neighbour[1];

				// Relax the edge
				if (dist[u] + edgeWeight < dist[v]) {
					// Found a SHORTER path to nextNode — reset count
					dist[v] = dist[u] + edgeWeight;
					countPath[v] = countPath[u];           // all ways to reach currentNode can now reach nextNode via this shorter path
					pq.push({ dist[v], v });
				}
				else if (dist[u] + edgeWeight == dist[v]) {
					// Found an EQUALLY short path to nextNode — add more ways
					countPath[v] = (countPath[v] + countPath[u]) % mod;          // ways through currentNode are additional shortest paths to nextNode
				}
			}
		}

		return countPath[destination] % mod;
	}
public:
	int countPaths(int n, vector<vector<int>>& roads) {

		// Build the graph
		unordered_map<int, vector<vector<int>>> graph;
		for (auto road : roads) {
			int u = road[0];
			int v = road[1];
			int time = road[2];
			graph[u].push_back({ v, time });
			graph[v].push_back({ u, time });
		}

		return dijkstra(graph, 0, n - 1);
	}
};

int main() {
	

	return 0;
}