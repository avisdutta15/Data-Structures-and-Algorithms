# QuickSelect Algorithm

## What It Does

Finds the kth smallest (or kth largest) element in an unsorted array in O(n) average time, without fully sorting it.

Based on QuickSort's partition, but instead of sorting both sides, we only recurse into the side that contains our target index.

---

## The Algorithm

```
1. Pick a pivot (random for best performance).
2. Partition the array: elements < pivot go left, elements >= pivot go right.
3. The pivot lands at its correct sorted position (index p).
4. If p == k → found it, return.
   If k < p  → answer is in the left half, recurse there.
   If k > p  → answer is in the right half, recurse there.
5. Only ONE side is explored each time (unlike QuickSort which recurses into both).
```

```cpp
int quickSelect(vector<int>& nums, int low, int high, int k) {
    if (low == high)
        return nums[low];

    int pivotIndex = partition(nums, low, high);

    if (pivotIndex == k)
        return nums[pivotIndex];
    else if (k < pivotIndex)
        return quickSelect(nums, low, pivotIndex - 1, k);
    else
        return quickSelect(nums, pivotIndex + 1, high, k);
}
```

Note: "kth largest" = element at index `(n - k)` in ascending order.

---

## Partition — Step by Step

### The Idea
https://www.youtube.com/watch?v=UqVxcO4oNXA

Pick a pivot, rearrange the array so that:
- Everything LEFT of pivot is < pivot
- Everything RIGHT of pivot is >= pivot
- Pivot is at its correct sorted position

### Two Pointers

- `i` = boundary between "< pivot" and ">= pivot" regions
- `j` = scanner that walks left to right

### Array Layout at Each State

#### State 1: During Partition (loop running)

```
[  < pivot        |  >= pivot       |    unseen         | pivot ]
 low ... i-1        i ... j-1         j ... high-1         high

 nums[low..i-1]   → all < pivot     (processed, smaller)
 nums[i..j-1]     → all >= pivot    (processed, larger or equal)
 nums[j..high-1]  → not yet scanned
 nums[high]       → pivot itself
```

`nums[i]` is always the FIRST element in the ">= pivot" region.
When `j` finds a smaller element, swap `nums[j]` with `nums[i]` —
this pushes the small element into the left region.

#### State 2: After Loop Finishes (before final swap)

All elements have been scanned. The "unseen" region is gone.

```
[  < pivot   |     >= pivot       |   pivot ]
 low...i-1     i ... high-1          high
```

The pivot is still sitting at `nums[high]`, separate from the >= region.

#### State 3: After Final Swap (swap nums[i] with nums[high])

Bring the pivot to its sorted position at index `i`.
Now `i..high-1` had elements >= pivot, and the pivot joins them at position `i`.

```
[  < pivot   |  == pivot  |   >= pivot   ]
 low...i-1         i         i+1...high
```

The pivot is at index `i` — its correct sorted position.
Everything left is strictly smaller, everything right is >= pivot.

---

## Full Dry Run

```
nums = [7, 2, 5, 3, 6],  find 2nd smallest (k = 1, 0-indexed)
```

### Round 1: partition(nums, 0, 4)

Pivot = nums[4] = 6

```
Initial:  [7, 2, 5, 3, 6]    i=0, j=0
           ^              
           i,j

j=0: nums[0]=7, 7 >= 6 → skip
     [7, 2, 5, 3, 6]    i=0, j=1

j=1: nums[1]=2, 2 < 6 → swap(nums[0], nums[1])
     [2, 7, 5, 3, 6]    i=1, j=2

j=2: nums[2]=5, 5 < 6 → swap(nums[1], nums[2])
     [2, 5, 7, 3, 6]    i=2, j=3

j=3: nums[3]=3, 3 < 6 → swap(nums[2], nums[3])
     [2, 5, 3, 7, 6]    i=3, j=4
```

Loop done. Before final swap (State 2):

```
[2, 5, 3,  |  7,  |  6 ]
 < pivot    >= p    pivot
 0   1  2     3      4
              i     high
```

Final swap: swap(nums[3], nums[4]):

```
[2, 5, 3,  |  6,  |  7 ]
 < pivot    pivot   >= p
 0   1  2     3      4
              i=3
```

Pivot index = 3.

### Decision

k = 1, pivotIndex = 3.
k < pivotIndex → recurse left: quickSelect(nums, 0, 2, 1)

### Round 2: partition(nums, 0, 2)

Working on subarray [2, 5, 3]. Pivot = nums[2] = 3.

```
Initial:  [2, 5, 3]    i=0, j=0

j=0: nums[0]=2, 2 < 3 → swap(nums[0], nums[0]) (no-op)
     [2, 5, 3]    i=1, j=1

j=1: nums[1]=5, 5 >= 3 → skip
     [2, 5, 3]    i=1, j=2
```

Before final swap (State 2):

```
[2,  |  5,  |  3 ]
 <p    >=p    pivot
 0      1      2
        i    high
```

Final swap: swap(nums[1], nums[2]):

```
[2,  |  3,  |  5 ]
 <p   pivot   >=p
 0      1      2
        i=1
```

Pivot index = 1.

### Decision

k = 1, pivotIndex = 1.
k == pivotIndex → FOUND! Return nums[1] = 3.

### Final State of Array

```
[2, 3, 5, 6, 7]
        ^
     k=1 (2nd smallest = 3)
```

Note: the full array isn't sorted (it happened to be in this example), but element at index k is guaranteed to be correct.

---

## Time Complexity Derivation

### Average Case: O(n)

Each partition does O(n) work (scans all elements in the range).
After partition, we recurse into only ONE side.

On average (random pivot), the pivot splits the array roughly in half:

```
Round 1: scan n elements
Round 2: scan n/2 elements     (recurse into half)
Round 3: scan n/4 elements     (half of half)
Round 4: scan n/8 elements
...

Total work = n + n/2 + n/4 + n/8 + ...
           = n × (1 + 1/2 + 1/4 + 1/8 + ...)
           = n × 2
           = O(2n)
           = O(n)
```

This is a geometric series that converges to 2n. The key insight: each round does HALF the work of the previous round, and the series sums to a constant times n.

### Why QuickSort is O(n log n) but QuickSelect is O(n)

```
QuickSort:   recurses into BOTH sides → n work per level × log n levels = O(n log n)
QuickSelect: recurses into ONE side  → n + n/2 + n/4 + ... = O(n)
```

QuickSort does n work at every level (all elements are touched). QuickSelect's work shrinks by half each level.

```
QuickSort levels:      n    n    n    n    ... (log n levels)
                       ─────────────────────
                       Total: n × log n

QuickSelect levels:    n   n/2  n/4  n/8  ...
                       ─────────────────────
                       Total: n × (1 + 1/2 + 1/4 + ...) = 2n
```

### Worst Case: O(n²)

If the pivot is always the smallest or largest element (e.g., sorted array with fixed pivot):

```
Round 1: scan n elements, pivot at position 0 or n-1
Round 2: scan n-1 elements
Round 3: scan n-2 elements
...

Total = n + (n-1) + (n-2) + ... + 1 = n(n+1)/2 = O(n²)
```

Each partition eliminates only 1 element. This is why random pivot is critical — it makes this worst case astronomically unlikely.

### Summary

```
                    Average         Worst
QuickSelect         O(n)            O(n²)
  with random pivot: worst case is extremely rare

QuickSort           O(n log n)      O(n²)
Sorting + index     O(n log n)      O(n log n)
Min-Heap (size k)   O(n log k)      O(n log k)
```

---

## When to Use QuickSelect

- You need the kth smallest/largest element
- You need the top k elements (unordered)
- O(n) average is acceptable (worst case O(n²) is rare with random pivot)
- Modifying the input array in-place is okay

When NOT to use:
- You need sorted output (QuickSelect doesn't sort)
- You can't modify the input array
- Guaranteed O(n log k) is required (use a heap instead)
