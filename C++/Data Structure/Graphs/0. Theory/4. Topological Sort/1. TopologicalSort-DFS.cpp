#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

/*
	Reference: https://www.youtube.com/watch?v=xqLY-ZLJig8&list=PLSVu1-lON6LyvT8iceopuqnmSmPiSA6wX&index=3
*/

class Graph {
private:
public:
	int V;
	unordered_map<int, vector<int>> adj;
	Graph(int vertices) : V(vertices), adj(vertices) {}

	void addEdge(int u, int v) {
		adj[u].push_back({ v });
	}
};

class Solution {
private:
	enum COLOUR { WHITE, GREY, BLACK };
	//returns true if the graph has cycles
	//if no cycle the stack stores the topoOrder
	bool DFS(Graph& g, int u, vector<COLOUR>& visited, stack<int>& stack) {
		visited[u] = GREY;

		for (int v : g.adj[u]) {
			if (visited[v] == WHITE) {
				if (DFS(g, v, visited, stack) == true)
					return true;
			}
			else if (visited[v] == GREY)
				return true;
		}

		visited[u] = BLACK;
		stack.push(u);
		return false;
	}

public:
	vector<int> topologicalSort(Graph& g) {
		vector<COLOUR> visited(g.V, WHITE);
		stack<int> stack;
		vector<int> topoOrder;

		//if the graph is cyclic then there would be no topoOrder
		if (DFS(g, 0, visited, stack) == true)
			return topoOrder;

		while (stack.empty() == false) {
			topoOrder.push_back(stack.top());
			stack.pop();
		}
		return topoOrder;
	}

};

int main() {
	Graph g1(5); // A=0, B=1, C=2, D=3, E=4

	g1.addEdge(0, 1); // A-B
	g1.addEdge(0, 2); // A-C
	g1.addEdge(1, 3); // B-D
	g1.addEdge(2, 3); // C-D
	g1.addEdge(3, 4); // C-D

	Solution obj;
	auto topoOrder = obj.topologicalSort(g1);
	for (int i : topoOrder) {
		cout << i << " ";
	}
	cout << endl;

	return 0;
}