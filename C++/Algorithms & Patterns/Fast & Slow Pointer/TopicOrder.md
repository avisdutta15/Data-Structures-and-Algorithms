# Floyd's Tortoise and Hare (Fast and Slow Pointers)

The **Fast and Slow Pointer** technique, formally known as Floyd's Cycle Detection Algorithm, is an elegant pointer algorithm that uses two pointers moving at different speeds to detect cycles in a sequence (like a Linked List or an Array where values act as pointers).

Typically, the "slow" pointer (the tortoise) moves $1$ step at a time, while the "fast" pointer (the hare) moves $2$ steps at a time. If there is a cycle, the fast pointer will eventually "lap" the slow pointer, and they will point to the same node.



---

## 1. The Mathematical Proof: Finding the Cycle Start
Detecting the cycle is intuitive, but the second phase—resetting one pointer to the start and moving both at the same speed to find the exact duplicate/cycle start—feels like magic. Here is the mathematical proof of why it works perfectly every time.

### Defining our Variables:
Let's define the distances in our system:
* $L$ = Distance from the start of the list to the start of the cycle.
* $C$ = The total length (perimeter) of the cycle.
* $K$ = Distance from the start of the cycle to the point where the two pointers first meet.
* $n$ = The number of complete cycles the fast pointer makes before they meet.

### The Equations:
When the two pointers collide in Phase 1, we can define the total distance each pointer has traveled.

1.  **Distance traveled by the slow pointer:**
    $$D_{slow} = L + K$$
    *(It traveled to the start of the cycle, and then $K$ steps into the cycle).*

2.  **Distance traveled by the fast pointer:**
    $$D_{fast} = L + n \cdot C + K$$
    *(It traveled to the cycle, spun around the cycle $n$ times, and met the slow pointer at $K$).*

### The Core Relationship:
Because the fast pointer moves exactly **twice as fast** as the slow pointer, the distance it travels is exactly twice the distance of the slow pointer:
$$D_{fast} = 2 \cdot D_{slow}$$

Now, substitute our earlier equations into this relationship:
$$L + n \cdot C + K = 2 \cdot (L + K)$$

Expand the right side:
$$L + n \cdot C + K = 2L + 2K$$

Rearrange the equation to solve for $L$ (the distance from the start to the cycle entrance):
$$L = n \cdot C - K$$

To make this easier to visualize, we can rewrite $n \cdot C - K$ by factoring out one full cycle ($C$):
$$L = (n - 1) \cdot C + (C - K)$$

### What does this final equation mean?
The term $(n - 1) \cdot C$ just means spinning around the cycle a few times, which brings you back to exactly where you started. We can ignore it for distance calculations. 

This leaves us with the beautiful conclusion:
$$L = C - K$$

* $L$ is the distance from the very beginning of the array to the cycle entrance.
* $C - K$ is the distance from the **meeting point** to the cycle entrance.

**The Conclusion:** The distance from the start of the array to the cycle entrance is exactly equal to the distance from the meeting point to the cycle entrance. Therefore, if you put one pointer at the start and leave one at the meeting point, and move them both at $1$ step per loop, they will collide exactly at the entrance of the cycle!

---

## 2. Deriving the Time Complexity

The time complexity of this algorithm is strictly **$O(N)$**, where $N$ is the total number of nodes (or elements in the array). Here is the breakdown:

### Phase 1: Detecting the Cycle
* If there is no cycle, the fast pointer reaches the end of the list in $N/2$ steps.
* If there is a cycle, the slow pointer will enter the cycle after $L$ steps. 
* Once the slow pointer enters the cycle, the fast pointer is already inside. The maximum distance between them inside the cycle is $C$. Since the fast pointer closes the gap by $1$ step per iteration, it will catch the slow pointer in at most $C$ steps.
* Total maximum steps for Phase 1: $L + C \le N$.

### Phase 2: Finding the Start
* Both pointers move $1$ step at a time.
* They will meet at the cycle entrance after exactly $L$ steps.
* Since $L < N$, this takes strictly less than $N$ iterations.

### Final Complexity:
* **Time Complexity:** $O(N) + O(N) = O(N)$. The algorithm scales linearly with the size of the input.
* **Space Complexity:** $O(1)$. We only ever allocate memory for two integer variables (`slow` and `fast`), regardless of how massive the input array or linked list is.



| Id | Problem | Comment / Urls |
|----|---------|----------------|
| 1  | Middle of the Linked List I | For odd-length lists: The fast pointer becomes nullptr exactly when slow reaches the middle. </br> For even-length lists: The fast pointer reaches the last node when slow reaches the first middle node. |
| 2  | Middle of the Linked List II | |
| 3| Linked List Cycle | | 
| 4| Linked List Cycle II
| 5| Palindrome Linked List| | 
| 6| Reorder List| | 
| 7| Maximum Twin Sum of a Linked List  |[TODO] | 
| 8| Split a Circular Linked List       |[TODO] | 
| 9| Happy Number| | 
| 10| Find the Duplicate Number          | | 
| 11| Circular Array Loop                |[TODO - need to check] | 
| 12| Is subsequence| | 
