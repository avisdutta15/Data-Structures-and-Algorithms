| Id | Problem | Comment / Urls |
| --- | --- | --- |
|1|Find all intervals that overlap||
|2|Merge Intervals||
|3|Insert Interval||
|4|Meeting Rooms||
|5|Meeting Rooms II||
|6|Meeting Rooms III  |[TODO]|
|7|N Meeting in One Room |If a meeting ends early, the room becomes available sooner, allowing more meetings to fit in. <br/> By always picking the meeting with the smallest finishing time that does not overlap with previously chosen meetings, we maximize the number of scheduled meetings.|
|8|Minimum number of platforms required ||
|9|Find Intersection of all Intervals||
|10|Non overlapping intervals ||
|11|Find Right Interval||
|12|Interval List Intersections||
|13|Data Stream as Disjoint Intervals ||
|14|Teemo Attacking ||
|15|Add Bold Tag in String ||
|16|Range Module ||
|17|Employee Free Time (Own Solution + algomonster) ||
|18|Partition Labels ||
|19|Amount of New Area Painted Each Day ||
|20|Longest Substring of One Repeating Character ||
|21|Count Integers in Intervals ||
|22|Divide Intervals Into Minimum Number of Groups ||
|23|Determine if Two Events Have Conflict ||
|24|Count Ways to Group Overlapping Ranges ||
|25|Points That Intersect With Cars ||
|26|Count Days Without Meetings ||
|27|Minimize Connected Groups by Inserting Interval ||
|28|My Calender I	||
|29|My Calender II |(https://www.youtube.com/watch?v=rRMdxFA-8G4&t=212s)|
|30|My Calender III  ||





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