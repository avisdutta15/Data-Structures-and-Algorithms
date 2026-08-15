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
	https://www.youtube.com/watch?v=9XybHVqTHcQ (why Dijkstra won't work)
	https://www.youtube.com/watch?v=VmUpydhNmuw (BFS)
    https://leetcode.com/problems/cheapest-flights-within-k-stops/solutions/8343913/3-approaches-a-bfs-b-dijkstra1d-min_stop-w2nt/

	Problem Statement:
	------------------
	There are n cities connected by some number of flights. 
    You are given an array flights where flights[i] = [fromi, toi, pricei] 
    indicates that there is a flight from city fromi to city toi with cost pricei.
    
    You are also given three integers src, dst, and k, return the cheapest price 
    from src to dst with at most k stops. If there is no such route, return -1.

 
	Example:
	--------
	Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
    Output: 700
    Explanation:
        The graph is shown above.
        The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
        Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops

	Approach 1 - DFS (Brute Force)
	---------------------
	DFS explores all paths from src to dst. Keep track of path that has minimum cost.
	During traversal, if any path exceeds k stops then return.


	Approach 2 - Dijkstra's Algorithm
	---------------------------------
	We use a Min-Heap (Priority Queue) sorted by cost (cost, node, stops). 
	Because it's a Min-Heap, paths are popped in strictly increasing order of cost. 
	The first path to pop a node is the absolute cheapest path to that node.

	Any subsequent path that pops the same node will inherently have an equal or higher cost. 
	Therefore, that subsequent path is only useful if it offers something better: 
		strictly fewer stops than any path seen before. 
	We can maintain a 1D min_stops array to track this.

	Algorithm Steps
	1. Initialize a 1D array min_stops of size n with INT_MAX.
	2. Push {0, src, 0} (cost, node, stops) into a min-heap.
	3. While popping (cost, u, stops):
		- If u == dst, return cost immediately (guaranteed cheapest valid path due to Min-Heap!).
		- If stops >= min_stops[u], prune it (continue). It is unnecessary to continue on this path.
		  This path is more expensive AND uses more/equal stops.
		- Otherwise, update min_stops[u] = stops.
		- If stops > k, do not expand its neighbors.
	4. Push all valid neighbor paths into the min-heap.

	Note: Why can't we push {node, cost, stops} into the heap?
	Answer: Because we want to process paths in increasing order of cost.
	However, if we push {node, cost, stops}, the heap will sort by node first,
	then by cost, then by stops. This doesn't guarantee processing paths in
	increasing order of cost.


	Time Complexity:
		vector<int> min_stops(n, INT_MAX);          // O(V)

		while (!pq.empty()) {                       // O(E·K) iterations total
			pq.pop();                               // O(log(E·K)) per pop
			// ...
			for (auto& [v, weight] : graph[u]) {    // Total across all valid processings: E·K
				// Each node u is validly processed at most K+1 times. 
				// Each processing iterates all outgoing edges of u.
				// Total iterations of this inner loop = Σ (K+1) × degree(u) for all u = (K+1) · E

				pq.push({...});                     // O(log(E·K)) per push
			}
		}

		Breaking it down:

		Initialization: O(V)
		Total pops: E·K × O(log(E·K)) = O(E·K · log(E·K))
		Total inner loop iterations (edge relaxations + pushes): E·K × O(log(E·K)) = O(E·K · log(E·K))
		Total = O(V + E·K · log(E·K))

	Approach 3 - BFS
	----------------
	Instead of using a Priority Queue to sort by cost, we use a standard std::queue to process the graph level by level.
		Level 0 contains the source node.
		Level 1 contains all nodes reachable with exactly 1 flight.
		Level 2 contains all nodes reachable with exactly 2 flights.

	Because we advance level-by-level, we can stop exactly after k+1 levels. 
	This guarantees we never process paths that violate the stop constraint. 
	Inside this level-by-level sweep, a simple 1D dist array tracks the minimum cost found up to the current level.
	
	Algorithm Steps
	1. Build an adjacency list: adj[u] = {v, weight}.
	2. Initialize a 1D array dist of size n with INT_MAX. Set dist[src] = 0.
	3. Push {src, 0} into a standard FIFO queue.
	4. Run a loop while the queue is not empty, keeping track of flights_taken. 
	   Stop when flights_taken > k.
	5. For each level, record the current size of the queue (sz). 
			Pop sz elements to process the current layer completely before moving to the next.
	6. When relaxing a neighbor, 
			if current_cost + weight < dist[neighbor], 
				update dist[neighbor] 
				and push it to the queue.

	Time Complexity:
	----------------
		1.  Initialize distance[V] = O(V)
		2.  This is level-order BFS where each level = one more flight taken. 
		    You process K+1 levels total (0 through K, inclusive).
			At each level:
				You pop all nodes in the current queue
				For each node, you iterate its adjacency list. Max E edges
			Total = O(E * (K + 1))
		3.  1 + 2 = O(V + (E * (K+1)))

	Space Complexity: 
		E — the adjacency list (graph storage). You store all E edges.
		N — the distance vector of size N.
		N·K — the queue size in the worst case.
			Level 0: push up to N-1 neighbors of src
			Level 1: each of those could push up to N-1 neighbors
			So across K+1 levels, up to N entries per level = O(N·K) queue entries
		Total = O(E + N + NK)
*/

/*
	- The goal is not to find a path with exactly K stops.
	- The goal is to find the cheapest path among all paths that have 0, 1, 2, ..., up to K stops.
	- Therefore, reaching the destination at any point before exceeding K stops is a valid success condition.
*/
class Solution1 {
private:
	void DFS(unordered_map<int, vector<pair<int, int>>> &graph, vector<bool> &visited, int currentCity, int dst, int k, int stopsTaken, int currentPathPrice, int &cheapestPrice) {
		
		visited[currentCity] = true;
		
		// Base Case 1: Reached destination
		// If we hit the destination, we don't care if we took 0 stops or K stops. 
		// We arrived successfully! We must record the price and stop exploring 
		// this specific branch.
		if (currentCity == dst) {
			cheapestPrice = min(cheapestPrice, currentPathPrice);
			visited[currentCity] = false;
			return;
		}
		
		// Base Case 2: Exceeded stop limit
		// If we haven't hit the destination yet, but we've used more than K stops, 
		// this path is dead.
		if (stopsTaken >= k + 1) {
			visited[currentCity] = false;
			return;
		}

		if (currentPathPrice >= cheapestPrice) {
			visited[currentCity] = false;
			return;
		}

		for (auto edge : graph[currentCity]) {
			int next_city = edge.first;
			int price = edge.second;

			if(!visited[next_city])
				DFS(graph, visited, next_city, dst, k, stopsTaken + 1, currentPathPrice + price, cheapestPrice);
		}

		visited[currentCity] = false;
	}
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
		int stopsTaken = 0;
		int cheapestPrice = INT_MAX;
		int currentPathPrice = 0;

		unordered_map<int, vector<pair<int, int>>> graph;
		for(auto flight : flights) {
			int source = flight[0];
			int destination = flight[1];
			int price = flight[2];

			graph[source].push_back({destination, price});
		}

		vector<bool> visited(n, false);
		DFS(graph, visited, src, dst, k, stopsTaken, currentPathPrice, cheapestPrice);
		return cheapestPrice == INT_MAX ? -1 : cheapestPrice;
	}
};

// Modified Dijkstra
class Solution2 {
private:
	int dijkstra(unordered_map<int, vector<pair<int, int>>>& graph, int src, int dst, int K, int n) {

		// dist array now tracks the minimum STOPS taken to reach a node.
		// Initialize with INT_MAX
		vector<int> min_stops(n, INT_MAX);

		// PQ stores: {cost, node, stops}
		priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
		pq.push({ 0, src, 0 });

		while (!pq.empty()) {
			auto [cost, u, stops] = pq.top();
			pq.pop();

			// If we reached the destination within limits, return cost
			// Rule 1: The Min-Heap guarantees the FIRST time we pull out 'dst', it's the cheapest.
			if (u == dst)
				return cost;

			// if we have previously reached this node
			// with FEWER (or equal) stops, this path is useless.
			if (stops >= min_stops[u])
				continue;

			// if we exceed stops then dont pursue further into this path.
			if (stops > K)
				continue;

			// Record that we found a way to reach 'u' with this many stops
			min_stops[u] = stops;

			// Relax neighbors
			for (auto& [v, weight] : graph[u]) {
				pq.push({ cost + weight, v, stops + 1 });
			}
		}
		return -1;
	}
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
		// Adjacency list: adj[u] = {{v, weight}, ...}
		unordered_map<int, vector<pair<int, int>>> graph;
		for (auto flight : flights) {
			int source = flight[0];
			int destination = flight[1];
			int price = flight[2];

			graph[source].push_back({ destination, price });
		}

		return dijkstra(graph, src, dst, K, n);
	}
};

// BFS
class Solution3 {
private:
	int BFS(unordered_map<int, vector<pair<int, int>>>& graph, int src, int dst, int K, int n) {

		// {node, cost}
		queue<pair<int, int>> q;
		q.push({ src, 0 });

		// Keeps track of minimum distance needed to reach a city
		vector<int> distance(n, INT_MAX);
		int flightsTaken = 0;

		// Level-by-Level BFS
		while (!q.empty() && flightsTaken <= K) {

			int size = q.size();

			// Process all nodes currently at the exact same flight-depth layer
			while (size--)
			{
				auto [u, cost] = q.front();
				q.pop();

				for (auto edge : graph[u]) {
					int v = edge.first;
					int price = edge.second;

					// If we find a cheaper way to reach neighbor 'v' at this layer
					if (cost + price < distance[v]) {
						distance[v] = cost + price;
						q.push({ v, cost + price });
					}
				}
			}
			flightsTaken++;
		}
		return distance[dst] == INT_MAX ? -1 : distance[dst];
	}

public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
		// Adjacency list: adj[u] = {{v, weight}, ...}
		unordered_map<int, vector<pair<int, int>>> graph;
		for (auto flight : flights) {
			int source = flight[0];
			int destination = flight[1];
			int price = flight[2];

			graph[source].push_back({ destination, price });
		}

		return BFS(graph, src, dst, K, n);
	}
};

int main() {
	

	return 0;
}