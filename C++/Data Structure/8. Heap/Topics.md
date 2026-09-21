priority_queue Basics:
----------------------
1. by default, priority_queue is max heap.
2. for min heap
	priority_queue<int, vector<int>, greater<int> > Q;

3. writing a custom comparator for min heap
	class comp{
		public:
			bool operator()(int a, int b){
				return (a>b);
			}
	}
	
	priority_queue<int, vector<int>, comp> pq;

4. Note: we donot use comp() in priority_queue as we use in sort
         we reverse the logic for min heap a>b as compared to sort. For sorting in ascending order, we used a<b.

5. using lambda function in priority queue
	
	    auto cmp = [](pair<int, pair<int,int>> &a, pair<int, pair<int,int>> &b){
                            return a.first > b.first;
                       };
            priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, decltype(cmp)> minHeap(cmp);

6. Root is at index 0 (i).
   left child = 2*(i) + 1
   right child = 2*(i) + 2
   parent = (i-1)/2
   firstInternalNode = (heapSize-1)/2
