class Solution {
private:
	void DFS(int u, vector<vector<int>>& isConnected, vector<bool>& visited) {
		visited[u] = true;
		for (int v = 0; v < isConnected.size(); v++) {
			// isConnected[u][v] == 1 means there's an edge between u and v
			if (!visited[v] && isConnected[u][v] == 1) {
				DFS(v, isConnected, visited);
			}
		}
	}
public:
	int findCircleNum(vector<vector<int>>& isConnected) {
		int n = isConnected.size();
		vector<bool> visited(n, false);
		int provinces = 0;

		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				DFS(i, isConnected, visited);
				provinces++;
			}
		}

		return provinces;
	}
};
