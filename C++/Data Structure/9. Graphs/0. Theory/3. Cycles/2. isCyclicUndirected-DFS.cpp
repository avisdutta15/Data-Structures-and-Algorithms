#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

/*
	Reference: https://www.youtube.com/watch?v=M8H4F3fw2WE
               https://www.geeksforgeeks.org/dsa/detect-cycle-undirected-graph/
*/

class Graph {
private:
public:
	int V;
	unordered_map<int, vector<int>> adj;
	Graph(int vertices) : V(vertices), adj(vertices) {}

	void addEdge(int u, int v) {
		adj[u].push_back({ v });
		adj[v].push_back({ u });
	}
};

class Solution {
private:
	bool DFS(Graph& g, int u, int parent, vector<bool>& visited) {
		visited[u] = true;
		for (int v : g.adj[u]) {
            // if traversing the unvisited neighbour returns that the graph is cyclic then return true.
			if (visited[v] == false) {
				if (DFS(g, v, u, visited) == true)
					return true;
			}
            // if the neighbour is visited and.
			else if (visited[v] == true){
                //if the neighbour is parent of u then continue
                if(v == parent)
                    continue;
                //if the neighbour is not parent then its a cycle. Return true.
                else if(v != parent)
			    	return true;
            }
		}
        return false;
	}
public:
	bool cycleExists(Graph& g) {
		vector<bool> visited(g.V, false);
		return DFS(g, 0, -1, visited);
	}
};

int main() {
	Graph g1(7); // A=0, B=1, C=2, D=3, E=4, F=5, G=6

	g1.addEdge(0, 1); // A-B
	g1.addEdge(0, 2); // A-C
	g1.addEdge(1, 4); // B-E
	g1.addEdge(2, 5); // C-F
	g1.addEdge(5, 6); // F-G
	g1.addEdge(4, 6); // E-G

	Solution obj;
	obj.cycleExists(g1) == true ? cout << "Cycle Exists" << endl : cout << "Cycle does not exist" << endl;

	Graph g2(6); // A=0, B=1, C=2, D=3, E=4, F=5, G=6

	g2.addEdge(0, 1); // A-B
	g2.addEdge(0, 2); // A-C
	g2.addEdge(1, 4); // B-E
	g2.addEdge(2, 5); // C-F

	obj.cycleExists(g2) == true ? cout << "Cycle Exists" << endl : cout << "Cycle does not exist" << endl;

	return 0;
}