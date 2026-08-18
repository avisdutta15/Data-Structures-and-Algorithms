#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement:
    ------------------
    You are given an array people where people[i] is the weight of the ith person,
    and an infinite number of boats where each boat can carry at most `limit` weight.
    Each boat carries at most TWO people at the same time, provided the sum of their
    weights is at most limit.

    Return the MINIMUM number of boats to carry every person.

    Examples:
    ---------
    Input:  people = [1, 2], limit = 3
    Output: 1
    Explanation: 1 boat (1, 2)

    Input:  people = [3, 2, 2, 1], limit = 3
    Output: 3
    Explanation: 3 boats: (1,2), (2), (3)

    Input:  people = [3, 5, 3, 4], limit = 5
    Output: 4
    Explanation: 4 boats: (3), (5), (3), (4) — no pair fits within limit=5... 
                 Actually: (1 boat each) since smallest pair 3+3=6 > 5.
                 Wait — only (3) alone fits? No, let me recalculate.
                 Sorted: [3, 3, 4, 5]. 3+3=6>5, so each goes alone = 4 boats.

    Constraints:
    ------------
    - 1 <= people.length <= 5 * 10^4
    - 1 <= people[i] <= limit <= 3 * 10^4

    Approach:
    ---------
    Greedy + Two Pointers (Converging):

    Key Insight:
    - Each boat holds at most 2 people.
    - To minimize boats, we want to pair people when possible.
    - Greedy: pair the LIGHTEST with the HEAVIEST. If they fit together, great
      (one boat, two people). If they don't fit, the heavy person must go alone
      (they can't pair with anyone lighter either, since this is the lightest).

    Steps:
    1. Sort the array.
    2. left = 0 (lightest), right = n-1 (heaviest).
    3. If people[left] + people[right] <= limit:
       → They share a boat. left++, right--, boats++.
    4. Else:
       → Heavy person goes alone. right--, boats++.
    5. Repeat until left > right.

    Why pair lightest with heaviest?
    - The heaviest person MUST go on a boat (alone or paired).
    - If even the lightest person can't pair with them, nobody can → heavy goes alone.
    - If the lightest CAN pair, it's optimal to use that pairing (saves a boat).
    - Pairing heavy with anyone heavier would fail; pairing heavy with someone
      in the middle might "waste" that middle person who could have paired elsewhere.
      But actually, since the lightest is the best candidate to fit, using them is optimal.

    Worked Example:
    ---------------
    people = [3, 2, 2, 1], limit = 3
    After sort: [1, 2, 2, 3]

    left=0, right=3: 1+3 = 4 > 3 → heavy goes alone. right--. boats=1.
    left=0, right=2: 1+2 = 3 <= 3 → pair them! left++, right--. boats=2.
    left=1, right=1: single person left. boats=3.
    left=2 > right=1, done.

    Total boats = 3 ✓

    Another Example:
    people = [1, 2, 3, 4, 5], limit = 5
    After sort: [1, 2, 3, 4, 5]

    left=0, right=4: 1+5 = 6 > 5 → 5 alone. right--. boats=1.
    left=0, right=3: 1+4 = 5 <= 5 → pair! left++, right--. boats=2.
    left=1, right=2: 2+3 = 5 <= 5 → pair! left++, right--. boats=3.
    left=2 > right=1, done.

    Total boats = 3 ✓ (instead of 5 boats if everyone went alone)

    Time Complexity: O(NlogN) for sort + O(N) for two pointers = O(NlogN)
    Space Complexity: O(1)
*/

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());

        int left = 0, right = people.size() - 1;
        int boats = 0;

        while (left <= right) {
            // Can lightest and heaviest share a boat?
            if (people[left] + people[right] <= limit) {
                left++;   // lightest person boards
                right--;  // heaviest person boards
            } else {
                right--;  // heaviest goes alone
            }
            boats++;  // one boat used either way
        }

        return boats;
    }
};

int main()
{
    Solution obj;

    vector<int> people1 = {3, 2, 2, 1};
    cout << "Boats needed: " << obj.numRescueBoats(people1, 3) << endl;  // 3

    vector<int> people2 = {1, 2, 3, 4, 5};
    cout << "Boats needed: " << obj.numRescueBoats(people2, 5) << endl;  // 3

    return 0;
}
