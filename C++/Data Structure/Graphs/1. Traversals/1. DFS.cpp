#include <bits/stdc++.h>
using namespace std;

class Solution{
private:
    void DFSUtil(vector<vector<int>> &adjList, int u, vector<int> &traversal, vector<bool> &visited){
        visited[u] = true;
        traversal.push_back(u);
        for(auto v: adjList[u]){
            if(!visited[v])
                DFSUtil(adjList, v, traversal, visited);
        }
    }

public:    
    // Build an undirected graph
    vector<vector<int>> buildGraph(vector<vector<int>> &edges, int V){
        vector<vector<int>> adjList(V, vector<int>());
        for(auto edge: edges){
            int u = edge[0];
            int v = edge[1];
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        return adjList;
    }
    
    // DFS Traversal on the given graph
    vector<int> DFS(vector<vector<int>> &adjList, int V){
        vector<int> traversal; 
        vector<bool> visited(V, false);
        DFSUtil(adjList, 0, traversal, visited);
        return traversal;
    }
};


int main(){
    Solution obj;
    vector<vector<int>> edges = {{1, 2}, {1, 0}, {2, 0}, {2, 3}, {2, 4}};
    int vertices = 5; // or edges.size()
    
    vector<vector<int>> adjList = obj.buildGraph(edges, vertices);
    vector<int> traversal = obj.DFS(adjList, vertices);
    for(auto u: traversal)
        cout<<u<<" ";
    cout<<endl;
    return 0;
}