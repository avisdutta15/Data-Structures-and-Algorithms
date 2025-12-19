#include <bits/stdc++.h>
using namespace std;

/*
    In Depth First Search (or DFS) for a graph, we traverse all adjacent vertices one by one. 
    When we traverse an adjacent vertex, we completely finish the traversal of all vertices 
    reachable through that adjacent vertex.

    initialize visited[V] = false

    DFS(u, visited)
        visited[u] = true
        for all neighbours v of u:
            if v is not visited
                DFS(v)

    Time Complexity:
    We initialize the visited array before calling the DFS. O(V)
    The DFS(u) is called exactly once for all vertices. 
    Within DFS, for each node, we explore all of its neighbors (adjacent vertices).
    Each edge is examined once when traversing from one node to its neighbor. 
    In an undirected graph, each edge is checked twice (once for each endpoint), 
    but this constant factor does not affect the overall complexity.
    Therefore, the total time in processing the edges is proportional to the number of edges, E, i.e., O(E).

    Total TC: O(V) + O(E)

    Ref: https://www.youtube.com/watch?v=bP3MWJHeohc
         https://www.youtube.com/watch?v=qH-mHxkoK0Q&list=PLSVu1-lON6LxCmXNMfZBq7bdMAvUf3Sc7&index=4
*/

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
    vector<int> DFS(vector<vector<int>> &adjList, int V, int startIndex){
        vector<int> traversal; 
        vector<bool> visited(V, false);
        DFSUtil(adjList, startIndex, traversal, visited);
        return traversal;
    }
};


int main(){
    Solution obj;
    vector<vector<int>> edges = {{1, 2}, {1, 0}, {2, 0}, {2, 3}, {2, 4}};
    int vertices = 5; // or edges.size()
    
    vector<vector<int>> adjList = obj.buildGraph(edges, vertices);
    vector<int> traversal = obj.DFS(adjList, vertices, 0);
    for(auto u: traversal)
        cout<<u<<" ";
    cout<<endl;
    return 0;
}