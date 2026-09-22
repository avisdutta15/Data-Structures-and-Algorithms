#include <iostream>
#include <queue>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 362 - Design Hit Counter

    Design a hit counter that counts the number of hits received
    in the past 5 minutes (300 seconds).

    Implement the HitCounter class:
        - HitCounter(): initializes the counter.
        - void hit(int timestamp): record a hit at the given timestamp
          (in seconds). Multiple hits may occur at the same timestamp.
        - int getHits(int timestamp): return the number of hits in the
          past 5 minutes (from timestamp - 299 to timestamp inclusive).

    Timestamps are given in increasing order.

    Examples:
    ---------

    Example 1:
        HitCounter counter;
        counter.hit(1);
        counter.hit(2);
        counter.hit(3);
        counter.getHits(4);    // returns 3 (hits at 1, 2, 3)
        counter.hit(300);
        counter.getHits(300);  // returns 4 (hits at 1, 2, 3, 300)
        counter.getHits(301);  // returns 3 (hit at 1 expired, left: 2, 3, 300)

    Constraints:
    ------------
    - 1 <= timestamp <= 2 * 10^9
    - All calls to hit and getHits are in chronological order.
    - At most 300 calls to hit and getHits.

    Approach 1: Queue (Sliding Window)
    ------------------------------------
    Keep all hit timestamps in a queue. On getHits, pop all expired
    timestamps from the front. Queue size = valid hit count.

    hit:      O(1)
    getHits:  O(n) worst case, O(1) amortized
    Space:    O(n) — grows with number of hits

    Approach 2: Fixed Arrays (Circular Buffer)
    --------------------------------------------
    Use two arrays of size 300:
        times[i] = the timestamp that last wrote to bucket i
        hits[i]  = how many hits occurred at that timestamp

    Bucket index = timestamp % 300 (circular mapping).

    hit(timestamp):
        index = timestamp % 300
        If times[index] == timestamp → same second, just increment hits.
        Else → new timestamp for this bucket, reset hits to 1.

    getHits(timestamp):
        Scan all 300 buckets. If timestamp - times[i] < 300,
        that bucket is still within the 5-minute window → add hits[i].

    Why does this work?
    --------------------
    The % 300 maps timestamps to a fixed set of 300 buckets.
    Timestamps that differ by exactly 300 map to the SAME bucket.
    But by the time the second one arrives, the first one has expired
    (it's 300+ seconds old). So overwriting is safe — the old data
    was already expired.

    The times[] array detects stale data: if times[i] is from a
    different (older) timestamp, we know that bucket's data is
    expired and should be ignored in getHits / reset on hit.

    Example:
        hit(1):    times[1]=1, hits[1]=1
        hit(301):  301 % 300 = 1 → same bucket.
                   times[1]=1 != 301 → overwrite: times[1]=301, hits[1]=1
                   (hit at timestamp 1 was 300s ago — expired, safely replaced)

    hit:      O(1)
    getHits:  O(300) = O(1)
    Space:    O(300) = O(1) — fixed size, doesn't grow

    Comparison:
    -----------
        Approach      hit     getHits     Space
        Queue         O(1)    O(n) amort  O(n) — grows
        Fixed Arrays  O(1)    O(300)      O(300) — constant

    Fixed arrays are better when hit volume is high (millions of
    hits). The queue would store all of them; arrays stay at 300.

*/

class HitCounter1 {
private:
    queue<int> hits;  // timestamps of all hits within the window

public:
    HitCounter1() {}

    // Record a hit at the given timestamp
    void hit(int timestamp) {
        hits.push(timestamp);
    }

    // Return number of hits in the past 300 seconds
    int getHits(int timestamp) {
        // Remove expired hits (older than 300 seconds ago)
        while (!hits.empty() && hits.front() <= timestamp - 300) {
            hits.pop();
        }
        // Remaining hits are all within the window
        return hits.size();
    }
};


class HitCounter2 {
private:
    vector<int> times;
    vector<int> hits;
public:
    HitCounter2() {
        times = vector<int>(300, 0);
        hits = vector<int>(300, 0);
    }

    // Record a hit at the given timestamp
    void hit(int timestamp) {
        int index = timestamp % 300;

        // same timestamp seen before
        if(times[index] == timestamp){
            hits[index]++;
        }
        else{
            times[index] = timestamp;
            hits[index] = 1;
        }
    }

    // Return number of hits in the past 300 seconds
    int getHits(int timestamp) {
        int total_hits = 0;
        for(int i=0; i<times.size(); i++){
            int timestampAtI = times[i];
            if(timestamp - timestampAtI < 300)
                total_hits = total_hits + hits[i];
        }
        return total_hits;
    }
};

int main() {
    // === Approach 1: Queue ===
    cout << "=== Queue ===" << endl;
    HitCounter1 c1;
    c1.hit(1);
    c1.hit(2);
    c1.hit(3);
    cout << c1.getHits(4) << endl;      // 3
    c1.hit(300);
    cout << c1.getHits(300) << endl;    // 4
    cout << c1.getHits(301) << endl;    // 3

    // === Approach 2: Fixed Arrays ===
    cout << "=== Fixed Arrays ===" << endl;
    HitCounter2 c2;
    c2.hit(1);
    c2.hit(2);
    c2.hit(3);
    cout << c2.getHits(4) << endl;      // 3
    c2.hit(300);
    cout << c2.getHits(300) << endl;    // 4
    cout << c2.getHits(301) << endl;    // 3

    // Multiple hits at same timestamp
    cout << "=== Multiple hits ===" << endl;
    HitCounter2 c3;
    c3.hit(1);
    c3.hit(1);
    c3.hit(1);
    cout << c3.getHits(1) << endl;      // 3
    cout << c3.getHits(301) << endl;    // 0

    return 0;
}
