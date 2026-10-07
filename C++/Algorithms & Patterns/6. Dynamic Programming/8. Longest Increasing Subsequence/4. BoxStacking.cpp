#include <bits/stdc++.h>
using namespace std;

/*
    https://www.youtube.com/watch?v=kLucR6-Q0GA&t=338s&pp=ygUMQm94IFN0YWNraW5n
    
    Problem: Box Stacking
    ─────────────────────

    Given a set of N boxes, each with dimensions (length, width, height),
    find the maximum height stack possible. A box can be placed on top of
    another only if BOTH its length and width are strictly less than
    the box below it. You can use multiple rotations of the same box
    (each rotation counts as a different box).

    Example:
    --------
    Input:  boxes = [{1, 2, 4}, {3, 2, 5}]
    Output: 11

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: Reduction to LIS
    ════════════════════════════════════════════════════════════════════════

    Step 1: Generate all 3 rotations of each box.
            For a box (l, w, h), the rotations are:
              - base (l, w), height h
              - base (l, h), height w
              - base (h, w), height l
            For each rotation, ensure l >= w (normalize so length >= width).

    Step 2: Sort rotations by base area in decreasing order.
            After sorting, if box i can go on top of box j where j < i,
            then j has a larger base area — this ordering lets us apply LIS.

    Step 3: Apply LIS-like DP.
            MSH[i] = Maximum Stack Height with box i on top

            MSH[i] = max(MSH[j] + height[i]) for all j < i where
                     length[j] > length[i] AND width[j] > width[i]

            If no such j exists, MSH[i] = height[i]

            This is exactly the "Maximum Sum Increasing Subsequence" pattern,
            but instead of sum, we maximize height, and instead of A[j] < A[i],
            we check both dimensions.

    Answer: max(MSH[0..3N-1])

    Time: O((3N)^2) = O(N^2)

    ════════════════════════════════════════════════════════════════════════
    COMPARISON WITH STANDARD LIS
    ════════════════════════════════════════════════════════════════════════

    Standard LIS:
        dp[i] = max(dp[j] + 1)  where A[j] < A[i]
        → counting elements

    Box Stacking:
        MSH[i] = max(MSH[j] + height[i])  where l[j] > l[i] AND w[j] > w[i]
        → summing heights (like Maximum Sum Increasing Subsequence)
        → 2D constraint instead of 1D

    ════════════════════════════════════════════════════════════════════════
*/

struct Box{
    int l, w, h;
};

// Sort by base area in decreasing order
// Returns true if a should come before b (i.e., a has larger base area)
bool compareByBaseArea(Box &a, Box &b){
    int baseAreaA = a.l * a.w;
    int baseAreaB = b.l * b.w;

    if(baseAreaA > baseAreaB)
        return true;   // a has larger area → a comes first
    return false;      // b has larger or equal area → b comes first (or stays)
}

class Solution{
    private:
        // ══════════════════════════════════════════════════════════════════
        // Approach 1: Recursive — O(2^(3N))
        // ══════════════════════════════════════════════════════════════════

        // i = current box index, prevIndex = index of last stacked box (-1 if none)
        // Boxes are sorted by decreasing base area
        int boxStackRecursive(vector<Box> &boxes, int i, int prevIndex, int N){
            // Base case: no more boxes to consider
            if(i == N)
                return 0;

             // Include box i: only if it fits on top of prevIndex
            // (both length and width must be strictly less)
            int include = 0;
            if(prevIndex == -1 || (boxes[i].l < boxes[prevIndex].l && boxes[i].w < boxes[prevIndex].w))
                include = boxes[i].h + boxStackRecursive(boxes, i+1, i, N);

            // Exclude box i: don't stack it
            int exclude = boxStackRecursive(boxes, i+1, prevIndex, N);          

            return max(include, exclude);
        }

        // ══════════════════════════════════════════════════════════════════
        // Approach 2: Top-Down Memoized — O(N^2) where N = 3 * numBoxes
        // ══════════════════════════════════════════════════════════════════

        // memo[i][prevIndex+1] = max height from index i with given prev
        int boxStackTopDown(vector<Box> &boxes, int i, int prevIndex, int N, vector<vector<int>> &memo){
            if(i == N)
                return 0;

            if(memo[i][prevIndex + 1] != -1)
                return memo[i][prevIndex + 1];

            // Exclude
            int exclude = boxStackTopDown(boxes, i+1, prevIndex, N, memo);

            // Include if it fits
            int include = 0;
            if(prevIndex == -1 || (boxes[i].l < boxes[prevIndex].l && boxes[i].w < boxes[prevIndex].w))
                include = boxes[i].h + boxStackTopDown(boxes, i+1, i, N, memo);

            memo[i][prevIndex + 1] = max(include, exclude);
            return memo[i][prevIndex + 1];
        }

        // ══════════════════════════════════════════════════════════════════
        // Approach 3: Bottom-Up — O(N^2) where N = 3 * numBoxes
        // ══════════════════════════════════════════════════════════════════

        // MSH[i] = Maximum Stack Height with box i on top
        // Analogous to LIS bottom-up, but:
        //   - condition: l[j] > l[i] AND w[j] > w[i]  (instead of A[j] < A[i])
        //   - value: MSH[j] + height[i]  (instead of dp[j] + 1)
        int boxStackBottomUp(vector<Box> &boxes, int N){
            // Initialize MSH[i] = height of box i (each box alone is a valid stack)
            vector<int> MSH(N);
            for(int i = 0; i < N; i++)
                MSH[i] = boxes[i].h;

            // parent[i] tracks which box is below i (for printing the stack)
            vector<int> parent(N);
            for(int i = 0; i < N; i++)
                parent[i] = i;

            for(int i = 1; i < N; i++){
                for(int j = 0; j < i; j++){
                    // Can box i go on top of box j?
                    // (box j is below, so j must be strictly larger in both dims)
                    if(boxes[i].l < boxes[j].l && boxes[i].w < boxes[j].w){
                        // If stacking i on j gives a taller stack than current best for i
                        if(MSH[j] + boxes[i].h > MSH[i]){
                            MSH[i] = MSH[j] + boxes[i].h;
                            parent[i] = j;  // box j is below box i
                        }
                    }
                }
            }

            // Find the maximum height and its index
            int maxHeight = 0, maxIndex = 0;
            for(int i = 0; i < N; i++){
                if(MSH[i] > maxHeight){
                    maxHeight = MSH[i];
                    maxIndex = i;
                }
            }

            // Print the stack (from top to bottom)
            cout << "Boxes in stack (top to bottom):" << endl;
            int idx = maxIndex;
            while(parent[idx] != idx){
                cout << "  (" << boxes[idx].l << " x " << boxes[idx].w << ", h=" << boxes[idx].h << ")" << endl;
                idx = parent[idx];
            }
            cout << "  (" << boxes[idx].l << " x " << boxes[idx].w << ", h=" << boxes[idx].h << ")" << endl;

            return maxHeight;
        }

    public:
        int findMaxStackHeight(vector<Box> &boxes){
            if(boxes.empty()) return 0;

            // Step 1: Generate all rotations (3 per box)
            vector<Box> rotations;
            for(int i=0; i<boxes.size(); i++){
                Box box = boxes[i];

                int l = box.l;
                int w = box.w;
                int h = box.h;

                Box rotation1;
                rotation1.l = max(l, w);
                rotation1.w = min(l, w);
                rotation1.h = h;

                Box rotation2;
                rotation2.l = max(w, h);
                rotation2.w = min(w, h);
                rotation2.h = l;

                Box rotation3;
                rotation3.l = max(h, l);
                rotation3.w = min(h, l);
                rotation3.h = w;

                rotations.push_back(rotation1);
                rotations.push_back(rotation2);
                rotations.push_back(rotation3);
            }

            // Step 2: Sort by decreasing base area
            sort(rotations.begin(), rotations.end(), compareByBaseArea);

            // Step 3: Apply LIS-like DP
            int N = rotations.size();  // 3 * numBoxes
            int i = 0;
            int prevIndex = -1;
            // Approach 1: Recursive
            // return boxStackRecursive(rotations, i, prevIndex, N);

            // Approach 2: Top-Down
            // vector<vector<int>> memo(N, vector<int>(N+1, -1));
            // return boxStackTopDown(rotations, i, prevIndex, N, memo);

            // Approach 3: Bottom-Up
            return boxStackBottomUp(rotations, N);
        }
};

int main(){
    Solution obj;

    vector<Box> boxes1 = {{1, 2, 4}, {3, 2, 5}};
    cout << "Maximum height: " << obj.findMaxStackHeight(boxes1) << endl;
    // 11

    cout << endl;

    vector<Box> boxes2 = {{4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32}};
    cout << "Maximum height: " << obj.findMaxStackHeight(boxes2) << endl;
    // 60

    return 0;
}
