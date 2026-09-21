#include <iostream> 
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

// Time Complexity: O(V-1. E) => O(V.E)
class Solution {
public:
    vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {

        // INITIALIZE
        vector<int> distance(V, INT_MAX);
        distance[S] = 0;

        // RELAX EACH EDGE V-1 TIMES
        for(int i = 1; i<=V-1; i++){
            for(auto edge : edges){
                int u = edge[0];
                int v = edge[1];
                int weight = edge[2];
                
                // if u can be reached from source
                if(distance[u] != INT_MAX){
                    // RELAX the edge between u->v
                    if(distance[v] > distance[u] + weight)
                        distance[v] = distance[u] + weight;
                }
            }
        }

        // DETECT ANY -VE CYCLE
        for(auto edge : edges){
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            
            // if u can be reached from source
            if(distance[u] != INT_MAX){
                // RELAX the edge between u->v.
                // if able to still relax after V-1 iterations then it means
                // a -ve cycle exist
                if(distance[v] > distance[u] + weight){
                    return {-1};
                }
            }
        }

        return distance;
    }
};


int main(){
    Solution obj;
}