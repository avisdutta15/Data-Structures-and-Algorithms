##  Pattern 1 : The Merge (Sort by Start Time)
These problems give you a static list (or simple arrays) and ask you to combine, group, or evaluate overlaps based on when things begin.

| Id | Problem | Comment / Urls |
|----|---------|----------------|
|1. |[Merge Intervals](./2.%20MergeIntervals.cpp)|![](./assets/1.%20MergeOverlappingIntervals.png)|
|2. |[Insert Interval](./3.%20InsertInterval.cpp)|![](./assets/2.%20InsertInterval.png)|
|3. |[Meeting Rooms](./4.%20MeetingRooms.cpp)|Simple overlap check|
|4. |Teemo Attacking (Merging overlapping poison durations)||
|5. |Add Bold Tag in String (Merge overlapping bold ranges before modifying the string)||
|6. |Partition Labels (Expand your interval based on the last occurrence of a character)||
|7. |Determine if Two Events Have Conflict||
|8. |Count Ways to Group Overlapping Ranges (Merge into disjoint groups, then do the math)||
|9. |Points That Intersect With Cars (Merge car footprints to count unique points)||
|10.| Count Days Without Meetings (Merge all meetings, subtract from total days)||
|11.| Minimize Connected Groups by Inserting Interval (Merge existing, see how the new one bridges gaps)||

##  Pattern 2 : Two-Pointer Intersection
These problems involve comparing distinct sets of intervals to find common ground.

| Id | Problem | Comment / Urls |
|----|---------|----------------|
|1. |Find Intersection of all Intervals||
|2. |Interval List Intersections||

##  Pattern 3 : Sweep Line & Priority Queues (Chronological Events)
These problems ask for peak concurrency, tracking active states, or distributing resources over time. 
You split the intervals into +1 (start) and -1 (end) events, or use a Min-Heap to track when resources free up.

| Id | Problem | Comment / Urls |
|----|---------|----------------|
|1. |Meeting Rooms II (Peak concurrency)||
|2. |Meeting Rooms III (Requires a Min-Heap to simulate room availability)||
|3. |Minimum number of platforms required (Exact same logic as Meeting Rooms II)||
|4. |Employee Free Time (Sweep line across all employee schedules to find the gaps)||
|5. |Divide Intervals Into Minimum Number of Groups (Another variation of Meeting Rooms II)||
|6. |My Calendar II (Track if sweep line ever hits 3 concurrent events)||
|7. |My Calendar III (Track the absolute maximum of the sweep line)||

##  Pattern 4 : The Greedy Choice (Sort by End Time)
These problems are about maximizing throughput or minimizing conflicts. You must ruthlessly pick the intervals that end the earliest to leave room for the rest.

| Id | Problem | Comment / Urls |
|----|---------|----------------|
|1. |N Meeting in One Room (Maximize meetings)||
|2. |Non-overlapping intervals (Minimize removals)||

##  The "Hidden" Staff-Level Pattern 5 : Dynamic Intervals
This is where the standard O(N log N) sorting trick breaks down. 
In these problems, you are not given the intervals all at once. They arrive as a data stream, or you must perform frequent updates and queries.
At the Staff level, you must recognize when to abandon static arrays and use a TreeMap (Balanced BST) or a Segment Tree.

| Id | Problem | Comment / Urls |
|----|---------|----------------|
|1. |Data Stream as Disjoint Intervals (Use a TreeMap to efficiently find the floor/ceiling of incoming numbers and merge dynamically)||
|2. |Range Module (Heavy use of TreeMap to track, add, and remove massive ranges dynamically)||
|3. |Amount of New Area Painted Each Day (Segment Tree or Sweep Line with a TreeSet)||
|4. |Longest Substring of One Repeating Character (Segment Tree to track merged character intervals upon updates)||
|5. |Count Integers in Intervals (Dynamic merging, best handled with a TreeMap or Segment Tree)||
|6. |My Calendar I (Can be done with an array, but the optimal dynamic solution is a TreeMap)||

(Note: Problem 11. Find Right Interval is a slight outlier. It involves sorting by start time, but then using Binary Search to quickly find the next valid interval. It bridges Pattern 1 and standard searching.)





------------------------------------------------------------------------
Interval related problems:

	Tips:
	1. Sort the intervals based on start time
	2. check if two intervals overlap
	   So if two intervals Ia=[a0,a1] and Ib=[b0,b1] don’t overlap, that means 
	   that Ib must be either fully to the left or fully to the right of Ia on 
	   the real number line. Now, if Ib is fully to the left of Ia, that means 
	   in particular that b’s rightmost point b1 must be to the left of a – that 
	   is, smaller than a0. And again, vice versa for the right side. So the two
	   intervals don’t overlap if either b1 < a0 or a1 < b0 
	
 	   bool overlap(Interval a, Interval b){
		if(a.end<b.start || b.end<a.start)
		   return false;
		return true;
	   }
	3. To merge 2 overlapping intervals, we want the minimum start time among the 
	   two intervals and the minimum end time among the two intervals.

	4. Suppose our intervals are not sorted. Then how to tell if two intervals
	   overlap or not?
			
		bool overlap(Interval i1, Interval i2){
			if(max(i1.start, i2.start) <= min(i1.end, i2.end))
				return true;
			return false;
		}

<code>
b:                     |---------| <br/>
a0<b0 & a1<b0:  |----| <br/>
a0<b0 & a1>b0:  |------------| (a started within b) <br/>
a0<b0 & a1>b1:  |-------------------| (a started within b) <br/>
a0>b0 & a0<b1:            |----|  (b started within a) <br/>
a0>b0 & a0>b1:            |---------| (b started within a) <br/>
a0>b1 & a1>b1:                      |----| <br/>
</code>