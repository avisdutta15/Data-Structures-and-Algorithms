#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Graph {
private:
	int V;
	unordered_map<int, vector<int>> adj;
	void getPath(unordered_map<int, int>& parent, vector<int>& path, int u, int v) {
		int i = v;
		while (i != u) {
			path.push_back(i);
			i = parent[i];
		}
		path.push_back(0);
	}
public:
	Graph(int vertices) : V(vertices), adj(vertices) {}

	void addEdge(int u, int v) {
		adj[u].push_back({ v });
		adj[v].push_back({ u });
	}

	//returns a path between u and v
	vector<int> findPath(int u, int v) {
		queue<int> Q;
		vector<bool> visited(V, 0);
		unordered_map<int, int> parent;
		vector<int> path;

		//process the first node
		Q.push(u);
		visited[u] = true;

		//for all other nodes in the Q
		while (!Q.empty()) {
			int vertex = Q.front();
			Q.pop();

			//if found the destination node then build the path[] and return
			if (vertex == v) {
				getPath(parent, path, u, v);
				return path;
			}

			//for all the neighbours visit them and push them to Q
			for (int child : adj[vertex]) {
				if (visited[child] == false) {
					visited[child] = true;
					parent[child] = vertex;
					Q.push(child);
				}
			}
		}

		//path not found, return empty path[]
		return vector<int>();
	}
};

int main() {
	Graph g(9); // A=0, B=1, C=2, D=3, E=4, F=5, G=6, H=7, I=8

	g.addEdge(0, 1); // A-B
	g.addEdge(0, 2); // A-C
	g.addEdge(1, 3); // B-D  
	g.addEdge(2, 3); // C-D
	g.addEdge(1, 4); // B-E
	g.addEdge(3, 4); // D-E
	g.addEdge(2, 5); // C-F
	g.addEdge(5, 6); // F-G
	g.addEdge(4, 6); // E-G

	auto path = g.findPath(0, 6);
	if (path.size() == 0)
		cout << "No Path" << endl;
	else {
		for (int u : path)
			cout << u << " ";
	}

	//Add a disconnected edge
	g.addEdge(7, 8);

	cout << endl;
	path = g.findPath(0, 8);
	if (path.size() == 0)
		cout << "No Path" << endl;
	else {
		for (int u : path)
			cout << u << " ";
	}

	return 0;
}