#include <bits/stdc++.h>
using namespace std;

/*
    Breadth First Search (BFS)  is a fundamental  graph traversal algorithm. 
    It begins with a node, then first traverses all its adjacent nodes. 
    Once all adjacent are visited, then their adjacent are traversed. 

    Ref: https://www.youtube.com/watch?v=4Y52Yw0m-lo
         https://www.youtube.com/watch?v=ls4cHglfc0g&list=PLSVu1-lON6LxCmXNMfZBq7bdMAvUf3Sc7&index=3
*/

class Solution{
public:
    vector<vector<int>> buildGraph(vector<vector<int>> &edges, int &V){
        vector<vector<int>> adjList(V, vector<int>());
        for(auto edge: edges){
            int u = edge[0];
            int v = edge[1];
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        return adjList;
    }

    vector<int> BFS(vector<vector<int>> &adjList, int V, int startVertex){
        vector<bool> visited(V, false);
        queue<int> Q;
        vector<int> traversal;

        //process the first node
        Q.push(startVertex);
        visited[startVertex] = true;
        traversal.push_back(startVertex);

        while(!Q.empty()){
            int u = Q.front();
            Q.pop();

            for(auto v: adjList[u]){
                if(visited[v] == false){
                    Q.push(v);
                    visited[v] = true;
                    traversal.push_back(v);
                }
            }
        }
        return traversal;
    }
};


int main(){
    Solution obj;
    vector<vector<int>> edges = {{1, 2}, {1, 0}, {2, 0}, {2, 3}, {2, 4}};
    int vertices = 5; // or edges.size()
    
    vector<vector<int>> adjList = obj.buildGraph(edges, vertices);
    vector<int> traversal = obj.BFS(adjList, vertices, 0);
    for(auto u: traversal)
        cout<<u<<" ";
    cout<<endl;
    return 0;

    return 0;
}