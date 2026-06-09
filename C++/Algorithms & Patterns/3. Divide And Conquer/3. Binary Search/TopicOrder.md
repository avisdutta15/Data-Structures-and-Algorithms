1. Binary Search
2. Find First and Last Occurance
3. Count the numbers of ones in a sorted binary array.
4. Find Floor and Ceil Of an element
	Floor - Largest element SMALLER than or equal to x
	Ceil  - Smallest element LARGER than or equal to x
5. Peak Element
   ```cpp
	while(lo <= hi){
        mid = lo + (hi - lo)/2;
        
        //edge case: mid came to first element then it is preak if it is greater than next
        if(mid == 0 && A[mid]>=A[mid+1])
            return 0;
        //edge case: mid came to last element then it is peak if it is greater than prev
        if(mid == N-1 && A[mid-1]<=A[mid])
            return N-1;
            
        //normal case: check if mid is greater than neighbours
        if(A[mid-1]<=A[mid] && A[mid]>=A[mid+1])
            return mid;
        
        //mid-1 cannot be a candidate if it is lesser than mid so go to right side
        if(A[mid-1]<=A[mid]) lo = mid+1;
        else hi = mid-1;
    }
   ```
7. Find bitonic point in given bitonic sequence
	It is same as finding a peak element.

8. Find the element that appears once in a sorted array. Others appears twice.
	All elements before the required have first occurrence at even index (0, 2, ..) 
	and next occurrence at odd index (1, 3, �). And all elements after the required 
	element have first occurrence at odd index and next occurrence at even index.
```cpp
	If �mid� is even, then compare arr[mid] and arr[mid + 1]. If both are same, then the required element after �mid� else before mid.
	If �mid� is odd, then compare arr[mid] and arr[mid � 1]. If both are same, then the required element after �mid� else before mid.
```

Finding minimum vertex cover size of a graph using binary search [TODO]
Square root and cubic root of an integer. 
	
Peak element in 2D array. 
https://abirbhushan.com/blog/2019/07/12/Two-dimensional-Peak-finding-problem/
http://kamalmeet.com/algorithms/finding-a-peak-in-2-dimensional-array/
For each element in 1st array count elements less than or equal to it in 2nd array.
	Sort arr2. 
	For every element x of arr1, find the last index of the largest element less than x in arr2.
Find a Fixed point with duplicates allowed
Binary Search on Singly Linked List
Find closest element to a given number x
	1. Do a binary search.
    2. For every mid check the difference between A[mid] and key. 
       If the difference is smaller than already seen then update the closestElement to A[mid]
    3. Go to left if A[mid]>key
       else goto right
Find K closest elements to a given number x 
	Find the index of the number x in the sorted array. (Even if x is not present, find the index where it should have been)
	From there, go in left and right direction to find the elements.
First bad version.
Given two sorted arrays one having 1 element extra, find the index of the extra element

Rotations
---------
1. Search in a sorted rotated array
```cpp
	mid = [left+right]/2;
	if(A[mid]==x)	return mid;
	if(A[left]<=A[mid]) {			//if left half is sorted
		if(A[left]<=x and x<=A[mid])	//if x lies in left then goto left
			right = mid-1
		else				
			left = mid+1				//else goto right
	}else if(A[mid+1]<=A[high]) {	//else right half is sorted
		if(A[mid+1]<=x and x<=A[right])	//if x lies in right then goto right
			left = mid+1
		else				
			right= mid-1				//else goto left
	}
```
3. Search in a sorted rotated array II (array contains duplicates)
```cpp
	mid = [left+right]/2;
	if(A[mid]==x)	
		return mid;
	if(A[left]==A[right])			//Case 4 4 1 2 4 4 where lo = 4 and mid = 1 and hi = 4
		left++; right--;			//shrink the window
	else if(A[left]<=A[mid]) {
		if(A[left]<=x and x<=A[mid])	
			right = mid-1
		else				
			left = mid+1
	}else if(A[mid+1]<=A[high]) {
		if(A[mid+1]<=x and x<=A[right])	
			left = mid+1
		else				
			right= mid-1
	}
```
5. Minimum element in sorted rotated array. 	Approach: Always store the minimum of the sorted side and goto opposite side.
```cpp
	while (lo <= hi) {
        int mid = lo + (hi - lo)/2;
        
        if(A[lo] <= A[mid]){			//if A[lo...mid] is sorted then store the smallest and goto right side.
            ans = min(ans, A[lo]);		//smallest can be ans or A[lo]
            lo  = mid + 1;
        }else{
            ans = min(ans, A[mid]);		//if A[mid...hi] is sorted then store the smallest and goto left side.
            hi  = mid - 1;				//smallest can be ans or A[mid]... Why A[mid]  4 5 [1 2 3]  here, 1, 2, 3 is sorted. min is 1.
        }
    }
```
7. Minimum element in sorted rotated array with duplicates
	SAME AS ABOVE
8. Find the Rotation Count in Rotated Sorted array (number of rotations is equal to index of minimum element)
	SAME AS ABOVE
9. Find bitonic point in a given bitonic sequence

Count elements less than or equal to a given value in a sorted rotated array.
	Given a sorted rotated array, find the index of minimum element.
	This helps to divide the array into 2 parts, A[0]....max_element, min_element....A[n-1]
	Now search for the index of the maximum element which is smaller than x in the range A[min_element]...A[n-1].
	Count =  index1 + 1 � min_index.
	Search for the index of the maximum element which is smaller than x in the range A[0]...A[max_element].
	Count =  index2 + 1 � min_index.
	Note check if the rotation count is 0. (if A[0] == A[min_element] then rotation count is 0 so no need to search in 2nd condition.)
	If x>max_element then count = n

Check whether an array is k sorted.
	Sort the array and store it in a aux array.
	For each element at index i in arr, find the index of that element in aux. Let the index be j.
	If for any element abs(i-j) > K then it is not a K sorted array.
	

TODO: Page 1-5 in Binary Search Tag

------------------------------------------------------------C++ STL Binary Search--------------------------------------
bool binary_search(A.begin(), A.end(), key) - returns true or false

lower_bound - first equal to or greater than
	A = {1, 4, 5, 6, 9, 9}
	int indx = lower_bound(A.begin(), A.end(), 4)  -  A.begin();   //1
	int indx = lower_bound(A.begin(), A.end(), 7)  -  A.begin();   //4
	int indx = lower_bound(A.begin(), A.end(), 10) -  A.begin();   //6
	index is 0 based index
```cpp
	int lower_bound(vector<int> A, int x){
    		int lo = 0;
		int hi = A.size()-1;
		int ans = A.size(); //Why? because the actual lower_bound returns a.size() if x is greater than the last element
    
    		while(lo <= hi){
		        int mid = lo + (hi-lo)/2;    
		        if(A[mid] == x){  //if A[mid] == x then save this index and goto left side
		            ans = mid;
		            hi  = mid - 1;
	        	}
	        	else if(x < A[mid]){ //if x is smaller than A[mid] then save this index and goto left side
		            ans = mid;
		            hi  = mid - 1;
        		}
	        	else{		     //else goto right side
	        	    lo = mid + 1;
        		}
		}
    		return ans;
	}
```

upper bound - first greater than
	A = {1, 4, 5, 6, 9, 9}
	int indx = upper_bound(A.begin(), A.end(), 4)  -  A.begin();   //2
	int indx = upper_bound(A.begin(), A.end(), 7)  -  A.begin();   //4
	int indx = upper_bound(A.begin(), A.end(), 10) -  A.begin();   //6
	index is 0 based index
```cpp
	int upper_bound(vector<int> A, int x){
    		int lo = 0;
		int hi = A.size()-1;
    		int ans = A.size();  //Why? because the actual upper_bound returns a.size() if x is greater than the last element
    
    		while(lo <= hi){
		        int mid = lo + (hi-lo)/2;    
	 	        if(A[mid] == x){
            			hi  = mid - 1;
		        }
		        else if(x < A[mid]){	//if x is smaller than A[mid] then save this index and goto left side
		            ans = mid;
		            hi = mid - 1;
		        }
		        else{
		            lo = mid + 1;            
		        }
	        }
    		return ans;
	  }
```
lower_bound : first equal to or greater than
upper bound - first greater than
Floor : Given a sorted array and a value x, the floor of x is the largest element in array smaller than or equal to x.
Ceil  : Given a sorted array and a value x, the ceiling of x is the smallest element in array greater than or equal to x.

---------------------------------------------------------------------------------------------------

Problems on upper_bound and lower_bound
1. Find the first occurrence of X in a sorted array. If it does not occur then print -1
	A = {1, 4, 5, 6, 9, 9}
	X = 9
	X = 2
	X = 12
```cpp
	int firstOccurence(A, X):
		int index = lower_bound(A.begin(), A.end(), X) - A.begin();
		if(index == A.size() || A[index]!=X)
			return -1;
		return index;
```
3. Find the last occurrence of X in a sorted array. If it does not occur then print -1
	A = {1, 4, 5, 6, 9, 9}
	X = 9
	X = 2
	X = 0
```cpp
	int lastOccurence(A, X):
		int index = upper_bound(A.begin(), A.end(), X) - A.begin();
		index--;
		if(index == -1 || A[index]!=X)
			return -1;
		return index;
```
5. Find the largest number smaller than X in a sorted array. If it does not occur then print -1
	A = {1, 4, 5, 6, 9, 9}
	X = 9
	X = 2
	X = 0
```cpp
	int largestNumberSmallerThan(A, X):
		int index = lower_bound(A.begin(), A.end(), X) - A.begin();
		index--;
		if(index == -1)
			return -1;
		return index;
```

---------------------------------------------------------------------------------------------------
PROBLEMS RELATED TO VALUE SEARCH SPACE:
https://leetcode.com/discuss/general-discussion/691825/Binary-Search-for-Beginners-Problems-or-Patterns-or-Sample-solutions
	1. Book Allocation
	2. Split Array Largest Sum
	3. Kth Smallest number in sorted matrix
	4. Kth Smallest number in multiplication table
	5. Kth Smallest absolute difference
	6. Maximum subarray size, such that all subarrays of that size have sum less than k 
	7. Longest subarray having average greater than or equal to x

https://www.youtube.com/watch?v=YTTdLgyqOLY
https://dilipkumar.medium.com/binary-search-pattern-c9402d045722
