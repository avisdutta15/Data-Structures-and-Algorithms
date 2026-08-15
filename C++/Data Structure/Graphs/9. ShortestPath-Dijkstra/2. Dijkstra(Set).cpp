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
	Dijkstra's Algorithm using a set (ordered by {distance, node}):
	  1. Initialize all distances to INF, source distance to 0.
	  2. Insert source into the set as {0, src}.
	  3. Extract the vertex with minimum distance (begin()).
	  4. For each neighbour, if a shorter path is found (relax):
	       - Erase the stale {old_distance, neighbour} entry from the set.
	       - Update distance and parent.
	       - Insert fresh {new_distance, neighbour} into the set.
	  5. Repeat until the set is empty.

	  Time Complexity: O((V + E) log V)
	  ---------------------------------
	  - Set size is always <= V because stale entries are erased before
	    inserting updated ones, so at most one entry per vertex exists.
	  - V extractions via erase(begin()):     V  * O(log V) = O(V log V)
	  - E relaxations, each with erase+insert: E  * O(log V) = O(E log V)
	  - Total: O((V + E) log V)

	  Compare with priority_queue variant:    O(E log E) = O(E log V)
	  -----------------------------------------------------------------
	  - priority_queue does NOT support erase, so stale entries remain.
	  - Each of the E relaxations does one push -> heap grows up to O(E).
	  - Each push/pop costs O(log E), and we do O(E) of them.
	  - Total: O(E log E) which simplifies to O(E log V) since E <= V^2.
	  - Set variant has a tighter bound due to bounded set size O(V),
	    and avoids memory bloat on dense graphs.

	  Space: O(V)  (set holds at most V entries at any time)
*/

// Dijkstra's Algorithm
class Solution {
public:
	vector<vector<int>> singleSourceShortestPath(vector<vector<pair<int, int>>>& adj, int src) {
		int V = adj.size();

		// INITIALIZE SINGEL SOURCE
		vector<int> distance(V, INT_MAX);
		vector<int> parent(V, -1);
		set<pair<int, int>> Q;
		distance[src] = 0;
		Q.insert({0, src});

		// WHILE WE HAVE VERTICES WHOSE SHORETEST PATH IS STILL AN ESTIMATE
		while (!Q.empty()) {

			// EXTRACT MIN
			auto [nodeWeight, node] = *(Q.begin());
			Q.erase(Q.begin());

			// FOR EACH VERTEX ADJACENT TO NODE, RELAX IT
			for (auto neighbourInfo : adj[node]) {
				int neighbour = neighbourInfo.first;
				int edgeWeight = neighbourInfo.second;
				
				// RELAX
				if (distance[neighbour] > distance[node] + edgeWeight) {

					// DECREASE KEY
					if (Q.find({ distance[neighbour], neighbour }) != Q.end()) {
						Q.erase({ distance[neighbour], neighbour });
					}

					distance[neighbour] = distance[node] + edgeWeight;
					parent[neighbour] = node;
					Q.insert({distance[neighbour], neighbour});
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