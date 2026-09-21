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
    Think of the 2D grid laid out row by row into a single 1D array:

    Grid (3 rows × 4 cols):

    col:  0   1   2   3
    row 0: [A] [B] [C] [D]
    row 1: [E] [F] [G] [H]
    row 2: [I] [J] [K] [L]

    Flattened 1D array:
    index:  0   1   2   3   4   5   6   7   8   9  10  11
        [A] [B] [C] [D] [E] [F] [G] [H] [I] [J] [K] [L]
        |--- row 0 ---|  |--- row 1 ---|  |--- row 2 ---|
    Each row occupies exactly cols slots. So row i starts at index i * cols. 
    Then column j is just an offset within that row. Hence i * cols + j.

    Approach:
    ---------
    Start with islands = 0.
    Scan every cell. When you hit a '1', assume it's a new island → islands++.

    for all cells
        if we hit a '1'
            Check all 4 neighbors. If a neighbor is also '1' 
                if they're NOT already connected in the DSU, merge them and do islands-- 
                (two separate islands just became one).

    At the end, islands holds the count.    

*/
class DSU {
private:
    vector<int> parent;
public:
    DSU(int n){
        parent.resize(n);
        for(int i=0; i<n; i++){
            parent[i] = i;
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
        parent[parentX] = parentY;
    }

    bool isConnected(int x, int y){
        return find(x) == find(y);
    }
};

// island is identified by (row * COLS) + col
// we assume all lands are individual islands.
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int dirs[4][2] = {{0,-1},{0,1},{1,0},{-1,0}};
        DSU dsu(rows * cols);
        
        int islands = 0;
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                if(grid[i][j] == '1') 
                    islands++;
            }
        }

        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){

                if(grid[i][j] == '1'){

                    // for all the adjacent lands, lets try to merge it into 1 island.
                    for(auto dir: dirs){
                        int x = i + dir[0];
                        int y = j + dir[1];
                        if(x>=0 && x<rows && y>=0 && y<cols && grid[x][y] == '1'){
                            // if not already merged
                            if(dsu.isConnected((i * cols + j), (x * cols + y))==false){
                                dsu.Union((i * cols + j), (x * cols + y));   // two separate islands merged into one
                                islands--;
                            }
                        }
                    }
                }
            }
        }
        return islands;
    }
};

int main() {
	return 0;
}