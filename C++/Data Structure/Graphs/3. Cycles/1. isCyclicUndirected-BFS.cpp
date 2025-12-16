#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

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
public:
	bool cycleExists(Graph& g) {
		//Q<node, parentFromWhichWeCanToNode>
		queue<pair<int, int>> Q;
		vector<bool> visited(g.V, false);

		Q.push({0, -1});
		visited[0] = true;
		while (!Q.empty()) {
			int u = Q.front().first;
			int parentOfU = Q.front().second;
			Q.pop();

			for (int v : g.adj[u]) {
				//if this neighbour is not visited and is not the parent of u then visit it
				if (visited[v] == false && v != parentOfU) {
					visited[v] = true;
					Q.push({ v, u });
				}
				//if this neighbour is visited and is not the parent of u i.e. this node is visited by 
				//someone else. so already a path exists from source. If we take that path, it will
				//end up in a cycle. So return true.
				else if (visited[v] == true && v != parentOfU)
					return true;
			}
		}
		return false;
	}
};

int main() {
	Graph g(7); // A=0, B=1, C=2, D=3, E=4, F=5, G=6

	g.addEdge(0, 1); // A-B
	g.addEdge(0, 2); // A-C
	g.addEdge(1, 4); // B-E
	g.addEdge(2, 5); // C-F
	g.addEdge(5, 6); // F-G
	g.addEdge(4, 6); // E-G

	Solution obj;
	obj.cycleExists(g) == true ? cout << "Cycle Exists" << endl : cout << "Cycle does not exist" << endl;

	return 0;
}