# Stack Topic Order

## 1. Monotonic Stack
https://www.youtube.com/watch?v=Dq_ObZwTY_Q&list=PLA96ZCqAS-Ysbg74pGnOF7qFGWj24HmY-&index=2&pp=iAQB
| Id | Problem | Comment / Urls |
|----|---------|----------------|
| 1 | Next Greater Element | Left to right traversal + Monotonic Decreasing Stack |
| 2 | Next Smaller Element | Left to right traversal + Monotonic Increasing Stack |
| 3 | Previous Greater Element | Right to left traversal + Monotonic Decreasing Stack |
| 4 | Previous Smaller Element | Right to left traversal + Monotonic Increasing Stack |
| 5 | Next Greater Element I [LC: 496]  | (NGE + HashTable) |
| 6 | Next Greater Element II [LC: 503] | Circular array. </br> <pre><code> nge[n]</br> for(int i=2*n-1; i>=0; i--){</br>    //actual element </br>    int j = i%n;</br>    ....ops on nums[j]</br> }</br></code></pre> https://www.youtube.com/watch?v=7PrncD7v9YQ |
| 7 | Online Stock Span [LC: 901] | |
| 8 | Trapping Rain Water [LC: 42] | |
| 9 | Largest Rectangle in Histogram [LC: 84]| |
| 10 | Maximal Rectangle [LC: 85] | |
| 11 | Daily Temperatures [LC: 739] | https://www.youtube.com/watch?v=ZhZEmGv-sOY |
| 255 | Verify Preorder Sequence in Binary Search Tree | |
| 316 | Remove Duplicate Letters | https://www.youtube.com/watch?v=rU5p0MRm5zU |
| 321 | Create Maximum Number | |
| 402 | Remove K Digits | https://www.youtube.com/watch?v=cFabMOnJaq0; edge cases: https://www.youtube.com/watch?v=jmbuRzYPGrg |
| 456 | 132 Pattern | |
| 581 | Shortest Unsorted Continuous Subarray | https://www.youtube.com/watch?v=JKcX5k00oaA; https://www.youtube.com/watch?v=p-O7FExDH1M |
| 654 | Maximum Binary Tree | |
| 768 | Max Chunks To Make Sorted II | |
| 769 | Max Chunks To Make Sorted | |
| 853 | Car Fleet | |
| 907 | Sum of Subarray Minimums | https://www.youtube.com/watch?v=v0e8p9JCgRc |
| 962 | Maximum Width Ramp | |
| 975 | Odd Even Jump | |
| 1008 | Construct Binary Search Tree from Preorder Traversal | |
| 1019 | Next Greater Node In Linked List | |
| 1063 | Number of Valid Subarrays | |
| 1081 | Smallest Subsequence of Distinct Characters | |
| 1124 | Longest Well-Performing Interval | |
| 1130 | Minimum Cost Tree From Leaf Values | |
| 1475 | Final Prices With a Special Discount in a Shop | |
| 1504 | Count Submatrices With All Ones | |
| 1526 | Minimum Number of Increments on Subarrays to Form a Target Array | |
| 1574 | Shortest Subarray to be Removed to Make Array Sorted | |
| 1673 | Find the Most Competitive Subsequence | |
| 1762 | Buildings With an Ocean View | |
| 1776 | Car Fleet II | |
| 1793 | Maximum Score of a Good Subarray | |
| 1856 | Maximum Subarray Min-Product | |
| 1944 | Number of Visible People in a Queue | |
| 1950 | Maximum of Minimum Values in All Subarrays | |
| 1996 | The Number of Weak Characters in the Game | |
| 2030 | Smallest K-Length Subsequence With Occurrences of a Letter | |
| 2104 | Sum of Subarray Ranges | |
| 2281 | Sum of Total Strength of Wizards | |
| 2282 | Number of People That Can Be Seen in a Grid | |
| 2289 | Steps to Make Array Non-decreasing | |
| 2297 | Jump Game VIII | |
| 2334 | Subarray With Elements Greater Than Varying Threshold | |
| 2345 | Finding the Number of Visible Mountains | |
| 2355 | Maximum Number of Books You Can Take | |
| 2454 | Next Greater Element IV | |
| 2487 | Remove Nodes From Linked List | |
| 2617 | Minimum Number of Visited Cells in a Grid | |
| 2736 | Maximum Sum Queries | |
| 2818 | Apply Operations to Maximize Score | |
| 2832 | Maximal Range That Each Element Is Maximum in It | |
| 2863 | Maximum Length of Semi-Decreasing Subarrays | |
| 2865 | Beautiful Towers I | |
| 2866 | Beautiful Towers II | |
| 2940 | Find Building Where Alice and Bob Can Meet | |
| 2945 | Find Maximum Non-decreasing Array Length | |
| 3113 | Find the Number of Subarrays Where Boundary Elements Are Maximum | |
| 3205 | Maximum Array Hopping Score I | |
| 3221 | Maximum Array Hopping Score II | |
| 3229 | Minimum Operations to Make Array Equal to Target | |
| 3359 | Find Sorted Submatrices With Maximum Element at Most K | |
| 3420 | Count Non-Decreasing Subarrays After K Operations | |
| 3430 | Maximum and Minimum Sums of at Most Size K Subarrays | |
| 3523 | Make Array Non-decreasing | |
| 3542 | Minimum Operations to Convert All Elements to Zero | |
| 3555 | Smallest Subarray to Sort in Every Sliding Window | |
| 3638 | Maximum Balanced Shipments | |
| 3676 | Count Bowl Subarrays | |

## Categorized Monotonic Stack

| id | problem | comment / urls |
|----|---------|----------------|
|  | Next Greater Element / Next Smaller Element | Next Greater Node In Linked List; Final Prices With a Special Discount in a Shop (next smaller or equal); Number of Visible People in a Queue (next greater, but also count); Next Greater Element IV (next greater element but with two conditions) |
|  | Previous Greater Element / Previous Smaller Element | Buildings With an Ocean View (previous greater element, but from right to left); Number of People That Can Be Seen in a Grid (previous greater in two dimensions) |
|  | Span-like problems | Sum of Subarray Ranges (two stacks for min/max); Sum of Total Strength of Wizards (min and max in subarrays) |
|  | Left/right boundary problems | Sum of Subarray Minimums; Maximum Subarray Min-Product; Subarray With Elements Greater Than Varying Threshold; Find Sorted Submatrices With Maximum Element at Most K (2D) |
|  | Monotonic stack for subsequence | Find the Most Competitive Subsequence; Smallest Subsequence of Distinct Characters; Smallest K-Length Subsequence With Occurrences of a Letter |
|  | Complex uses (DP / two passes / simulation) | Odd Even Jump; Longest Well-Performing Interval; Minimum Cost Tree From Leaf Values; Minimum Number of Increments on Subarrays to Form a Target Array; Shortest Subarray to be Removed to Make Array Sorted; Car Fleet II; Maximum Score of a Good Subarray; Maximum of Minimum Values in All Subarrays; The Number of Weak Characters in the Game; Steps to Make Array Non-decreasing; Jump Game VIII; Finding the Number of Visible Mountains; Maximum Number of Books You Can Take; Remove Nodes From Linked List; Minimum Number of Visited Cells in a Grid; Maximum Sum Queries; Apply Operations to Maximize Score; Maximal Range That Each Element Is Maximum in It; Maximum Length of Semi-Decreasing Subarrays; Beautiful Towers I & II; Find Building Where Alice and Bob Can Meet; Find Maximum Non-decreasing Array Length; Find the Number of Subarrays Where Boundary Elements Are Maximum; Maximum Array Hopping Score I & II; Minimum Operations to Make Array Equal to Target; Count Non-Decreasing Subarrays After K Operations; Maximum and Minimum Sums of at Most Size K Subarrays; Make Array Non-decreasing; Minimum Operations to Convert All Elements to Zero; Smallest Subarray to Sort in Every Sliding Window; Maximum Balanced Shipments; Count Bowl Subarrays |

## Parentheses

| id | problem | comment / urls |
|----|---------|----------------|
|  | Valid Parentheses | |
|  | Longest Valid Parentheses | |
|  | Score of Parentheses | |
|  | Minimum Add to Make Parentheses Valid | |
|  | Valid Parenthesis String | |
|  | Remove Outermost Parentheses | |
|  | Maximum Nesting Depth of Two Valid Parentheses Strings | |
|  | Reverse Substrings Between Each Pair of Parentheses | |
|  | Minimum Remove to Make Valid Parentheses | |
|  | Minimum Insertions to Balance a Parentheses String | |
|  | Maximum Nesting Depth of the Parentheses | |
|  | Check if a Parentheses String Can Be Valid | |
|  | Ternary Expression Parser | |
|  | Parse Lisp Expression | |
|  | Parsing A Boolean Expression | |
|  | Minimum Cost to Change the Final Value of Expression | |
|  | The Score of Students Solving Math Expression | |
|  | Brace Expansion | |
|  | Brace Expansion II | |

## Binary Tree

| id | problem | comment / urls |
|----|---------|----------------|
|  | Binary Tree Inorder Traversal | |
|  | Flatten Binary Tree to Linked List | |
|  | Binary Tree Preorder Traversal | |
|  | Binary Tree Postorder Traversal | |
|  | Binary Search Tree Iterator | |
|  | Closest Binary Search Tree Value II | |
|  | Verify Preorder Serialization of a Binary Tree | |
|  | Convert Binary Search Tree to Sorted Doubly Linked List | |
|  | Construct Binary Tree from String | |
|  | N-ary Tree Preorder Traversal | |
|  | N-ary Tree Postorder Traversal | |
|  | Increasing Order Search Tree | |
|  | Binary Search Tree Iterator II | |
|  | Build Binary Expression Tree From Infix Expression | |
|  | Design an Expression Tree With Evaluate Function | |
|  | Is Array a Preorder of Some ‌Binary Tree | |
|  | Two Sum BSTs | |

## Basic Calculator

| id | problem | comment / urls |
|----|---------|----------------|
|  | Basic Calculator | |
|  | Basic Calculator II | |
|  | Basic Calculator III | |
|  | Basic Calculator IV | |

## Implementations

| id | problem | comment / urls |
|----|---------|----------------|
|  | Implement Stack using Array | |
|  | Implement Stack using List | |
|  | Implement Stack using Queues | |
|  | Implement Queue using Stacks | |
|  | Design a Middle Stack | |
|  | Min Stack | |
|  | Max Stack | |
|  | Design a Stack With Increment Operation | https://www.youtube.com/watch?v=-JzKnBKOxyM |
|  | Build an Array With Stack Operations | https://www.youtube.com/watch?v=nmNLu1Qz-C0&pp=ygUkQnVpbGQgYW4gQXJyYXkgV2l0aCBTdGFjayBPcGVyYXRpb25z |
|  | Design Video Sharing Platform | https://leetcode.ca/2022-05-26-2254-Design-Video-Sharing-Platform/ |
|  | Design a Text Editor | |
|  | Design Browser History | |
|  | Simplify Path | |
|  | Reorder List | |
|  | Evaluate Reverse Polish Notation | |

## Linked List

| id | problem | comment / urls |
|----|---------|----------------|
|  | Palindrome Linked List | |
|  | Flatten Nested List Iterator | |
|  | Nested List Weight Sum II | |
|  | Print Immutable Linked List in Reverse | |
|  | Maximum Twin Sum of a Linked List | |
|  | Double a Number Represented as a Linked List | |

## Misc / Strings / Others

| id | problem | comment / urls |
|----|---------|----------------|
|  | Remove All Adjacent Duplicates In String | |
|  | Remove All Adjacent Duplicates in String II | |
|  | Removing Stars From a String | |
|  | Validate Stack Sequences | |
|  | Asteroid Collision | |
|  | Mini Parser | |
|  | Longest Absolute File Path | |
|  | Decode String | |
|  | Backspace String Compare | |
|  | Decoded String at Index | |
|  | Make The String Great | |
|  | Add Two Numbers II | |
|  | Find Permutation | |
|  | Zuma Game | |
|  | Tag Validator | |
|  | Exclusive Time of Functions | |
|  | Baseball Game | |
|  | Maximum Frequency Stack | |
|  | Number of Atoms | |
|  | Stamping The Sequence | |
|  | Check If Word Is Valid After Substitutions | |
|  | Clumsy Factorial | |
|  | Dinner Plate Stacks | |
|  | Crawler Log Folder | |
|  | Minimum Deletions to Make String Balanced | |
|  | Number of Students Unable to Eat Lunch | |
|  | Maximum Score From Removing Substrings | |
|  | Remove All Occurrences of a Substring | |
|  | Minimum Number of Swaps to Make the String Balanced | |
|  | Reverse Prefix of Word | |
|  | Replace Non-Coprime Numbers in Array | |
|  | Count Collisions on a Road | |
|  | Minimum Deletions to Make Array Beautiful | |
|  | Construct Smallest Number From DI String | |
|  | Using a Robot to Print the Lexicographically Smallest String | |
|  | Maximum Frequency Score of a Subarray | |
|  | Minimum Time to Complete All Tasks | |
|  | Minimum Additions to Make Valid String | |
|  | Minimum String Length After Removing Substrings | |
|  | Robot Collisions | |
|  | Maximum Elegance of a K-Length Subsequence | |
|  | Lexicographically Minimum String After Removing Stars | |
|  | Clear Digits | |
|  | Find Mirror Score of a String | |
|  | Resulting String After Adjacent Removals | |
|  | Remove K-Balanced Substrings | |
