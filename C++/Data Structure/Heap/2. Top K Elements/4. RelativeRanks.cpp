#include <iostream>
#include <queue>
#include <deque>
#include <string>
#include <vector>
#include <climits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 506 - Relative Ranks

    You are given an integer array `scores` of size n, where scores[i]
    is the score of the ith athlete in a competition. All scores are
    unique.

    The athletes are placed based on their scores:
        - 1st place → "Gold Medal"
        - 2nd place → "Silver Medal"
        - 3rd place → "Bronze Medal"
        - 4th place onward → placement number as a string ("4", "5", ...)

    Return an array `result` of size n where result[i] is the rank
    of the ith athlete.

    Examples:
    ---------

    Example 1:
        Input:  scores = [5, 4, 3, 2, 1]
        Output: ["Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"]

    Example 2:
        Input:  scores = [10, 3, 8, 9, 4]
        Output: ["Gold Medal", "5", "Bronze Medal", "Silver Medal", "4"]
        Explanation:
            Sorted by score: 10(idx 0), 9(idx 3), 8(idx 2), 4(idx 4), 3(idx 1)
            Rank 1 → idx 0: "Gold Medal"
            Rank 2 → idx 3: "Silver Medal"
            Rank 3 → idx 2: "Bronze Medal"
            Rank 4 → idx 4: "4"
            Rank 5 → idx 1: "5"

    Constraints:
    ------------
    - n == scores.length
    - 1 <= n <= 10^4
    - 0 <= scores[i] <= 10^6
    - All scores are unique.

    Approach: Max Heap
    -------------------
    Push all (score, original index) pairs into a max-heap.
    Pop them one by one — highest score first. Each pop gives
    the next rank. Use the stored index to place the rank string
    at the correct position in the result array.

    Dry Run (scores = [10, 3, 8, 9, 4]):
    --------------------------------------
    Heap after all pushes: [(10,0), (9,3), (8,2), (4,4), (3,1)]

    Rank 1: pop (10, 0) → result[0] = "Gold Medal"
    Rank 2: pop (9,  3) → result[3] = "Silver Medal"
    Rank 3: pop (8,  2) → result[2] = "Bronze Medal"
    Rank 4: pop (4,  4) → result[4] = "4"
    Rank 5: pop (3,  1) → result[1] = "5"

    Result: ["Gold Medal", "5", "Bronze Medal", "Silver Medal", "4"] ✓

    Complexity Analysis:
    --------------------
    Time:  O(n log n) — n pushes and n pops, each O(log n).
    Space: O(n) — heap + result array.

*/

class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& scores) {
        int N = scores.size();

        vector<string> result(N);
        priority_queue<pair<int,int>> pq;   //score, index in original array
        for (int i = 0; i < N; i++) {
            pq.push({ scores[i], i});
        }

        // pop the max heap. each popped item will get a rank
        // based on the popped item's index in the original array,
        // we place the rank in that index in the result array.
        int rank = 1;
        for (rank = 1; rank <= N; rank++) {
            auto[score, idx] = pq.top(); pq.pop();
            if(rank == 1) result[idx] = "Gold Medal";
            else if (rank == 2) result[idx] = "Silver Medal";
            else if (rank == 3) result[idx] = "Bronze Medal";
            else result[idx] = to_string(rank);
        }

        return result;
    }
};


int main() {
    Solution obj;
    vector<int> scores = {10, 3, 8, 9, 4};
    vector<string> result = obj.findRelativeRanks(scores);

    for (const auto& rank : result) {
        cout << rank << " ";
    }
    cout << endl;
    // Expected: Gold Medal 5 Bronze Medal Silver Medal 4

    return 0;
}
