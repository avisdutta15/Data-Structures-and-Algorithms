#include <algorithm>
#include <iostream>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

/*
    Variant	                                Time (amortized)
    No optimization	                        O(n) worst case — tree becomes a straight line
    Union by rank/size only	                O(log n) — tree height stays logarithmic
    Path compression only	                O(log n) amortized — flattens over time
    Both (rank/size + path compression)	    O(α(n)) ≈ O(1) — α is inverse Ackermann, ≤ 4 for any practical n
*/

class DSU {
private:
    vector<int> parent;
    vector<int> size;
public:
    DSU(int n){
        parent.resize(n);
        size.resize(n);

        for(int i=0; i<n; i++){
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int x){
        if(parent[x] == x)
            return x;
        return parent[x] = find(parent[x]); //path compression
    }

    void Union(int x, int y){
        int parentX = find(x);
        int parentY = find(y);

        if(parentX == parentY)
            return;
        
        if(size[parentX] > size[parentY]){
            parent[parentY] = parentX;          // jiska size bada hai wo baap banega
            size[parentX] += size[parentY];     // jo baap bana, uska size badhega
        }
        else if(size[parentY] >= size[parentX]){
            parent[parentX] = parentY;          // jiska size bada hai wo baap banega
            size[parentY] += size[parentX];     // jo baap bana, uska size badhega
        }
    }

    void UnionWithOutRankin(int x, int y){
        int parentX = find(x);
        int parentY = find(y);
        if(parentX == parentY)
            return;
        parent[parentX] = parentY;
    }

    bool isConnected(int x, int y){
        return find(x) == find(y);
    }

};

int main() {
    int n = 7;
    DSU dsu(n);
    
    dsu.Union(1, 2);
    dsu.Union(3, 4);
    dsu.Union(1, 4);    // merges {1,2} and {3,4}

    cout << dsu.isConnected(2, 3) << endl;  // 1 (same set)
    cout << dsu.isConnected(2, 5) << endl;  // 0 (different sets)

	return 0;
}