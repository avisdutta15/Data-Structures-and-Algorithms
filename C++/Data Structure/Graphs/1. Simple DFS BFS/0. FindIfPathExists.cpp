#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <queue>
#include <unordered_map>
#include <stack>
using namespace std;

/*
	Problem Statement:
	-----------------
	There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1 (inclusive). 
    The edges in the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes 
    a bi-directional edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, 
    and no vertex has an edge to itself.
    You want to determine if there is a valid path that exists from vertex source to vertex destination.
    Given edges and the integers n, source, and destination, return true if there is a valid path from source 
    to destination, or false otherwise.

 	Example:
	-------
	Example 1:
    Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
    Output: true
    Explanation: There are two paths from vertex 0 to vertex 2:
    - 0 → 1 → 2
    - 0 → 2
    
    Example 2:
    Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
    Output: false
    Explanation: There is no path from vertex 0 to vertex 5.


	Approach:
	---------
	1. DFS / Iterative DFS / BFS
*/

class Solution {
private:
    bool DFS(unordered_map<int, vector<int>>& adjList, int u, int destination, vector<int> visited) {
        if (u == destination)
            return true;

        visited[u] = true;
        for (auto v : adjList[u]) {
            if (visited[v] == false && DFS(adjList, v, destination, visited) == true)
                return true;
        }
        return false;
    }
    bool BFS(unordered_map<int, vector<int>>& adjList, int u, int destination, vector<int> visited) {
        queue<int> Q;
        Q.push(u);
        visited[u] = true;

        while (!Q.empty()) {
            u = Q.front();
            Q.pop();

            if (u == destination)
                return true;
            for (auto v : adjList[u]) {
                if (visited[v] == false) {
                    visited[v] = true;
                    Q.push(v);
                }
            }
        }

        return false;
    }
    bool DFSIterative(unordered_map<int, vector<int>>& adjList, int u, int destination, vector<int> visited) {
        stack<int> stack;
        stack.push(u);
        visited[u] = true;
        while (!stack.empty()) {
            u = stack.top();
            stack.pop();

            if (u == destination)
                return true;

            visited[u] = true;
            for (auto v : adjList[u]) {
                if (visited[v] == false)
                    stack.push(v);
            }
        }

        return false;
    }
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        unordered_map<int, vector<int>> adjList;
        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        vector<int> visited(n, false);
        return DFSIterative(adjList, source, destination, visited);
    }
};
int main()
{
	Solution obj;

    vector<vector<int>> grid = {{0, 1}, {1, 2}, {2, 0}};
    cout << obj.validPath(3, grid, 0, 2) << endl;

    grid = { {0,1} ,{0,2},{3,5},{5,4},{4,3} };
    cout << obj.validPath(6, grid, 0, 5) << endl;


	return 0;
}

