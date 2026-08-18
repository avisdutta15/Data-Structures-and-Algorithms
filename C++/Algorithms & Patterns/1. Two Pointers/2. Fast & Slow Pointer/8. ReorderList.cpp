#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

// ════════════════════════════════════════════════════════════════════════════════
// TWO POINTER PATTERN 2: FAST & SLOW POINTERS
// ════════════════════════════════════════════════════════════════════════════════
//
// Core Idea:
// - Two pointers move at different speeds (slow moves 1 step, fast moves 2 steps).
// - When fast reaches the end, slow is at the middle.
// - If there's a cycle, fast and slow will eventually meet.
//
// Common uses:
// - Find middle of linked list (slow at middle when fast hits end)
// - Detect cycles (if fast meets slow → cycle exists)
// - Find cycle start (Floyd's algorithm)
// - Problems that combine: find middle + do something with both halves
//
// ════════════════════════════════════════════════════════════════════════════════

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// ──────────────────────────────────────────────────────────────────────────────
// Problem: Reorder List (LeetCode 143)
// ──────────────────────────────────────────────────────────────────────────────

/*
    Problem Statement:
    ------------------
    Given the head of a singly linked list:
        L0 → L1 → … → Ln-1 → Ln

    Reorder it to:
        L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …

    You may NOT modify the values in the list's nodes. Only nodes themselves
    may be changed.

    Examples:
    ---------
    Input:  [1, 2, 3, 4]
    Output: [1, 4, 2, 3]

    Input:  [1, 2, 3, 4, 5]
    Output: [1, 5, 2, 4, 3]

    Constraints:
    ------------
    - The number of nodes is in range [1, 5 * 10^4]
    - 1 <= Node.val <= 1000

    Approach:
    ---------
    This problem combines THREE techniques:
    1. Find the middle (fast & slow pointer)
    2. Reverse the second half
    3. Merge the two halves alternately

    Step-by-step:
    1. Use slow/fast to find the middle node.
       - slow moves 1 step, fast moves 2 steps.
       - When fast reaches end, slow is at middle.

    2. Split the list into two halves at the middle.
       - First half: head → ... → mid
       - Second half: mid.next → ... → end

    3. Reverse the second half.
       - Standard iterative linked list reversal.

    4. Merge the two halves by interleaving.
       - Take one from first, one from second, alternating.

    Worked Example:
    ---------------
    Input: 1 → 2 → 3 → 4 → 5

    Step 1: Find middle
      slow=1, fast=1
      slow=2, fast=3
      slow=3, fast=5 (fast.next == null, stop)
      Middle = 3

    Step 2: Split
      First half:  1 → 2 → 3
      Second half: 4 → 5

    Step 3: Reverse second half
      Second half reversed: 5 → 4

    Step 4: Merge alternately
      Take 1, then 5: 1 → 5
      Take 2, then 4: 1 → 5 → 2 → 4
      Take 3 (remaining): 1 → 5 → 2 → 4 → 3

    Result: 1 → 5 → 2 → 4 → 3 ✓

    Another Example:
    Input: 1 → 2 → 3 → 4

    Step 1: Find middle
      slow=1, fast=1
      slow=2, fast=3 (fast.next.next == null, stop)
      Middle = 2

    Step 2: Split
      First half:  1 → 2
      Second half: 3 → 4

    Step 3: Reverse second half
      Second half reversed: 4 → 3

    Step 4: Merge alternately
      Take 1, then 4: 1 → 4
      Take 2, then 3: 1 → 4 → 2 → 3

    Result: 1 → 4 → 2 → 3 ✓

    Time Complexity: O(N) — each step is O(N)
    Space Complexity: O(1) — in-place, no extra data structures
*/

class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;

        // ─── Step 1: Find the middle using slow/fast ───
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        // slow is now at the middle (end of first half)

        // ─── Step 2: Split into two halves ───
        ListNode* secondHalf = slow->next;
        slow->next = nullptr;  // cut the list

        // ─── Step 3: Reverse the second half ───
        ListNode* prev = nullptr;
        ListNode* curr = secondHalf;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        secondHalf = prev;  // prev is the new head of reversed second half

        // ─── Step 4: Merge two halves alternately ───
        ListNode* first = head;
        ListNode* second = secondHalf;
        while (second) {
            ListNode* firstNext = first->next;
            ListNode* secondNext = second->next;

            first->next = second;
            second->next = firstNext;

            first = firstNext;
            second = secondNext;
        }
    }
};

// ── Helper functions for testing ──
ListNode* buildList(vector<int>& vals) {
    if (vals.empty()) return nullptr;
    ListNode* head = new ListNode(vals[0]);
    ListNode* curr = head;
    for (int i = 1; i < vals.size(); i++) {
        curr->next = new ListNode(vals[i]);
        curr = curr->next;
    }
    return head;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main()
{
    Solution obj;

    vector<int> vals1 = {1, 2, 3, 4, 5};
    ListNode* head1 = buildList(vals1);
    cout << "Before: "; printList(head1);
    obj.reorderList(head1);
    cout << "After:  "; printList(head1);  // 1 -> 5 -> 2 -> 4 -> 3

    cout << endl;

    vector<int> vals2 = {1, 2, 3, 4};
    ListNode* head2 = buildList(vals2);
    cout << "Before: "; printList(head2);
    obj.reorderList(head2);
    cout << "After:  "; printList(head2);  // 1 -> 4 -> 2 -> 3

    return 0;
}
