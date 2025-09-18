#include <bits/stdc++.h>
using namespace std;

/*
    https://www.youtube.com/watch?v=M8H4F3fw2WE
*/

class Solution{
        bool DFS(vector<vector<int>> &graph, int u, int parent, vector<bool> &visited){
            visited[u] = true;
            for(auto v: graph[u]){
                // if traversing the neighbour returns that the graph is cyclic then return true.
                if(visited[v] == false){
                    if (DFS(graph, v, u, visited) == true)
                        return true;
                }
                // if the neighbour is visited and.
                else if(visited[v] == true){
                    //if the neighbour is parent of u then continue
                    if(v == parent)
                        continue;
                    //if the neighbour is not parent then its a cycle. Return true.
                    else
                        return true;
                }
            }
            return false;
        }
    public:
        vector<vector<int>> buildGraph(vector<vector<int>> &edges, int &V){
            vector<vector<int>> adjList(V, vector<int>());
            for(auto edge: edges){
                int u = edge[0], v = edge[1];
                adjList[u].push_back(v);
                adjList[v].push_back(u);
            }
            return adjList;
        }

        bool isCyclic(vector<vector<int>> &graph, int &V){
            vector<bool> visited(V, false);
            int u = 0;
            int parent = -1;
            return DFS(graph, u, parent, visited);
        }        
};

/*
    1----0----3
    |   /     |
    |  /      |
     2        4
     
*/

int main(){
    Solution obj;
    vector<vector<int>> edges = {{1, 0}, {1, 2}, {2, 0}, {0, 3}, {3, 4}};
    int vertices = 5;
    vector<vector<int>> graph = obj.buildGraph(edges, vertices);

    obj.isCyclic(graph, vertices) == true ? cout<<"Cyclic"<<endl : cout<<"Not Cyclic"<<endl;

    edges = {{1, 0}, {1, 2}, {0, 3}, {3, 4}};
    vertices = 5;
    graph = obj.buildGraph(edges, vertices);

    obj.isCyclic(graph, vertices) == true ? cout<<"Cyclic"<<endl : cout<<"Not Cyclic"<<endl;

    return 0;
}