#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

/*
	Reference:
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
	enum COLOUR { WHITE, RED, BLUE };

	//returns true if the graph is bipartite else returns false
	bool DFS(Graph& g, int u, vector<COLOUR> &visited, COLOUR color) {
		
		//vist u with color
		visited[u] = color;

		color = (color == RED) ? BLUE : RED;
		for (int v : g.adj[u]) {
			//if the child is not visited then do DFS
			if (visited[v] == WHITE) {
				if (DFS(g, v, visited, color) == false)
					return false;
			}
			//if the child is visited and have same color then its not bipartite
			else if (visited[v] == visited[u])
				return false;
			//if the child is visited and doesnot have the same color then continue
			else if (visited[v] != visited[u])
				continue;
		}
		return true;
	}

public:
	bool isBipartite(Graph& g) {
		//initialization
		vector<COLOUR> visited(g.V, WHITE);
		return DFS(g, 0, visited, RED);
	}
};

int main() {
	Graph g1(6); // A=0, B=1, C=2, D=3, E=4, F=5

	g1.addEdge(0, 1); // A-B
	g1.addEdge(1, 2); // B-C
	g1.addEdge(1, 3); // B-D
	g1.addEdge(3, 4); // D-E
	g1.addEdge(2, 4); // C-E
	g1.addEdge(4, 5); // E-F


	Solution obj;
	obj.isBipartite(g1) == true ? cout << "Bipartite" << endl : cout << "Not Bipartite" << endl;

	Graph g2(5); // A=0, B=1, C=2, D=3, E=4, F=5
	g2.addEdge(0, 1);
	g2.addEdge(1, 2);
	g2.addEdge(2, 3);
	g2.addEdge(3, 4);
	g2.addEdge(4, 0);
	obj.isBipartite(g2) == true ? cout << "Bipartite" << endl : cout << "Not Bipartite" << endl;

	return 0;
}