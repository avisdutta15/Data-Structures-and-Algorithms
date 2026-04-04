# Backtracking Patterns

## 1. Include/Exclude (The Binary Decision Pattern)

Problems where the core logic is a sequence of mutually exclusive choices: "Take it or Leave it", "Add (+) or Subtract (-)", or "Option A or Option B".

```cpp
solve(nums, 0, current_subset, result);

void solve(vector<int>& nums, int index, vector<int>& current_subset, vector<vector<int>>& result) {
                       
    // Base case: We have made a yes/no decision for every element in the array
    if (index == nums.size()) {
        result.push_back(current_subset);
        return;
    }

    // ==========================================
    // DECISION 1: INCLUDE the current element
    // ==========================================
    current_subset.push_back(nums[index]);
    solve(nums, index + 1, current_subset, result);
    current_subset.pop_back(); // Backtrack to undo the choice

    // ==========================================
    // DECISION 2: EXCLUDE the current element
    // ==========================================
    
    // -> IF HANDLING DUPLICATES (Subsets II style):
    // Since we chose to exclude nums[index], we must also exclude 
    // all identical adjacent elements to prevent duplicate branches.

    int next_index = index + 1;
    while (next_index < nums.size() && nums[next_index] == nums[index]) {
        next_index++;
    }
    solve(nums, next_index, current_subset, result);
    
    // -> IF NO DUPLICATES exist (Classic Subsets):
    // You can delete the while loop above and simply use:
    // solve(nums, index + 1, current_subset, result);
}
```

### Recursion Tree — `nums = [1, 2, 3]`

Each node makes a binary decision: include or exclude the current element.

```
                                solve(idx=0, [])
                               /                \
                     Include 1                    Exclude 1
                    solve(idx=1, [1])            solve(idx=1, [])
                   /              \              /              \
            Include 2         Exclude 2    Include 2         Exclude 2
        solve(idx=2,[1,2])  solve(idx=2,[1])  solve(idx=2,[2])  solve(idx=2,[])
          /        \          /        \        /        \        /        \
      Inc 3    Exc 3     Inc 3    Exc 3    Inc 3    Exc 3    Inc 3    Exc 3
        |        |         |        |        |        |        |        |
    [1,2,3]   [1,2]     [1,3]     [1]     [2,3]     [2]      [3]      []
```

Result: `[1,2,3], [1,2], [1,3], [1], [2,3], [2], [3], []`

### Classic Subsets (Take it or Leave it)
- 78\. Subsets (Print all/ One/ Count with sum = k)
- 1863\. Sum of All Subset XOR Totals
- 2044\. Count Number of Maximum Bitwise-OR Subsets
- 2597\. The Number of Beautiful Subsets

### Subsequence Building (Order matters, but strictly Left-to-Right)
- 491\. Non-decreasing Subsequences
- 1239\. Maximum Length of a Concatenated String with Unique Characters

### Strict A/B Selection (Two mutually exclusive actions)
- 22\. Generate Parentheses (Choice: Add `(` or Add `)`)
- 3211\. Generate Binary Strings Without Adjacent Zeros (Choice: Add `0` or Add `1`)
- 1980\. Find Unique Binary String (Choice: Add `0` or Add `1`)
- 401\. Binary Watch (Choice: Turn LED on or off)

### TODO
- 494\. Target Sum (Choice: Assign `+` or Assign `-`)

### String & Character Mutation
- 784\. Letter Case Permutation (Choice: Uppercase or Lowercase)
- 320\. Generalized Abbreviation (Choice: Keep char or change to number)
- 89\. Gray Code (Bit manipulation binary decisions)
- 17\. Letter Combinations of a Phone Number (Mapping single digits to specific character sets)

### Target Sum (Unbounded)
- 39\. Combination Sum (Choice: Take number and stay to reuse, or leave and move on)

---

## 2. Combinations & Fixed-Size Selection (The For-Loop "Team" Pattern)

Problems where you are building a combination by iterating through remaining choices. This is strongly preferred over Include/Exclude when dealing with array duplicates or when picking exactly `k` elements.

```cpp
//  Optional: Sort if you need to handle duplicates
sort(nums.begin(), nums.end()); 
    
solve(nums, 0, current_combo, 0, target, result);
return result;

void solve(vector<int>& nums, int start_index, vector<int>& current_combo,
           int current_sum, int target, vector<vector<int>>& result) {

    // Base case: Found a valid combination
    if (current_sum == target) { // Replace with your problem's valid condition
        result.push_back(current_combo);
        return;
    }
    
    for (int i = start_index; i < nums.size(); ++i) {
        // Optional: Skip duplicates
        if (i > start_index && nums[i] == nums[i - 1]) continue;
        
        // Optional: Prune the tree
        if (current_sum + nums[i] > target) break; 
        
        // Make a choice
        current_combo.push_back(nums[i]);
        
        // Recurse (i + 1 to move forward, or just 'i' if reuse is allowed)
        backtrack(nums, i + 1, current_combo, current_sum + nums[i], target, result);
        
        // Undo choice
        current_combo.pop_back();
    }
};
```

### Recursion Tree — `nums = [1, 2, 3, 4]`, pick `k = 2`

The for-loop at each level picks the next element from `start_index` onward. Base case: `current_combo.size() == k`.

```
                          solve(start=0, [])
                       /        |         \
                  pick 1      pick 2      pick 3
            solve(start=1,[1]) solve(start=2,[2]) solve(start=3,[3])
              /    |    \         /      \              |
          pick 2 pick 3 pick 4  pick 3  pick 4       pick 4
          [1,2]✓ [1,3]✓ [1,4]✓  [2,3]✓  [2,4]✓      [3,4]✓
```

Result: `[1,2], [1,3], [1,4], [2,3], [2,4], [3,4]`

Note: picking `4` at the top level is skipped because there aren't enough remaining elements to form a pair.

### Classic Combinations (Pick exactly k elements)
- 77\. Combinations
- 216\. Combination Sum III
- 254\. Factor Combinations
- 2178\. Maximum Split of Positive Even Integers

### Handling Duplicates (Sorting + Skip Logic)
- 90\. Subsets II
- 40\. Combination Sum II

### String & Character Combinations
- 1079\. Letter Tile Possibilities
- 1087\. Brace Expansion
- 1096\. Brace Expansion II
- 1286\. Iterator for Combination

---

## 3. Permutations (The "Ordering" Pattern)

Problems where order matters. You must evaluate every element for every position, iterating from 0 each time while tracking used elements.

```cpp
class PermutationsPattern {
public:
    vector<vector<int>> solvePermutations(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current_perm;
        vector<bool> used(nums.size(), false);
        
        backtrack(nums, used, current_perm, result);
        return result;
    }

private:
    void backtrack(const vector<int>& nums, vector<bool>& used, 
                   vector<int>& current_perm, vector<vector<int>>& result) {
        // Base case: The arrangement is complete
        if (current_perm.size() == nums.size()) {
            result.push_back(current_perm);
            return;
        }
        
        // ALWAYS start from 0 to evaluate all elements
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i]) continue; // Skip used elements
            
            // Make a choice
            current_perm.push_back(nums[i]);
            used[i] = true;
            
            // Recurse
            backtrack(nums, used, current_perm, result);
            
            // Undo choice
            used[i] = false;
            current_perm.pop_back();
        }
    }
};
```

### Recursion Tree — `nums = [1, 2, 3]`

The for-loop always starts from index 0 and skips `used` elements. Every element is considered for every position.

```
                                  solve(perm=[], used={})
                            /            |            \
                       pick 1          pick 2          pick 3
                  solve([1],{1})   solve([2],{2})   solve([3],{3})
                  /        \        /        \        /        \
             pick 2     pick 3  pick 1    pick 3  pick 1    pick 2
          solve([1,2]) solve([1,3]) solve([2,1]) solve([2,3]) solve([3,1]) solve([3,2])
              |           |           |           |           |           |
           pick 3      pick 2      pick 3      pick 1      pick 2      pick 1
          [1,2,3]✓    [1,3,2]✓    [2,1,3]✓    [2,3,1]✓    [3,1,2]✓    [3,2,1]✓
```

Result: `[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1]`  (3! = 6 permutations)

### Classic Array Permutations
- 46\. Permutations
- 47\. Permutations II (Handling duplicates)
- 3437\. Permutations III

### Number & Digit Formation
- 357\. Count Numbers with Unique Digits
- 949\. Largest Time for Given Digits
- 967\. Numbers With Same Consecutive Differences
- 1088\. Confusing Number II
- 2048\. Next Greater Numerically Balanced Number
- 2375\. Construct Smallest Number From DI String
- 2992\. Number of Self-Divisible Permutations

### Array/Sequence Index Constraints
- 526\. Beautiful Arrangement (Number must divide index or vice versa)
- 996\. Number of Squareful Arrays (Adjacent sums must be perfect squares)
- 1415\. The k-th Lexicographical String of All Happy Strings of Length n
- 1718\. Construct the Lexicographically Largest Valid Sequence

### String & Binary Cycle Permutations
- 267\. Palindrome Permutation II
- 1238\. Circular Permutation in Binary Representation

---

## 4. String Partitioning (The "Slicing" Pattern)

Problems where you take a sequence and determine valid indices to "slice" it into contiguous, valid chunks.

```cpp
class StringPartitionPattern {
public:
    vector<vector<string>> solvePartitioning(string s) {
        vector<vector<string>> result;
        vector<string> current_partitions;
        
        backtrack(s, 0, current_partitions, result);
        return result;
    }

private:
    void backtrack(const string& s, int start_index, 
                   vector<string>& current_partitions,
                   vector<vector<string>>& result) {
        // Base case: Reached the end of the string
        if (start_index == s.length()) {
            result.push_back(current_partitions);
            return;
        }
        
        for (int i = start_index; i < s.length(); ++i) {
            // Extract the current slice
            string current_slice = s.substr(start_index, i - start_index + 1);
            
            // Only recurse if the current slice is valid
            if (isValidSlice(current_slice)) {
                current_partitions.push_back(current_slice);
                backtrack(s, i + 1, current_partitions, result);
                current_partitions.pop_back(); // Undo choice
            }
        }
    }
    
    bool isValidSlice(const string& slice) {
        // Implement your validity check here
        return true; 
    }
};
```

### Recursion Tree — Palindrome Partitioning `s = "aab"`

The for-loop tries every possible slice starting at `start_index`. Only palindromic slices proceed.

```
                              solve(start=0, [])
                         /           |            \
                    slice "a"    slice "aa"     slice "aab"
                  (palindrome✓)  (palindrome✓)  (not palindrome✗)
                       |              |
              solve(start=1,["a"])  solve(start=2,["aa"])
                /          \              |
          slice "a"     slice "ab"    slice "b"
        (palindrome✓) (not palin✗)  (palindrome✓)
              |                           |
     solve(start=2,["a","a"])    solve(start=3,["aa","b"])
              |                           |
          slice "b"                    BASE CASE
        (palindrome✓)                 ➜ ["aa","b"] ✓
              |
     solve(start=3,["a","a","b"])
              |
          BASE CASE
         ➜ ["a","a","b"] ✓
```

Result: `["a","a","b"], ["aa","b"]`

### Palindromes & Distinct Properties
- 131\. Palindrome Partitioning
- 2767\. Partition String Into Minimum Beautiful Substrings (Powers of 5)
- 1593\. Split a String Into the Max Number of Unique Substrings

### Word Breaking & Sentence Parsing
- 140\. Word Break II
- 1258\. Synonymous Sentences

### Formatting (IPs & Coordinates)
- 93\. Restore IP Addresses
- 816\. Ambiguous Coordinates

### Math & Number Splitting
- 282\. Expression Add Operators
- 306\. Additive Number
- 842\. Split Array into Fibonacci Sequence
- 1849\. Splitting a String Into Descending Consecutive Values
- 2698\. Find the Punishment Number of an Integer

---

## 5. 2D Grid & Graph Search (The "Pathfinding" Pattern)

Problems navigating a matrix, chess board, or explicit graph where you must temporarily mark nodes/cells as "visited" before recursing into adjacent directions.

```cpp
class GridSearchPattern {
private:
    // Directions: Right, Down, Left, Up
    int dr[4] = {0, 1, 0, -1};
    int dc[4] = {1, 0, -1, 0};
    int ROWS, COLS;

public:
    void solveGrid(vector<vector<char>>& grid) {
        ROWS = grid.size();
        COLS = grid[0].size();
        
        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                backtrack(grid, r, c);
            }
        }
    }

private:
    void backtrack(vector<vector<char>>& grid, int r, int c) {
        // Base cases: Out of bounds or visited/invalid cell
        if (r < 0 || c < 0 || r >= ROWS || c >= COLS || grid[r][c] == '#') {
            return;
        }
        
        // Check if goal is reached here...
        
        // 1. Store original value and mark cell as visited
        char original_value = grid[r][c];
        grid[r][c] = '#'; 
        
        // 2. Explore all adjacent directions
        for (int i = 0; i < 4; ++i) {
            backtrack(grid, r + dr[i], c + dc[i]);
        }
        
        // 3. Backtrack: Restore original value
        grid[r][c] = original_value;
    }
};
```

### Recursion Tree — Word Search `board`, `word = "CAT"`

Starting from cell `(0,0)` containing `'C'`. At each step, try all 4 directions; only matching characters proceed.

```
    Board:            C  A  R
                      X  T  B

                      backtrack(0,0) match 'C' ✓
                     /      |       \       \
                  Right    Down     Left     Up
                 (0,1)    (1,0)   (0,-1)   (-1,0)
                'A'✓      'X'✗    OOB✗     OOB✗
                  |
          backtrack(0,1) match 'A' ✓
           /      |       \       \
        Right    Down     Left     Up
        (0,2)   (1,1)   (0,0)   (-1,1)
        'R'✗    'T'✓   visited✗  OOB✗
                  |
          backtrack(1,1) match 'T' ✓
                  |
            word complete → found "CAT" ✓
```

Cells are marked `'#'` (visited) on the way down and restored on the way back up.

### Matrix Pathfinding & Traversals
- 980\. Unique Paths I
- 980\. Unique Paths II
- 980\. Unique Paths III
- 1219\. Path with Maximum Gold
- 489\. Robot Room Cleaner
- 2850\. Minimum Moves to Spread Stones Over Grid

### Word Search on a Grid
- 79\. Word Search
- 212\. Word Search II (Usually combined with a Trie)

### Board Games (Placement & Movement Constraints)
- 51\. N-Queens
- 52\. N-Queens II
- 37\. Sudoku Solver
- 2664\. The Knight's Tour
- 2056\. Number of Valid Move Combinations On Chessboard

### Explicit Graph & Tree Paths
- 113\. Path Sum II
- 257\. Binary Tree Paths
- 988\. Smallest String Starting From Leaf
- 797\. All Paths From Source to Target
- 2065\. Maximum Path Quality of a Graph

---

## 6. Bin Packing & Complex State Space (The "Distribution" Pattern)

The most complex category. You aren't just forming one group; you are assigning multiple items across `k` different buckets/states, requiring heavy tree-pruning to avoid Time Limit Exceeded (TLE).

```cpp
class BinPackingPattern {
public:
    bool solveBinPacking(vector<int>& items, int k_buckets, int target_capacity) {
        // Sort items descending to place largest items first (Optimization trick)
        sort(items.begin(), items.end(), greater<int>());
        vector<int> buckets(k_buckets, 0);
        
        return backtrack(items, buckets, 0, target_capacity);
    }

private:
    bool backtrack(const vector<int>& items, vector<int>& buckets, 
                   int item_index, int target_capacity) {
        // Base case: All items have been placed
        if (item_index == items.size()) {
            return true;
        }
        
        int current_item = items[item_index];
        
        for (int j = 0; j < buckets.size(); ++j) {
            // Prune: If adding this item exceeds capacity, skip
            if (buckets[j] + current_item > target_capacity) continue;
            
            // Make choice
            buckets[j] += current_item;
            
            // Recurse
            if (backtrack(items, buckets, item_index + 1, target_capacity)) {
                return true; 
            }
            
            // Undo choice
            buckets[j] -= current_item;
            
            // CRITICAL PRUNING: If placing in an empty bucket failed, 
            // placing in subsequent empty buckets will also fail.
            if (buckets[j] == 0) break;
        }
        
        return false;
    }
};
```

### Recursion Tree — `items = [3, 2, 1]`, `k = 2` buckets, `target = 3`

Each item is tried in every bucket. Pruning skips buckets that would overflow and duplicate empty buckets.

```
                        solve(item=0, buckets=[0,0])
                          /                    \
                  3→bucket[0]              3→bucket[1]
              buckets=[3,0]              (bucket[0] is empty & failed → PRUNE)
                    |
            solve(item=1, [3,0])
              /              \
        2→bucket[0]      2→bucket[1]
       [5,0] → 5>3 PRUNE   [3,2]
                              |
                    solve(item=2, [3,2])
                      /              \
                1→bucket[0]      1→bucket[1]
               [4,2] → 4>3 PRUNE   [3,3] → 3>3 PRUNE
                              
                    ... backtrack and try other orderings ...

    With sorted input [3,2,1]:
        bucket[0]=3, bucket[1]=2+1=3  →  [3, 3] ✓  (both equal target)
```

The "empty bucket" pruning is key: if placing an item in one empty bucket fails, all other empty buckets are identical, so we `break`.

### Bin Packing (Distributing items into k equal/constrained buckets)
- 473\. Matchsticks to Square (4 equal buckets)
- 698\. Partition to K Equal Sum Subsets
- 1723\. Find Minimum Time to Finish All Jobs
- 1986\. Minimum Number of Work Sessions to Finish the Tasks
- 2305\. Fair Distribution of Cookies
- 1655\. Distribute Repeating Integers

### Matching, Pairing & Operations
- 1799\. Maximize Score After N Operations
- 1947\. Maximum Compatibility Score Sum
- 1601\. Maximum Number of Achievable Transfer Requests
- 465\. Optimal Account Balancing

### Puzzles & Complex Transitions
- 126\. Word Ladder II
- 351\. Android Unlock Patterns
- 679\. 24 Game
- 756\. Pyramid Transition Matrix
- 773\. Sliding Puzzle
- 1240\. Tiling a Rectangle with the Fewest Squares
- 1307\. Verbal Arithmetic Puzzle
- 301\. Remove Invalid Parentheses
- 691\. Stickers to Spell Word

### Complex Subset Selection (Multiple overlapping conditions)
- 1255\. Maximum Score Words Formed by Letters
- 2397\. Maximum Rows Covered by Columns
- 2708\. Maximum Strength of a Group
- 2151\. Maximum Good People Based on Statements
- 2212\. Maximum Points in an Archery Competition
- 638\. Shopping Offers

### Generators & Highly Specific Math/State Search
- 95\. Unique Binary Search Trees II
- 411\. Minimum Unique Word Abbreviation
- 425\. Word Squares
- 3799\. Word Squares II
- 681\. Next Closest Time
- 1066\. Campus Bikes II
- 1215\. Stepping Numbers
- 1467\. Probability of a Two Boxes Having The Same Number of Distinct Balls
- 2002\. Maximum Product of the Length of Two Palindromic Subsequences
- 2014\. Longest Subsequence Repeated k Times
- 2152\. Minimum Number of Lines to Cover Points
- 3348\. Smallest Divisible Digit Product II
- 3376\. Minimum Time to Break Locks I
- 3646\. Next Special Palindrome Number
- 3669\. Balanced K-Factor Decomposition
