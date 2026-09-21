#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 23 - Merge k Sorted Lists

    You are given an array of k linked lists, each sorted in ascending
    order. Merge all the linked lists into one sorted linked list and
    return it.

    Examples:
    ---------

    Example 1:
        Input:  lists = [[1,4,5], [1,3,4], [2,6]]
        Output: [1,1,2,3,4,4,5,6]
        Explanation:
            Three sorted lists:
                1 → 4 → 5
                1 → 3 → 4
                2 → 6
            Merged: 1 → 1 → 2 → 3 → 4 → 4 → 5 → 6

    Example 2:
        Input:  lists = []
        Output: []

    Example 3:
        Input:  lists = [[]]
        Output: []

    Constraints:
    ------------
    - k == lists.length
    - 0 <= k <= 10^4
    - 0 <= lists[i].length <= 500
    - -10^4 <= lists[i][j] <= 10^4
    - lists[i] is sorted in ascending order.
    - Total nodes across all lists <= 10^4.

    Approach: Min-Heap (K-way Merge)
    ----------------------------------
    The key insight: at any point, the next smallest element must be
    at the HEAD of one of the k lists (since each list is sorted).
    So we only need to compare k heads, not all elements.

    A min-heap of size k gives us the smallest head in O(log k).

    Algorithm:
        1. Push the head node of each non-empty list into a min-heap.
        2. Pop the smallest node. Append it to the result list.
        3. If that node has a next, push next into the heap.
        4. Repeat until the heap is empty.

    Why push nodes (not values)?
    -----------------------------
    We push ListNode* pointers, not just values. This way, after
    popping, we can follow node->next to get the next element from
    that same list — without tracking which list each value came from.

    The custom comparator:
    -----------------------
        auto cmp = [](ListNode* a, ListNode* b) {
            return a->val > b->val;   // min-heap: smaller val = higher priority
        };

    This looks like "greater" (descending), but remember: heap
    comparators are inverted. return true = "a has LOWER priority."
    So a->val > b->val means "a is less important when a is bigger"
    = smaller values float to the top = min-heap.

    Dry Run (lists = [[1,4,5],[1,3,4],[2,6]]):
    --------------------------------------------

    Heap: [1(list0), 1(list1), 2(list2)]

    Pop 1(list0) → result: 1.  Push 4(list0).  Heap: [1, 2, 4]
    Pop 1(list1) → result: 1→1.  Push 3(list1).  Heap: [2, 3, 4]
    Pop 2(list2) → result: 1→1→2.  Push 6(list2).  Heap: [3, 4, 6]
    Pop 3(list1) → result: 1→1→2→3.  Push 4(list1).  Heap: [4, 4, 6]
    Pop 4(list0) → result: 1→1→2→3→4.  Push 5(list0).  Heap: [4, 5, 6]
    Pop 4(list1) → result: 1→1→2→3→4→4.  No next.  Heap: [5, 6]
    Pop 5(list0) → result: ...→5.  No next.  Heap: [6]
    Pop 6(list2) → result: ...→5→6.  No next.  Heap: []

    Result: 1→1→2→3→4→4→5→6 ✓

    Why not just merge two at a time?
    ----------------------------------
    You could merge list0 with list1, then result with list2, etc.
    That's O(kN) where N = total nodes. The heap approach is
    O(N log k) — much better when k is large.

    Complexity Analysis:
    --------------------
    Time:  O(N log k) — N total nodes, each push/pop is O(log k).
    Space: O(k) — heap holds at most k nodes at any time.

*/



struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* dummyHead = new ListNode(-1);
        ListNode* tail = dummyHead;

        // Custom comparator struct for min-heap (MSVC-friendly)
        struct Compare {
            bool operator()(ListNode* a, ListNode* b) {
                return a->val > b->val;     // min heap: smaller val = higher priority
            }
        };
        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;

        // 1. Add the all the list heads (non-empty) to the min heap
        for (auto list : lists) {
            if (list != nullptr)
                pq.push(list);
        }

        // 2. While the heap is not empty, add the nodes to the resultant
        //    list and advance the corresponding list
        while (!pq.empty()) {
            // 1. Pop
            auto listNode = pq.top();
            pq.pop();

            // 2. Add to result list
            tail->next = listNode;
            tail = tail->next;

            // 3. If there is a next node, push it to the heap
            if (listNode->next != nullptr)
                pq.push(listNode->next);
        }
        return dummyHead->next;
    }
};

int main() {
    Solution obj;

    // Helper to build a linked list from a vector
    auto buildList = [](vector<int> vals) -> ListNode* {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        for (int v : vals) {
            tail->next = new ListNode(v);
            tail = tail->next;
        }
        return dummy.next;
    };

    // Helper to print a linked list
    auto printList = [](ListNode* head) {
        while (head) {
            cout << head->val;
            if (head->next) cout << " -> ";
            head = head->next;
        }
        cout << endl;
    };

    // Example 1: [[1,4,5],[1,3,4],[2,6]]
    vector<ListNode*> lists1 = {
        buildList({1, 4, 5}),
        buildList({1, 3, 4}),
        buildList({2, 6})
    };
    cout << "Example 1: ";
    printList(obj.mergeKLists(lists1));
    // Expected: 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6

    // Example 2: empty
    vector<ListNode*> lists2 = {};
    cout << "Example 2: ";
    printList(obj.mergeKLists(lists2));
    // Expected: (empty)

    // Example 3: single list
    vector<ListNode*> lists3 = {buildList({5, 10, 15})};
    cout << "Example 3: ";
    printList(obj.mergeKLists(lists3));
    // Expected: 5 -> 10 -> 15

    return 0;
}