#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 973 - K Closest Points to Origin

    Given an array of `points` where points[i] = [xi, yi] represents
    a point on the X-Y plane, and an integer `k`, return the k closest
    points to the origin (0, 0).

    Distance is Euclidean: sqrt(x² + y²). Since we only compare
    distances, we can skip the sqrt and use x² + y² directly.

    The answer may be returned in any order.

    Examples:
    ---------

    Example 1:
        Input:  points = [[1,3],[-2,2]], k = 1
        Output: [[-2,2]]
        Explanation:
            Distance of (1,3)  = 1² + 3² = 10
            Distance of (-2,2) = 4 + 4    = 8
            (-2,2) is closer. Return it.

    Example 2:
        Input:  points = [[3,3],[5,-1],[-2,4]], k = 2
        Output: [[3,3],[-2,4]]  (any order)
        Explanation:
            Distances: (3,3)=18, (5,-1)=26, (-2,4)=20
            Two closest: (3,3) and (-2,4).

    Constraints:
    ------------
    - 1 <= k <= points.length <= 10^4
    - -10^4 <= xi, yi <= 10^4

    Approaches:
    -----------

    Approach 1 — Sort: O(n log n)
        Compute all distances, sort by distance, take first k.

    Approach 2 — Max Heap of size k: O(n log k)
        Maintain a max-heap of size k. The heap top is the farthest
        of the k closest seen so far. For each new point, if its
        distance is smaller than the top, replace the top.
        Why max-heap? We want to quickly evict the FARTHEST point
        in our k candidates — max-heap gives us that in O(1) peek.

    Approach 3 — QuickSelect: O(n) average
        Partition the points by distance. After partition, the pivot
        is at its sorted position. If pivotIndex == k, the left side
        has exactly the k closest. Otherwise, recurse into the
        correct side. No need to fully sort — just partition until
        the boundary is right.

    Complexity Comparison:
    ----------------------
        Sort:           O(n log n)
        Max Heap (k):   O(n log k)
        QuickSelect:    O(n) average, O(n²) worst

*/

// Approach 1: Sort
class Solution1 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {

        vector<pair<int, int>> distanceAndIndexMap;        // [distance between 0 and point, index of point]

        for (int i = 0; i < points.size(); i++) {
            auto point = points[i];

            int x = point[0];
            int y = point[1];

            int distance = (x * x) + (y * y);
            distanceAndIndexMap.push_back({ distance, i });
        }

        sort(distanceAndIndexMap.begin(), distanceAndIndexMap.end()); // sort each item based on distance

        vector<vector<int>> result;
        for (auto& [distanace, index] : distanceAndIndexMap) {  // iterate all sorted distance and points
            result.push_back(points[index]);
            if (result.size() == k)             // collect only k points
                break;
        }

        return result;
    }
};

// Approach 2: Max Heap of size k
class Solution2 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        
        // k closest points based on distance from origin (0,0)
        // means min distances. => max heap of size k

        priority_queue<pair<int, int>> maxHeap;     // [distance between 0 and point, index of point]

        for (int i = 0; i<points.size(); i++) {
            auto point = points[i];
            int x = point[0];
            int y = point[1];

            int distance = (x * x) + (y * y);

            if (maxHeap.size() < k) {
                maxHeap.push({ distance, i });
            }
            else if (distance < maxHeap.top().first) {
                maxHeap.pop();
                maxHeap.push({ distance, i });
            }
        }

        vector<vector<int>> result;
        while (!maxHeap.empty()) {
            auto [distance, index] = maxHeap.top();
            maxHeap.pop();
            result.push_back(points[index]);
        }
        return result;
    }
};

// Approach 3: Quick Select
// You don't need the k closest points sorted — you just need ANY k points that are the closest. 
// QuickSelect can partition the array so that the k smallest distances are in the left portion, 
// without fully sorting.
// The idea: partition the points array by distance. 
// After partition, the pivot is at its sorted position. 
//      If pivotIndex == k, everything to the left is closer (the k closest). 
//      If not, recurse into the correct side.

class Solution3 {
private:
    int distance(vector<int>& point) {
        int x = point[0];
        int y = point[1];
        return (x * x)+ (y * y);
    }

    int partition(vector<vector<int>>& points, int low, int high) {
        int pivot_index = high;

        int i = low;
        int j = low;

        while (j < high) {
            if (distance(points[j]) < distance(points[pivot_index])) {
                swap(points[i], points[j]);
                i++;
            }
            j++;
        }

        swap(points[i], points[high]);
        return i;
    }

    // points = [ ... k closest ... | pivot | ... farther points ... ]
    //              0 .... k - 1        k
    void quickSelect(vector<vector<int>>& points, int low, int high, int k){
        if (low >= high)
            return;

        int pivot_index = partition(points, low, high);

        if (pivot_index == k)
            return; // done — left side has exactly k closest points

        if (pivot_index < k) {
            quickSelect(points, pivot_index + 1, high, k);
        }
        else if (pivot_index > k) {
            quickSelect(points, low, pivot_index - 1, k);
        }
    }

public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        quickSelect(points, 0, points.size()-1, k);
        
        vector<vector<int>> result;

        // After quickSelect, points[0..k-1] are the k closest (unordered)
        for(int i=0; i<k; i++){
            result.push_back(points[i]);
        }
        return result;
    }
};

int main() {
    // Test with Example 1: points = [[1,3],[-2,2]], k = 1
    vector<vector<int>> points = {{1, 3}, {-2, 2}};
    int k = 1;

    // Test all 3 approaches
    Solution1 s1;
    auto result1 = s1.kClosest(points, k);
    cout << "Sort: ";
    for (auto& p : result1) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;

    Solution2 s2;
    points = {{1, 3}, {-2, 2}};  // reset since quickselect modifies in place
    auto result2 = s2.kClosest(points, k);
    cout << "Heap: ";
    for (auto& p : result2) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;

    Solution3 s3;
    points = {{1, 3}, {-2, 2}};
    auto result3 = s3.kClosest(points, k);
    cout << "QuickSelect: ";
    for (auto& p : result3) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;

    // Expected: [-2,2] for all three

    return 0;
}
