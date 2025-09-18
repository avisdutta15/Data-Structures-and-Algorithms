#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    Given the number of vertices V and a list of directed edges, determine whether 
    the graph contains a cycle or not.



*/

class Solution{
    bool DFS(vector<vector<int>> &graph, int u, vector<bool> &visited){
        visited[u] = true;
        for(auto v: graph[u]){
            if(visited[v] == false && DFS(graph, v, visited)==true)
                return true;
            if(visited[v] == true)
                return true;
        }
        return false;
    }
public:
    vector<vector<int>> buildGraph(vector<vector<int>> &edges, int V){
        vector<vector<int>> graph(V, vector<int>());

        for(auto edge : edges){
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
        }

        return graph;
    }

    bool isCyclic(vector<vector<int>> &graph, int V){
        vector<bool> visited(V, false);
        return DFS(graph, 0, visited);
    }
};


int main(){
    Solution obj;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}, {2, 3}};
    vector<vector<int>> graph = obj.buildGraph(edges, edges.size());

    obj.isCyclic(graph, edges.size());
    return 0;
}