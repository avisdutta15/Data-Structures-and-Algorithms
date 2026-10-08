## Quick Analysis
 - **The Largest Category:** Graph Traversal (58 questions) is your most extensive section, covering everything from basic DFS to complex Shortest Path and Minimum Spanning Tree algorithms.

 - **The Most "Design-Heavy" Section:** Design & Tries has a high concentration of questions (40) per pattern, as these often require implementing full classes rather than just a single function.

 - **The "Core" Logic:** Dynamic Programming and Two Pointers/Sliding Windows make up the backbone of most technical interviews, totaling 102 questions combined.

## 1. Two Pointer Patterns

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 1: Converging** | 11 | [Container With Most Water](Algorithms%20&%20Patterns/1.%20Two%20Pointers/1.%20Converging/1.%20ContainerWithMostWater.cpp) |
|  | 15 | [3Sum](Algorithms%20&%20Patterns/1.%20Two%20Pointers/1.%20Converging/2.%203Sum.cpp) |
|  | 16 | [3Sum Closest](Algorithms%20&%20Patterns/1.%20Two%20Pointers/1.%20Converging/3.%203SumClosest.cpp) |
|  | 18 | [4Sum](Algorithms%20&%20Patterns/1.%20Two%20Pointers/1.%20Converging/4.%204Sum.cpp) |
|  | 167 | [Two Sum II - Input Array Is Sorted](Algorithms%20&%20Patterns/1.%20Two%20Pointers/1.%20Converging/5.%20TwoSum(I)-SortedInput.cpp) |
|  | 349 | [Intersection of Two Arrays](Algorithms%20&%20Patterns/1.%20Two%20Pointers/1.%20Converging/6.%20IntersectionOfTwoArrays.cpp) |
|  | 881 | [Boats to Save People](Algorithms%20&%20Patterns/1.%20Two%20Pointers/1.%20Converging/7.BoatsToSavePeople.cpp) |
|  | 977 | [Squares of a Sorted Array](Algorithms%20&%20Patterns/1.%20Two%20Pointers/1.%20Converging/8.%20SquaresOfASortedArray.cpp) |
|  | 259 | [3Sum Smaller](Algorithms%20&%20Patterns/1.%20Two%20Pointers/1.%20Converging/9.%203SumSmaller.cpp) |
| **Pattern 2: Fast & Slow** | 141 | [Linked List Cycle](Algorithms%20&%20Patterns/1.%20Two%20Pointers/2.%20Fast%20&%20Slow%20Pointer/3.%20LinkedListCycle%20I.cpp) |
|  | 142 | [Linked List Cycle II](Algorithms%20&%20Patterns/1.%20Two%20Pointers/2.%20Fast%20&%20Slow%20Pointer/4.%20LinkedListCycle%20II.cpp) |
|  | 876 | [Middle of the Linked List](Algorithms%20&%20Patterns/1.%20Two%20Pointers/2.%20Fast%20&%20Slow%20Pointer/1.%20MiddleOfLinkedList%20I.cpp) |
|  | 234 | [Palindrome Linked List](Algorithms%20&%20Patterns/1.%20Two%20Pointers/2.%20Fast%20&%20Slow%20Pointer/5.%20PalindromeLinkedList.cpp) |
|  | 143 | [Reorder List](Algorithms%20&%20Patterns/1.%20Two%20Pointers/2.%20Fast%20&%20Slow%20Pointer/8.%20ReorderList.cpp) |
|  | 457 | Circular Array Loop |
|  | 202 | [Happy Number](Algorithms%20&%20Patterns/1.%20Two%20Pointers/2.%20Fast%20&%20Slow%20Pointer/6.%20HappyNumber.cpp) |
|  | 287 | [Find the Duplicate Number](Algorithms%20&%20Patterns/1.%20Two%20Pointers/2.%20Fast%20&%20Slow%20Pointer/7.%20FindTheDuplicateNumber.cpp) |
|  | 392 | Is Subsequence |
| **Pattern 3: Fixed Separation** | 19 | [Remove Nth Node From End of List](Data%20Structure/4.%20LinkedList/3.%20RemoveNthNodeFromEnd.cpp) |
|  | 876 | [Middle of the Linked List](Algorithms%20&%20Patterns/1.%20Two%20Pointers/2.%20Fast%20&%20Slow%20Pointer/1.%20MiddleOfLinkedList%20I.cpp) |
|  | 2095 | [Delete the Middle Node of a Linked List](Data%20Structure/4.%20LinkedList/12.%20DeleteTheMiddleNodeOfALinkedList.cpp) |
| **Pattern 4: In-place Array Modification** | 26 | Remove Duplicates from Sorted Array |
|  | 27 | Remove Element |
|  | 75 | Sort Colors |
|  | 80 | Remove Duplicates from Sorted Array II |
|  | 283 | Move Zeroes |
|  | 443 | String Compression |
|  | 905 | Sort Array By Parity |
|  | 2337 | Move Pieces to Obtain a String |
|  | 2938 | Separate Black and White Balls |
| **Pattern 5: String Comparison (Special)** | 844 | Backspace String Compare |
|  | 1598 | Crawler Log Folder |
|  | 2390 | Removing Stars From a String |
| **Pattern 6: Expanding From Center** | 5 | [Longest Palindromic Substring](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/3.%20Palindromic%20Subsequence/4.%20LongestPalindromicSubstring.cpp) |
|  | 647 | [Palindromic Substrings](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/3.%20Palindromic%20Subsequence/5.%20CountPalindromicSubstrings.cpp) |
| **Pattern 7: String Reversal** | 151 | Reverse Words in a String |
|  | 344 | [Reverse String](Algorithms%20&%20Patterns/1.%20Two%20Pointers/1.%20Running%20From%20Both%20Ends/ReversingOrSwapping/2.ReverseString.cpp) |
|  | 345 | [Reverse Vowels of a String](Algorithms%20&%20Patterns/1.%20Two%20Pointers/1.%20Running%20From%20Both%20Ends/ReversingOrSwapping/3.ReverseVowelsOfAString.cpp) |
|  | 541 | Reverse String II |

## 2. Sliding Window Patterns

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 8: Fixed Size** | 346 | [Moving Average from Data Stream](Algorithms%20&%20Patterns/2.%20Sliding%20Window/1.%20Fixed%20Window%20Size/7.%20MovingAverageFromDataStream.cpp) |
|  | 643 | [Maximum Average Subarray I](Algorithms%20&%20Patterns/2.%20Sliding%20Window/1.%20Fixed%20Window%20Size/9.%20MaximumAverageSubarrayI.cpp) |
|  | 2985 | Calculate Compressed Mean |
|  | 3254 | Find the Power of K-Size Subarrays I |
|  | 3318 | Find X-Sum of All K-Long Subarrays I |
| **Pattern 9: Variable Size** | 3 | [Longest Substring Without Repeating Characters](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/2.%20LongestSubstringWithoutRepeatingCharacter.cpp) |
|  | 76 | [Minimum Window Substring](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/10.%20MinimumWindowSubstring.cpp) |
|  | 209 | [Minimum Size Subarray Sum](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/1.%20MinimumSizeSubarraySum.cpp) |
|  | 219 | [Contains Duplicate II](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/7.%20ContainsDuplicate(II).cpp) |
|  | 424 | [Longest Repeating Character Replacement](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/6.%20LongestRepeatingCharacterReplacement.cpp) |
|  | 713 | [Subarray Product Less Than K](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/8.%20SubarrayProductLessThanK.cpp) |
|  | 904 | [Fruit Into Baskets](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/5.%20FruitsIntoBasket.cpp) |
|  | 1004 | [Max Consecutive Ones III](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/3.%20MaximumConsequtiveOnes(III).cpp) |
|  | 1438 | [Longest Continuous Subarray With Absolute Diff <= Limit](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/14.%20LongestContinuousSubarrayWithAbsoluteDiffLessOrEqualLimit.cpp) |
|  | 1493 | [Longest Subarray of 1's After Deleting One Element](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/4.%20LongestSubarrayof1sAfterDeletingOneElement.cpp) |
|  | 1658 | [Minimum Operations to Reduce X to Zero](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/11.%20MinimumOperationsToReduceXToZero.cpp) |
|  | 1838 | [Frequency of the Most Frequent Element](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/16.%20Frequency%20of%20the%20Most%20Frequent%20Element.cpp) |
|  | 2461 | [Maximum Sum of Distinct Subarrays With Length K](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/9.%20MaximumSumofDistinctSubarraysWithLengthK.cpp) |
|  | 2516 | [Take K of Each Character From Left and Right](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/12.%20TakeKOfEachCharacterFromLeftAndRight.cpp) |
|  | 2762 | [Continuous Subarrays](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/13.%20ContinuousSubarrays.cpp) |
|  | 2779 | [Maximum Beauty of an Array After Applying Operation](Algorithms%20&%20Patterns/2.%20Sliding%20Window/2.%20Variable%20Window%20Size/15.%20MaximumBeautyOfAnArrayAfterApplyingOperation.cpp) |
|  | 2981 | Find Longest Special Substring That Occurs Thrice I |
|  | 3026 | [Maximum Good Subarray Sum](Data%20Structure/5.%20Hash%20Table/2.%20Prefix%20Sum/11.%20MaximumGoodSubarraySum.cpp) |
|  | 3346 | Max Frequency After Performing Operations I |
|  | 3347 | Max Frequency After Performing Operations II |
| **Pattern 10: Monotonic Queue** | 239 | [Sliding Window Maximum](Algorithms%20&%20Patterns/2.%20Sliding%20Window/3.%20Monotonic%20Queue/1.%20SlidingWindowMaximum.cpp) |
|  | 862 | Shortest Subarray with Sum at Least K |
|  | 1696 | Jump Game VI |
| **Pattern 11: Character Freq Matching** | 1 | Two Sum |
|  | 438 | [Find All Anagrams in a String](Algorithms%20&%20Patterns/2.%20Sliding%20Window/1.%20Fixed%20Window%20Size/3.%20FindAllAnagramsInAString.cpp) |
|  | 567 | [Permutation in String](Algorithms%20&%20Patterns/2.%20Sliding%20Window/1.%20Fixed%20Window%20Size/8.%20PermutationInString.cpp) |

## 3. Tree Traversal Patterns (DFS & BFS)

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 12: Level Order Traversal** | 102 | Binary Tree Level Order Traversal |
|  | 103 | Binary Tree Zigzag Level Order Traversal |
|  | 199 | Binary Tree Right Side View |
|  | 515 | Find Largest Value in Each Tree Row |
|  | 1161 | Maximum Level Sum of a Binary Tree |
| **Pattern 13: Recursive Preorder** | 100 | Same Tree |
|  | 101 | Symmetric Tree |
|  | 105 | Construct Binary Tree from Preorder and Inorder |
|  | 114 | [Flatten Binary Tree to Linked List](Data%20Structure/4.%20LinkedList/36.%20FlattenABinaryTreeToLinkedList.cpp) |
|  | 226 | Invert Binary Tree |
|  | 257 | Binary Tree Paths |
|  | 988 | Smallest String Starting From Leaf |
| **Pattern 14: Recursive Inorder** | 94 | Binary Tree Inorder Traversal |
|  | 98 | Validate Binary Search Tree |
|  | 173 | Binary Search Tree Iterator |
|  | 230 | Kth Smallest Element in a BST |
|  | 501 | Find Mode in Binary Search Tree |
|  | 530 | Minimum Absolute Difference in BST |
| **Pattern 15: Recursive Postorder** | 104 | Maximum Depth of Binary Tree |
|  | 110 | Balanced Binary Tree |
|  | 124 | [Binary Tree Maximum Path Sum](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/16.%20DP%20on%20Trees/2.%20BinaryTreeMaximumPathSum.cpp) |
|  | 145 | Binary Tree Postorder Traversal |
|  | 337 | [House Robber III](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/9.%20Fibonacci/6.%20HouseRobber(III).cpp) |
|  | 366 | Find Leaves of Binary Tree |
|  | 543 | [Diameter of Binary Tree](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/16.%20DP%20on%20Trees/1.%20DiameterOfATree.cpp) |
|  | 863 | All Nodes Distance K in Binary Tree |
|  | 1110 | Delete Nodes And Return Forest |
|  | 2458 | Height of Binary Tree After Subtree Removal |
| **Pattern 16: Lowest Common Ancestor** | 235 | Lowest Common Ancestor of a BST |
|  | 236 | Lowest Common Ancestor of a Binary Tree |
| **Pattern 17: Serialization** | 297 | Serialize and Deserialize Binary Tree |
|  | 572 | Subtree of Another Tree |
|  | 652 | Find Duplicate Subtrees |

## 4. Graph Traversal Patterns

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 18: DFS - Islands** | 130 | [Surrounded Regions](Data%20Structure/9.%20Graphs/2.%20BFS%20Variations/1.SurroundedRegions.cpp) |
|  | 200 | [Number of Islands](Data%20Structure/9.%20Graphs/1.%20Simple%20DFS%20BFS/1.%20NumberOfIslands.cpp) |
|  | 417 | Pacific Atlantic Water Flow |
|  | 547 | [Number of Provinces](Data%20Structure/9.%20Graphs/3.%20ConnectedComponents/4.%20NumberOfProvinces.cpp) |
|  | 695 | [Max Area of Island](Data%20Structure/9.%20Graphs/1.%20Simple%20DFS%20BFS/4.%20MaxAreaOfAIsland.cpp) |
|  | 733 | [Flood Fill](Data%20Structure/9.%20Graphs/1.%20Simple%20DFS%20BFS/5.%20FloodFill.cpp) |
|  | 841 | [Keys and Rooms](Data%20Structure/9.%20Graphs/1.%20Simple%20DFS%20BFS/9.%20KeysAndRooms.cpp) |
|  | 1020 | [Number of Enclaves](Data%20Structure/9.%20Graphs/2.%20BFS%20Variations/3.NumberOfEnclaves.cpp) |
|  | 1254 | [Number of Closed Islands](Data%20Structure/9.%20Graphs/2.%20BFS%20Variations/4.NumberOfClosedIslands.cpp) |
|  | 1905 | [Count Sub Islands](Data%20Structure/9.%20Graphs/1.%20Simple%20DFS%20BFS/8.%20CountSubIslands.cpp) |
|  | 2101 | Detonate the Maximum Bombs |
| **Pattern 19: BFS - Islands** | 542 | [01 Matrix](Data%20Structure/9.%20Graphs/2.%20BFS%20Variations/5.01Matrix.cpp) |
|  | 994 | [Rotting Oranges](Data%20Structure/9.%20Graphs/3.%20ConnectedComponents/3.%20RottingOranges.cpp) |
|  | 1091 | [Shortest Path in Binary Matrix](Data%20Structure/9.%20Graphs/2.%20BFS%20Variations/01%20BFS/1.%20ShortestPathInBinaryMatrix.cpp) |
| **Pattern 20: DFS - Cycle Detection** | 207 | [Course Schedule](Data%20Structure/9.%20Graphs/6.%20Topological%20Sorting/1.%20CourseSchedule.cpp) |
|  | 210 | [Course Schedule II](Data%20Structure/9.%20Graphs/6.%20Topological%20Sorting/2.%20CourseSchedule(II).cpp) |
|  | 802 | Find Eventual Safe States |
|  | 1059 | All Paths from Source Lead to Destination |
| **Pattern 21: Topological Sort** | 210 | [Course Schedule II](Data%20Structure/9.%20Graphs/6.%20Topological%20Sorting/2.%20CourseSchedule(II).cpp) |
|  | 269 | [Alien Dictionary](Data%20Structure/9.%20Graphs/6.%20Topological%20Sorting/3.%20AlienDictionary.cpp) |
|  | 310 | [Minimum Height Trees](Data%20Structure/9.%20Graphs/6.%20Topological%20Sorting/4.%20MinimumHeightTrees.cpp) |
|  | 444 | Sequence Reconstruction |
|  | 1136 | [Parallel Courses](Data%20Structure/9.%20Graphs/6.%20Topological%20Sorting/5.%20ParallelCourses.cpp) |
|  | 1857 | Largest Color Value in a Directed Graph |
|  | 2050 | [Parallel Courses III](Data%20Structure/9.%20Graphs/6.%20Topological%20Sorting/6.%20ParallelCourses(III).cpp) |
|  | 2115 | Find All Possible Recipes from Supplies |
|  | 2392 | Build a Matrix With Conditions |
| **Pattern 22: Deep Copy / Cloning** | 133 | [Clone Graph](Data%20Structure/9.%20Graphs/15.%20Misc/1.%20CloneGraph.cpp) |
|  | 1334 | [Find City With Smallest Neighbors at Threshold](Data%20Structure/9.%20Graphs/10.%20ShortestPath-BellmanFord/2.%20FindTheCityWithTheSmallest%20NumberOfNeighborsAtAThresholdDistance.cpp) |
|  | 138 | [Copy List with Random Pointer](Data%20Structure/4.%20LinkedList/27.%20CopyNodesWithRandomPointers.cpp) |
|  | 1490 | Clone N-ary Tree |
| **Pattern 23: Shortest Path** | 743 | [Network Delay Time](Data%20Structure/9.%20Graphs/9.%20ShortestPath-Dijkstra/3.%20NetworkDelayTime.cpp) |
|  | 778 | [Swim in Rising Water](Data%20Structure/9.%20Graphs/9.%20ShortestPath-Dijkstra/8.%20SwimInRisingWater.cpp) |
|  | 1514 | [Path with Maximum Probability](Data%20Structure/9.%20Graphs/9.%20ShortestPath-Dijkstra/7.%20PathWithMaximumProbability.cpp) |
|  | 1631 | [Path With Minimum Effort](Data%20Structure/9.%20Graphs/9.%20ShortestPath-Dijkstra/6.%20PathWithMinimumEffort.cpp) |
|  | 1976 | [Number of Ways to Arrive at Destination](Data%20Structure/9.%20Graphs/9.%20ShortestPath-Dijkstra/105.%20NumberOfWaysToArriveAtDestination.cpp) |
|  | 2045 | Second Minimum Time to Reach Destination |
|  | 2203 | Min Weighted Subgraph With Required Paths |
|  | 2290 | [Minimum Obstacle Removal to Reach Corner](Data%20Structure/9.%20Graphs/2.%20BFS%20Variations/01%20BFS/2.%20MinimumObstacleRemovalToReachCorner.cpp) |
|  | 2577 | Minimum Time to Visit a Cell In a Grid |
|  | 2812 | Find the Safest Path in a Grid |
| **Pattern 24: Shortest Path (K Stops)** | 787 | [Cheapest Flights Within K Stops](Data%20Structure/9.%20Graphs/2.%20BFS%20Variations/9.%20CheapestFlightsWithInKStops.cpp) |
|  | 1129 | Shortest Path with Alternating Colors |
| **Pattern 25: Union-Find** | 200 | [Number of Islands](Data%20Structure/9.%20Graphs/1.%20Simple%20DFS%20BFS/1.%20NumberOfIslands.cpp) |
|  | 261 | [Graph Valid Tree](Data%20Structure/9.%20Graphs/3.%20ConnectedComponents/1.%20GraphValidTree.cpp) |
|  | 305 | [Number of Islands II](Data%20Structure/9.%20Graphs/1.%20Simple%20DFS%20BFS/2.%20NumberOfIslands(II).cpp) |
|  | 323 | [Number of Connected Components](Data%20Structure/9.%20Graphs/3.%20ConnectedComponents/2.%20NumberOfConnectedComponentsInUndirectedGraph.cpp) |
|  | 547 | [Number of Provinces](Data%20Structure/9.%20Graphs/3.%20ConnectedComponents/4.%20NumberOfProvinces.cpp) |
|  | 684 | [Redundant Connection](Data%20Structure/9.%20Graphs/3.%20ConnectedComponents/5.%20RedundantConnection(I).cpp) |
|  | 721 | Accounts Merge |
|  | 737 | Sentence Similarity II |
|  | 947 | [Most Stones Removed with Same Row/Col](Data%20Structure/9.%20Graphs/3.%20ConnectedComponents/7.%20MostStonesRemovedWithSameRowOrColumn.cpp) |
|  | 952 | Largest Component Size by Common Factor |
|  | 959 | Regions Cut By Slashes |
|  | 1101 | Earliest Moment Everyone Become Friends |
| **Pattern 26: SCC** | 210 | [Course Schedule II](Data%20Structure/9.%20Graphs/6.%20Topological%20Sorting/2.%20CourseSchedule(II).cpp) |
|  | 547 | [Number of Provinces](Data%20Structure/9.%20Graphs/3.%20ConnectedComponents/4.%20NumberOfProvinces.cpp) |
|  | 1192 | [Critical Connections in a Network](Data%20Structure/9.%20Graphs/12.%20Bridges%20and%20Articulation%20Points/1.%20CriticalConnectionsInANetwork.cpp) |
|  | 2127 | Max Employees to Be Invited to a Meeting |
| **Pattern 27: Bridges (Tarjan)** | 1192 | [Critical Connections in a Network](Data%20Structure/9.%20Graphs/12.%20Bridges%20and%20Articulation%20Points/1.%20CriticalConnectionsInANetwork.cpp) |
|  | 2360 | [Longest Cycle in a Graph](Data%20Structure/9.%20Graphs/5.%20Cycle%20Detection/1.%20LongestCycleInAGraph.cpp) |
| **Pattern 28: Minimum Spanning Tree** | 1135 | [Connecting Cities With Minimum Cost](Data%20Structure/9.%20Graphs/11.%20Minimum%20Spanning%20Tree/3.%20ConnectingCitiesWithMinimumCost.cpp) |
|  | 1584 | [Min Cost to Connect All Points](Data%20Structure/9.%20Graphs/11.%20Minimum%20Spanning%20Tree/4.%20MinCostToConnectAllPoints.cpp) |
|  | 1168 | Optimize Water Distribution in a Village |
|  | 1489 | Find Critical Edges in MST |
| **Pattern 29: Bidirectional BFS** | 127 | [Word Ladder](Data%20Structure/9.%20Graphs/2.%20BFS%20Variations/6.WordLadder(I).cpp) |
|  | 126 | [Word Ladder II](Data%20Structure/9.%20Graphs/2.%20BFS%20Variations/7.WordLadder(II).cpp) |
|  | 815 | Bus Routes |

## 5. Dynamic Programming (DP) Patterns

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 30: Fibonacci Style** | 70 | [Climbing Stairs](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/9.%20Fibonacci/2.%20ClimbingStairs.cpp) |
|  | 91 | [Decode Ways](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/9.%20Fibonacci/3.%20DecodeWays.cpp) |
|  | 198 | [House Robber](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/9.%20Fibonacci/4.%20HouseRobber(I).cpp) |
|  | 213 | [House Robber II](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/9.%20Fibonacci/5.%20HouseRobber(II).cpp) |
|  | 337 | [House Robber III](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/9.%20Fibonacci/6.%20HouseRobber(III).cpp) |
|  | 509 | [Fibonacci Number](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/9.%20Fibonacci/1.%20FibonacciNumber.cpp) |
|  | 740 | Delete and Earn |
|  | 746 | [Min Cost Climbing Stairs](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/9.%20Fibonacci/7.%20MinCostClimbingStairs.cpp) |
| **Pattern 31: Kadane's Algorithm** | 53 | [Maximum Subarray](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/11.%20Kadane/1.%20MaximumSumSubarray.cpp) |
|  | 918 | [Maximum Sum Circular Subarray](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/11.%20Kadane/2.%20MaximumCircularSubarraySum.cpp) |
|  | 2321 | Max Score Of Spliced Array |
|  | 1749 | Max Absolute Sum of Any Subarray |
|  | 152 | [Maximum Product Subarray](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/11.%20Kadane/4.%20MaximumProductSubarray.cpp) |
| **Pattern 32: Unbounded Knapsack** | 322 | [Coin Change](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/0.%20Knapsack/23.%20CoinChange(MinimumNumberOfCoins).cpp) |
|  | 377 | [Combination Sum IV](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/0.%20Knapsack/28.%20CombinationSum(IV).cpp) |
|  | 518 | [Coin Change II](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/0.%20Knapsack/22.%20CoinChange(TotalWays).cpp) |
| **Pattern 33: 0/1 Knapsack / Subset** | 416 | [Partition Equal Subset Sum](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/0.%20Knapsack/10.%20EqualSumPartition.cpp) |
|  | 494 | [Target Sum](Algorithms%20&%20Patterns/5.%20Backtracking/1.%20IncludeExclude/12.TargetSum.cpp) |
| **Pattern 34: Word Break Style** | 139 | [Word Break](Algorithms%20&%20Patterns/5.%20Backtracking/4.%20String%20Partitioning/4.WordBreak.cpp) |
|  | 140 | [Word Break II](Algorithms%20&%20Patterns/5.%20Backtracking/4.%20String%20Partitioning/5.WordBreak(II).cpp) |
| **Pattern 35: LCS Style** | 1143 | [Longest Common Subsequence](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/MainPatterns/5.LongestCommonSubsequence.cpp) |
|  | 1092 | Shortest Common Supersequence |
|  | 1312 | Min Insertion Steps for Palindrome |
| **Pattern 36: Edit Distance** | 72 | Edit Distance |
|  | 583 | Delete Operation for Two Strings |
|  | 712 | Minimum ASCII Delete Sum |
| **Pattern 37: Unique Paths / Grid** | 62 | [Unique Paths](Algorithms%20&%20Patterns/5.%20Backtracking/5.%20Grid/1.UniquePaths(I).cpp) |
|  | 63 | [Unique Paths II](Algorithms%20&%20Patterns/5.%20Backtracking/5.%20Grid/2.UniquePaths(II).cpp) |
|  | 64 | [Minimum Path Sum](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/15.%20DP%20On%20Grids/3.%20MinimumPathSum.cpp) |
|  | 120 | [Triangle](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/15.%20DP%20On%20Grids/6.%20MinPathSumTriangle.cpp) |
|  | 221 | [Maximal Square](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/15.%20DP%20On%20Grids/8.%20MaximalSquare.cpp) |
|  | 931 | [Minimum Falling Path Sum](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/15.%20DP%20On%20Grids/4.%20MaxPathSumFromFirstRowToLastRow-MaximumFallingPathSum.cpp) |
|  | 1277 | Count Square Submatrices with All Ones |
| **Pattern 38: Interval DP** | 312 | Burst Balloons |
|  | 546 | Remove Boxes |
| **Pattern 39: Catalan Numbers** | 95 | Unique Binary Search Trees II |
|  | 96 | Unique Binary Search Trees |
|  | 241 | [Different Ways to Add Parentheses](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/14.%20CatalanNumbers/4.%20DifferentWaysToAddParentheses.cpp) |
| **Pattern 40: LIS Style** | 300 | [Longest Increasing Subsequence](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/MainPatterns/6.LIS.cpp) |
|  | 354 | Russian Doll Envelopes |
|  | 1671 | Min Removals to Make Mountain Array |
|  | 2407 | Longest Increasing Subsequence II |
| **Pattern 41: Stock Problems** | 121 | [Best Time to Buy and Sell Stock](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/21.%20State%20Machine%20DP%20(DP%20on%20Stocks)/1.%20BestTimeToBuyAndSellStock(I).cpp) |
|  | 122 | [Best Time to Buy and Sell Stock II](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/21.%20State%20Machine%20DP%20(DP%20on%20Stocks)/2.%20BestTimeToBuyAndSellStock(II).cpp) |
|  | 123 | [Best Time to Buy and Sell Stock III](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/21.%20State%20Machine%20DP%20(DP%20on%20Stocks)/3.%20BestTimeToBuyAndSellStock(III).cpp) |
|  | 188 | [Best Time to Buy and Sell Stock IV](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/21.%20State%20Machine%20DP%20(DP%20on%20Stocks)/4.%20BestTimeToBuyAndSellStock(IV).cpp) |
|  | 309 | [Stock with Cooldown](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/21.%20State%20Machine%20DP%20(DP%20on%20Stocks)/5.%20BestTimeToBuyAndSellStockwithCooldown.cpp) |

## 6. Heap (Priority Queue) Patterns

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 42: Top K Elements** | 215 | [Kth Largest Element in an Array](Data%20Structure/8.%20Heap/2.%20Top%20K%20Elements/1.%20KthLargestElementInAnArray.cpp) |
|  | 347 | [Top K Frequent Elements](Data%20Structure/8.%20Heap/2.%20Top%20K%20Elements/2.%20TopKFrequentElements.cpp) |
|  | 451 | [Sort Characters By Frequency](Data%20Structure/8.%20Heap/2.%20Top%20K%20Elements/3.%20SortCharactersByFrequency.cpp) |
|  | 506 | [Relative Ranks](Data%20Structure/8.%20Heap/2.%20Top%20K%20Elements/4.%20RelativeRanks.cpp) |
|  | 703 | [Kth Largest Element in a Stream](Data%20Structure/8.%20Heap/2.%20Top%20K%20Elements/5.%20KthLargestElementInAStream.cpp) |
|  | 973 | [K Closest Points to Origin](Data%20Structure/8.%20Heap/2.%20Top%20K%20Elements/6.%20KClosestPointToOrigin.cpp) |
|  | 1046 | [Last Stone Weight](Data%20Structure/8.%20Heap/2.%20Top%20K%20Elements/7.%20LastStoneWeight.cpp) |
|  | 2558 | Take Gifts From the Richest Pile |
| **Pattern 43: Two Heaps (Median)** | 295 | [Find Median from Data Stream](Data%20Structure/8.%20Heap/3.%20Two%20Heaps/1.%20FindMedianFromDataStreams.cpp) |
|  | 480 | [Sliding Window Median](Data%20Structure/8.%20Heap/3.%20Two%20Heaps/2.%20SlidingWindowMedian.cpp) |
|  | 1825 | [Finding MK Average](Data%20Structure/8.%20Heap/3.%20Two%20Heaps/3.%20FindingMKAverage.cpp) |
| **Pattern 44: K-way Merge** | 23 | [Merge k Sorted Lists](Data%20Structure/8.%20Heap/4.%20K%20Way%20Merge/1.%20MergeKSortedLists.cpp) |
|  | 373 | [Find K Pairs with Smallest Sums](Data%20Structure/8.%20Heap/4.%20K%20Way%20Merge/5.%20FindKPairsWithSmallestSum.cpp) |
|  | 378 | [Kth Smallest Element in a Sorted Matrix](Data%20Structure/8.%20Heap/4.%20K%20Way%20Merge/4.%20KthSmallestElementInASortedMatrix.cpp) |
|  | 632 | [Smallest Range Covering Elements](Data%20Structure/8.%20Heap/4.%20K%20Way%20Merge/6.%20SmallestRangeConveringElementsFromKLists.cpp) |
| **Pattern 45: Scheduling / Min Cost** | 253 | [Meeting Rooms II](Algorithms%20&%20Patterns/4.%20Greedy/1.%20Intervals/5.%20MeetingRoomsII.cpp) |
|  | 767 | [Reorganize String](Data%20Structure/8.%20Heap/5.%20Scheduling%20and%20Min-Cost/1.%20ReorganizeString.cpp) |
|  | 358 | [Rearrange String k Distance Apart](Data%20Structure/8.%20Heap/5.%20Scheduling%20and%20Min-Cost/2.%20RearrangeStringKDistanceApart.cpp) |
|  | 857 | Minimum Cost to Hire K Workers |
|  | 1642 | [Furthest Building You Can Reach](Data%20Structure/8.%20Heap/5.%20Scheduling%20and%20Min-Cost/3.%20FurthestBuildingYouCanReach.cpp) |
|  | 1792 | Maximum Average Pass Ratio |
|  | 1834 | Single-Threaded CPU |
|  | 1942 | Number of the Smallest Unoccupied Chair |
|  | 2402 | Meeting Rooms III |
| **Pattern : Misc** | 502 | IPO (https://www.youtube.com/watch?v=b12SZXrZF9I) |
|  |  | Sort an almost(K) sorted array |
|  |  |Minimum Number Of refueling stops |
|  |  |The Skyline Problem |

## 7. Backtracking Patterns

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 46: Subsets** | 17 | [Letter Combinations of a Phone Number](Algorithms%20&%20Patterns/5.%20Backtracking/1.%20IncludeExclude/14.LetterCombinationsOfAPhoneNumber.cpp) |
|  | 77 | [Combinations](Algorithms%20&%20Patterns/5.%20Backtracking/2.%20For-Loop-idx%20based/2.Combinations.cpp) |
|  | 78 | [Subsets](Algorithms%20&%20Patterns/5.%20Backtracking/1.%20IncludeExclude/1.Subsets(PrintAll)-One-CountWithSumK.cpp) |
|  | 90 | [Subsets II](Algorithms%20&%20Patterns/5.%20Backtracking/2.%20For-Loop-idx%20based/3.Subsets(II).cpp) |
| **Pattern 47: Permutations** | 31 | Next Permutation |
|  | 46 | [Permutations](Algorithms%20&%20Patterns/5.%20Backtracking/3.%20Permutations/1.Permutations(I).cpp) |
|  | 60 | Permutation Sequence |
| **Pattern 48: Combination Sum** | 39 | [Combination Sum](Algorithms%20&%20Patterns/5.%20Backtracking/1.%20IncludeExclude/17.CombinationSum(I).cpp) |
|  | 40 | [Combination Sum II](Algorithms%20&%20Patterns/5.%20Backtracking/2.%20For-Loop-idx%20based/4.CombinationSum(II).cpp) |
| **Pattern 49: Parentheses Generation** | 22 | [Generate Parentheses](Algorithms%20&%20Patterns/5.%20Backtracking/1.%20IncludeExclude/8.GenerateParenthesis.cpp) |
|  | 301 | Remove Invalid Parentheses |
| **Pattern 50: Word Search / Grid** | 79 | Word Search |
|  | 212 | Word Search II |
|  | 2018 | Check if Word Can Be Placed In Crossword |
| **Pattern 51: Constraint Satisfaction** | 37 | Sudoku Solver |
|  | 51 | N-Queens |
| **Pattern 52: Palindrome Partitioning** | 131 | [Palindrome Partitioning](Algorithms%20&%20Patterns/5.%20Backtracking/4.%20String%20Partitioning/1.PalindromePartitioning.cpp) |
|  | 132 | [Palindrome Partitioning II](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/12.%20Matrix%20Chain%20Multiplication/2.PalindromePartition(II).cpp) |
|  | 1457 | Pseudo-Palindromic Paths in a Tree |

## 8. Greedy Patterns

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 53: Intervals** | 56 | [Merge Intervals](Algorithms%20&%20Patterns/4.%20Greedy/1.%20Intervals/2.%20MergeIntervals.cpp) |
|  | 57 | [Insert Interval](Algorithms%20&%20Patterns/4.%20Greedy/1.%20Intervals/3.%20InsertInterval.cpp) |
|  | 759 | Employee Free Time |
|  | 986 | Interval List Intersections |
|  | 2406 | Divide Intervals Into Min Groups |
| **Pattern 54: Jump Game** | 45 | Jump Game II |
|  | 55 | Jump Game |
| **Pattern 55: Buy/Sell Stock** | 121 | [Best Time to Buy and Sell Stock](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/21.%20State%20Machine%20DP%20(DP%20on%20Stocks)/1.%20BestTimeToBuyAndSellStock(I).cpp) |
|  | 122 | [Best Time to Buy and Sell Stock II](Algorithms%20&%20Patterns/6.%20Dynamic%20Programming/21.%20State%20Machine%20DP%20(DP%20on%20Stocks)/2.%20BestTimeToBuyAndSellStock(II).cpp) |
| **Pattern 56: Gas Station Circuit** | 134 | [Gas Station](Algorithms%20&%20Patterns/4.%20Greedy/GasStation.cpp) |
|  | 2202 | Maximize Topmost Element After K Moves |
| **Pattern 57: Task Scheduling** | 621 | Task Scheduler |
|  | 767 | [Reorganize String](Data%20Structure/8.%20Heap/5.%20Scheduling%20and%20Min-Cost/1.%20ReorganizeString.cpp) |
|  | 1054 | Distant Barcodes |
| **Pattern 58: Sorting Based** | 455 | Assign Cookies |
|  | 135 | Candy |
|  | 406 | Queue Reconstruction by Height |
|  | 1029 | Two City Scheduling |

## 9. Binary Search Patterns

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 59: On Sorted Array** | 35 | Search Insert Position |
|  | 69 | Sqrt(x) |
|  | 74 | [Search a 2D Matrix](Algorithms%20&%20Patterns/3.%20Divide%20And%20Conquer/3.%20Binary%20Search/1.%20Standard%20Binary%20Search/SearchIn2DMatrix.cpp) |
|  | 278 | First Bad Version |
|  | 374 | Guess Number Higher or Lower |
|  | 540 | Single Element in a Sorted Array |
|  | 704 | Binary Search |
|  | 1539 | Kth Missing Positive Number |
| **Pattern 60: Rotated / Peak** | 33 | [Search in Rotated Sorted Array](Algorithms%20&%20Patterns/3.%20Divide%20And%20Conquer/3.%20Binary%20Search/2.%20Rotated%20&%20Peak/1.SearchInSortedRotatedArray.cpp) |
|  | 81 | [Search in Rotated Sorted Array II](Algorithms%20&%20Patterns/3.%20Divide%20And%20Conquer/3.%20Binary%20Search/2.%20Rotated%20&%20Peak/2.SearchInSortedRotatedArray(II).cpp) |
|  | 153 | [Find Minimum in Rotated Sorted Array](Algorithms%20&%20Patterns/3.%20Divide%20And%20Conquer/3.%20Binary%20Search/2.%20Rotated%20&%20Peak/3.FindMinimumInSortedRotatedArray.cpp) |
|  | 162 | [Find Peak Element](Algorithms%20&%20Patterns/3.%20Divide%20And%20Conquer/3.%20Binary%20Search/2.%20Rotated%20&%20Peak/5.FindPeakElement.cpp) |
|  | 852 | Peak Index in a Mountain Array |
|  | 1095 | Find in Mountain Array |
| **Pattern 61: On Answer / Condition** | 410 | [Split Array Largest Sum](Algorithms%20&%20Patterns/3.%20Divide%20And%20Conquer/3.%20Binary%20Search/5.%20Binary%20Search%20On%20Answer/2.%20SplitArrayLargestSum.cpp) |
|  | 774 | Minimize Max Distance to Gas Station |
|  | 875 | Koko Eating Bananas |
|  | 1011 | [Capacity To Ship Packages Within D Days](Algorithms%20&%20Patterns/3.%20Divide%20And%20Conquer/3.%20Binary%20Search/5.%20Binary%20Search%20On%20Answer/4.%20CapacityToShipPackagesWithinDDays.cpp) |
|  | 1482 | [Min Days to Make m Bouquets](Algorithms%20&%20Patterns/3.%20Divide%20And%20Conquer/3.%20Binary%20Search/5.%20Binary%20Search%20On%20Answer/3.%20MinimumNumberOfDaysToMakeMBouquets.cpp) |
|  | 1760 | Minimum Limit of Balls in a Bag |
|  | 2064 | Minimized Max of Products to Any Store |
|  | 2226 | Max Candies Allocated to K Children |
| **Pattern 62: First/Last Occurrence** | 34 | Find First and Last Position in Sorted Array |
|  | 658 | Find K Closest Elements |
| **Pattern 63: Median / Kth Smallest** | 4 | [Median of Two Sorted Arrays](Algorithms%20&%20Patterns/3.%20Divide%20And%20Conquer/3.%20Binary%20Search/6.%20KthElementOrMedian/1.%20MedianOf2SortedArrays.cpp) |
|  | 719 | Find K-th Smallest Pair Distance |
|  | 378 | [Kth Smallest Element in a Sorted Matrix](Data%20Structure/8.%20Heap/4.%20K%20Way%20Merge/4.%20KthSmallestElementInASortedMatrix.cpp) |

## 10. Stack Patterns

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 64: Parentheses Matching** | 20 | [Valid Parentheses](Data%20Structure/2.%20Stack/1.%20Parenthesis/1.%20ValidParentheses.cpp) |
|  | 32 | [Longest Valid Parentheses](Data%20Structure/2.%20Stack/1.%20Parenthesis/2.%20LongestValidParentheses.cpp) |
|  | 921 | [Minimum Add to Make Parentheses Valid](Data%20Structure/2.%20Stack/1.%20Parenthesis/3.%20MinimumAddToMakeParenthesesValid.cpp) |
|  | 1249 | [Minimum Remove to Make Valid Parentheses](Data%20Structure/2.%20Stack/1.%20Parenthesis/4.%20MinimumRemoveToMakeValidParentheses.cpp) |
|  | 1963 | Min Swaps to Make String Balanced |
| **Pattern 65: Monotonic Stack** | 402 | [Remove K Digits](Data%20Structure/2.%20Stack/3.%20Monotonic%20Stack/8.%20RemoveKDigits.cpp) |
|  | 496 | [Next Greater Element I](Data%20Structure/2.%20Stack/3.%20Monotonic%20Stack/5.%20NextGreaterElement%20I.cpp) |
|  | 503 | [Next Greater Element II](Data%20Structure/2.%20Stack/3.%20Monotonic%20Stack/6.%20NextGreaterElement%20II.cpp) |
|  | 739 | [Daily Temperatures](Data%20Structure/2.%20Stack/3.%20Monotonic%20Stack/9.%20DailyTemparatures.cpp) |
|  | 901 | [Online Stock Span](Data%20Structure/2.%20Stack/3.%20Monotonic%20Stack/7.%20OnlineStockSpan.cpp) |
|  | 907 | [Sum of Subarray Minimums](Data%20Structure/2.%20Stack/3.%20Monotonic%20Stack/10.%20SumOfSubarrayMinimums.cpp) |
|  | 962 | Maximum Width Ramp |
|  | 1475 | [Final Prices With a Special Discount](Data%20Structure/2.%20Stack/3.%20Monotonic%20Stack/15.%20FinalPriceWithASpecialDiscountInAShop.cpp) |
|  | 1673 | Find the Most Competitive Subsequence |
| **Pattern 66: Expression Evaluation** | 150 | Evaluate Reverse Polish Notation |
|  | 224 | Basic Calculator |
|  | 227 | [Basic Calculator II](Data%20Structure/2.%20Stack/4.%20Expressions%20&%20Calculator/1.%20BasicCalculator%20II%20.cpp) |
|  | 772 | Basic Calculator III |
| **Pattern 67: Simulation / Helper** | 71 | Simplify Path |
|  | 394 | Decode String |
|  | 735 | [Asteroid Collision](Data%20Structure/2.%20Stack/3.%20Monotonic%20Stack/11.%20AsteroidCollision.cpp) |
| **Pattern 68: Design (Min Stack)** | 155 | [Min Stack](Data%20Structure/2.%20Stack/2.%20Implementations%20&%20Operations/6.%20DesignMinimumStack.cpp) |
|  | 895 | [Maximum Frequency Stack](Data%20Structure/2.%20Stack/2.%20Implementations%20&%20Operations/15.%20MaximumFrequencyStack.cpp) |
|  | 901 | [Online Stock Span](Data%20Structure/2.%20Stack/3.%20Monotonic%20Stack/7.%20OnlineStockSpan.cpp) |
| **Pattern 69: Histogram / Rectangle** | 84 | [Largest Rectangle in Histogram](Data%20Structure/2.%20Stack/3.%20Monotonic%20Stack/13.%20LargestRectangleInHistogram.cpp) |
|  | 85 | [Maximal Rectangle](Data%20Structure/2.%20Stack/3.%20Monotonic%20Stack/14.%20MaximalRectangle.cpp) |

## 11. Bit Manipulation Patterns

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 70: Bitwise XOR** | 136 | Single Number |
|  | 137 | Single Number II |
|  | 268 | [Missing Number](Algorithms%20&%20Patterns/Sorting/1.%20Cyclic%20Sort/3.MissingNumber.cpp) |
|  | 389 | Find the Difference |
| **Pattern 71: Bitwise AND / Hamming** | 191 | Number of 1 Bits |
|  | 231 | Power of Two |
|  | 477 | Total Hamming Distance |
| **Pattern 72: Bitwise DP** | 338 | Counting Bits |
|  | 1494 | Parallel Courses II |
|  | 1442 | Count Triplets With Equal XOR |
| **Pattern 73: Power Checks** | 231 | Power of Two |
|  | 342 | Power of Four |

## 12. Linked List Manipulation Patterns

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 74: In-place Reversal** | 83 | [Remove Duplicates from Sorted List](Data%20Structure/4.%20LinkedList/8.%20RemoveDuplicatesFromSortedList.cpp) |
|  | 92 | [Reverse Linked List II](Data%20Structure/4.%20LinkedList/20.%20ReverseList(II).cpp) |
|  | 206 | [Reverse Linked List](Data%20Structure/4.%20LinkedList/19.%20ReverseList.cpp) |
|  | 25 | [Reverse Nodes in k-Group](Data%20Structure/4.%20LinkedList/21.%20ReverseALinkedListInGroupsOfGivenSize.cpp) |
|  | 234 | [Palindrome Linked List](Algorithms%20&%20Patterns/1.%20Two%20Pointers/2.%20Fast%20&%20Slow%20Pointer/5.%20PalindromeLinkedList.cpp) |
|  | 82 | [Remove Duplicates from Sorted List II](Data%20Structure/4.%20LinkedList/9.%20DeleteDuplicatesFromSortedList(II).cpp) |
| **Pattern 75: Merging** | 21 | [Merge Two Sorted Lists](Data%20Structure/4.%20LinkedList/29.%20MergeTwoSortedLists.cpp) |
|  | 23 | [Merge k Sorted Lists](Data%20Structure/8.%20Heap/4.%20K%20Way%20Merge/1.%20MergeKSortedLists.cpp) |
| **Pattern 76: Addition** | 2 | [Add Two Numbers](Data%20Structure/4.%20LinkedList/25.%20AddTwoNumbers.cpp) |
|  | 369 | Plus One Linked List |
| **Pattern 77: Intersection** | 160 | [Intersection of Two Linked Lists](Data%20Structure/4.%20LinkedList/14.%20DetectCycleInAListAndFirstNodeInCycle.cpp) |
|  | 599 | Minimum Index Sum of Two Lists |
| **Pattern 78: Reorder / Partition** | 24 | Swap Nodes in Pairs |
|  | 61 | Rotate List |
|  | 86 | [Partition List](Data%20Structure/4.%20LinkedList/18.%20PartitionList.cpp) |
|  | 143 | [Reorder List](Algorithms%20&%20Patterns/1.%20Two%20Pointers/2.%20Fast%20&%20Slow%20Pointer/8.%20ReorderList.cpp) |
|  | 328 | [Odd Even Linked List](Data%20Structure/4.%20LinkedList/16.%20OddEvenList.cpp) |

## 13. Array/Matrix Manipulation Patterns

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 79: In-place Rotation** | 48 | [Rotate Image](Data%20Structure/1.%20Arrays%20&%20Matrix/2.%20Matrix/1.%20RotateImage.cpp) |
|  | 189 | Rotate Array |
|  | 867 | Transpose Matrix |
| **Pattern 80: Spiral Traversal** | 54 | [Spiral Matrix](Data%20Structure/1.%20Arrays%20&%20Matrix/2.%20Matrix/2.%20SpiralMatrix.cpp) |
|  | 59 | [Spiral Matrix II](Data%20Structure/1.%20Arrays%20&%20Matrix/2.%20Matrix/3.%20SpiralMatrix(II).cpp) |
|  | 885 | [Spiral Matrix III](Data%20Structure/1.%20Arrays%20&%20Matrix/2.%20Matrix/4.%20SpiralMatrix(III).cpp) |
|  | 2326 | Spiral Matrix IV |
| **Pattern 81: In-place Marking** | 73 | Set Matrix Zeroes |
|  | 289 | Game of Life |
|  | 498 | Diagonal Traverse |
| **Pattern 82: Prefix/Suffix Products** | 238 | [Product of Array Except Self](Data%20Structure/5.%20Hash%20Table/2.%20Prefix%20Sum/8.%20ProductOfArrayExceptSelf.cpp) |
|  | 845 | Longest Mountain in Array |
|  | 2483 | Minimum Penalty for a Shop |
| **Pattern 83: Math / Simulation** | 66 | Plus One |
|  | 43 | Multiply Strings |
|  | 989 | Add to Array-Form of Integer |
|  | 67 | Add Binary |
| **Pattern 84: In-place from End** | 88 | Merge Sorted Array |
|  | 977 | [Squares of a Sorted Array](Algorithms%20&%20Patterns/1.%20Two%20Pointers/1.%20Converging/8.%20SquaresOfASortedArray.cpp) |
| **Pattern 85: Cyclic Sort** | 41 | [First Missing Positive](Algorithms%20&%20Patterns/Sorting/1.%20Cyclic%20Sort/8.FirstMissingPositive.cpp) |
|  | 268 | [Missing Number](Algorithms%20&%20Patterns/Sorting/1.%20Cyclic%20Sort/3.MissingNumber.cpp) |
|  | 287 | [Find the Duplicate Number](Algorithms%20&%20Patterns/1.%20Two%20Pointers/2.%20Fast%20&%20Slow%20Pointer/7.%20FindTheDuplicateNumber.cpp) |
|  | 442 | [Find All Duplicates in an Array](Algorithms%20&%20Patterns/Sorting/1.%20Cyclic%20Sort/6.FindAllDuplicatesInAnArray.cpp) |
|  | 448 | [Find All Numbers Disappeared in Array](Algorithms%20&%20Patterns/Sorting/1.%20Cyclic%20Sort/4.FindAllDisappearedNumbers1toN.cpp) |

## 14. String Manipulation Patterns

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 86: Palindrome Check** | 9 | Palindrome Number |
|  | 125 | [Valid Palindrome](Algorithms%20&%20Patterns/1.%20Two%20Pointers/1.%20Running%20From%20Both%20Ends/ReversingOrSwapping/1.ValidPalindrome.cpp) |
|  | 680 | Valid Palindrome II |
| **Pattern 87: Anagram Check** | 49 | [Group Anagrams](Data%20Structure/5.%20Hash%20Table/1.%20Frequency%20Counting%20And%20Anagram/1.%20GroupAnagrams.cpp) |
|  | 242 | [Valid Anagram](Data%20Structure/5.%20Hash%20Table/1.%20Frequency%20Counting%20And%20Anagram/2.%20ValidAnagram.cpp) |
| **Pattern 88: Roman Conversion** | 13 | Roman to Integer |
|  | 12 | Integer to Roman |
| **Pattern 89: String to Int (atoi)** | 8 | String to Integer (atoi) |
|  | 65 | Valid Number |
| **Pattern 90: Manual Simulation** | 43 | Multiply Strings |
|  | 415 | Add Strings |
|  | 67 | Add Binary |
| **Pattern 91: String Matching** | 28 | Index of First Occurrence |
|  | 214 | Shortest Palindrome |
|  | 686 | Repeated String Match |
|  | 796 | Rotate String |
|  | 3008 | Beautiful Indices in Given Array II |
| **Pattern 92: Repeated Substring** | 459 | Repeated Substring Pattern |
|  | 28 | Index of First Occurrence |
|  | 686 | Repeated String Match |

## 15. Design Patterns & Tries

| Pattern | LC Code | Problem Name |
| --- | --- | --- |
| **Pattern 93: Design (System/DS)** | 146 | [LRU Cache](Data%20Structure/11.%20Design/1.%20LRU.cpp) |
|  | 155 | [Min Stack](Data%20Structure/2.%20Stack/2.%20Implementations%20&%20Operations/6.%20DesignMinimumStack.cpp) |
|  | 225 | [Implement Stack using Queues](Data%20Structure/11.%20Design/5.%20ImplementStackUsingQueues.cpp) |
|  | 232 | [Implement Queue using Stacks](Data%20Structure/11.%20Design/4.%20ImplementQueueUsingStacks.cpp) |
|  | 251 | Flatten 2D Vector |
|  | 271 | Encode and Decode Strings |
|  | 295 | [Find Median from Data Stream](Data%20Structure/8.%20Heap/3.%20Two%20Heaps/1.%20FindMedianFromDataStreams.cpp) |
|  | 341 | Flatten Nested List Iterator |
|  | 346 | [Moving Average from Data Stream](Algorithms%20&%20Patterns/2.%20Sliding%20Window/1.%20Fixed%20Window%20Size/7.%20MovingAverageFromDataStream.cpp) |
|  | 353 | Design Snake Game |
|  | 359 | Logger Rate Limiter |
|  | 362 | [Design Hit Counter](Data%20Structure/11.%20Design/26.%20HitCounter.cpp) |
|  | 379 | [Design Phone Directory](Data%20Structure/11.%20Design/35.%20PhoneDirectory.cpp) |
|  | 380 | Insert Delete GetRandom O(1) |
|  | 432 | All O`one Data Structure |
|  | 460 | [LFU Cache](Data%20Structure/11.%20Design/2.%20LFU.cpp) |
|  | 604 | Design Compressed String Iterator |
|  | 622 | Design Circular Queue |
|  | 641 | Design Circular Deque |
|  | 642 | Design Search Autocomplete System |
|  | 706 | Design HashMap |
|  | 715 | Range Module |
|  | 900 | RLE Iterator |
|  | 981 | Time Based Key-Value Store |
|  | 1146 | Snapshot Array |
|  | 1348 | Tweet Counts Per Frequency |
|  | 1352 | Product of the Last K Numbers |
|  | 1381 | Design a Stack With Increment |
|  | 1756 | Design Most Recently Used Queue |
|  | 2013 | Detect Squares |
|  | 2034 | Stock Price Fluctuation |
|  | 2296 | Design a Text Editor |
|  | 2336 | [Smallest Number in Infinite Set](Data%20Structure/11.%20Design/34.%20SmallestNumberInInfiniteSet.cpp) |
| **Pattern 94: Tries** | 208 | [Implement Trie (Prefix Tree)](Data%20Structure/Trie/1.Trie.cpp) |
|  | 211 | Design Add and Search Words |
|  | 720 | Longest Word in Dictionary |
|  | 648 | Replace Words |
|  | 425 | Word Squares |
|  | 642 | Design Search Autocomplete System |
|  | 745 | Prefix and Suffix Search |

---