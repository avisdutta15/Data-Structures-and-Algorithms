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
	Given a weighted undirected graph and a source vertex, find the shortest
	distance from the source to all other vertices (Single Source Shortest Path).

	Example:
	--------
	        4         6
	   0 ------- 1 ------- 4
	   |       / |         |
	 8 |    3/   | (not    | 10
	   |   /     |  direct)|
	   2 ------- 3 --------+
	        2

	  Adjacency:
	    0: (1,4), (2,8)
	    1: (0,4), (2,3), (4,6)
	    2: (0,8), (1,3), (3,2)
	    3: (2,2), (4,10)
	    4: (1,6), (3,10)

	  Shortest distances from src=0:
	    0->0: 0
	    0->1: 4        (0->1)
	    0->2: 7        (0->1->2)
	    0->3: 9        (0->1->2->3)
	    0->4: 10       (0->1->4)

	Approach:
	---------
	Dijkstra's Algorithm using a min-heap (priority queue):
	  1. Initialize all distances to INF, source distance to 0.
	  2. Push source into the min-heap as {0, src}.
	  3. Extract the vertex with minimum distance.
	  4. For each neighbour, if a shorter path is found (relax), update
	     its distance, record its parent, and push it into the heap.
	  5. Repeat until the heap is empty.
	  Time:  O((V + E) log V)
	  Space: O(V)
*/

// Dijkstra's Algorithm
class Solution {
public:
	vector<vector<int>> singleSourceShortestPath(vector<vector<pair<int, int>>>& adj, int src) {
		int V = adj.size();

		// INITIALIZE SINGEL SOURCE
		vector<int> distance(V, INT_MAX);
		vector<int> parent(V, -1);
		priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
		distance[src] = 0;
		Q.push({0, src});

		// WHILE WE HAVE VERTICES WHOSE SHORETEST PATH IS STILL AN ESTIMATE
		while (!Q.empty()) {

			// EXTRACT MIN
			auto [nodeWeight, node] = Q.top();
			Q.pop();

			// Remove the processed node from the set
        	st.erase(st.begin());

			// FOR EACH VERTEX ADJACENT TO NODE, RELAX IT
			for (auto neighbourInfo : adj[node]) {
				int neighbour = neighbourInfo.first;
				int edgeWeight = neighbourInfo.second;
				
				// RELAX
				if (distance[neighbour] > distance[node] + edgeWeight) {
					distance[neighbour] = distance[node] + edgeWeight;
					parent[neighbour] = node;
					Q.push({distance[neighbour], neighbour});
				}
			}
		}

		return vector<vector<int>>{distance, parent};
	}
};

void printPath(vector<int>& parent, int v) {
	if (parent[v] == -1) { 
		cout << v; 
		return; 
	}
	printPath(parent, parent[v]);
	cout << " " << v;
}

void printParent(vector<int>& parent) {
	for (int i = 0; i < (int)parent.size(); i++) {
		cout << "Path to " << i << ": ";
		printPath(parent, i);
		cout << "\n";
	}
}

int main() {
	Solution obj;
	int src = 0;

	vector<vector<pair<int, int>>> adj(5);
	adj[0] = { {1,4}, {2,8} };
	adj[1] = { {0,4}, {4,6}, {2,3} };
	adj[2] = { {0,8}, {3,2}, {1,3} };
	adj[3] = { {2,2}, {4,10} };
	adj[4] = { {1,6}, {3,10} };

	auto result = obj.singleSourceShortestPath(adj, src);
	auto distance = result[0];
	auto parent = result[1];

	for (int i : distance) {
		cout << i << " ";
	}

	cout << endl;

	printParent(parent);
	
	return 0;
}