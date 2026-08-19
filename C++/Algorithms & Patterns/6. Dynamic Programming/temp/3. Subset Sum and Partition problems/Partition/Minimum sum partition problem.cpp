#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
        int minPartitionUtil(vector<int> A, int n, int S1, int S2, bool *includeInSet1)
        {
        	// base case: if list becomes empty, return the absolute
        	// difference between two sets
        	if (n < 0)
        		return abs(S1 - S2);
        
        	// Case 1. include current item in the subset S1 and recurse
        	// for remaining items (n - 1)
        	includeInSet1[n] = true;
        	int include = minPartitionUtil(A, n - 1, S1 + A[n], S2, includeInSet1);
        
        	// Case 2. exclude current item from subset S1 and recurse for
        	// remaining items (n - 1)
        	includeInSet1[n] = false;
        	int exclude = minPartitionUtil(A, n - 1, S1, S2 + A[n], includeInSet1);
            
			/*if the sum obtained by including the current element is less than 
			  the sum obtained by excluding it then make includeInSet1[n] as true*/
            if(include<exclude)
                includeInSet1[n] = true;
        	return min (include, exclude);
        }

		int minPartition(vector<int> A){
			int n = A.size();

			//if includeInSet1[i] == true it means A[i] is included in set1.
			//if includeInSet1[i] == false it means A[i] is included in set2.
			bool includeInSet1[n] = {false};
			int S1 = 0; //sum of set1
			int S2 = 0; //sum of set2

			int midDiff = minPartitionUtil(A, n - 1, S1, S2, includeInSet1);

			cout << "The minimum difference is: " <<midDiff<<endl;

			cout<<"Set A: ";
			for(int i=0; i<n; i++){
				if(includeInSet1[i]==true)
					cout<<A[i]<<" ";
			}
			
			cout<<endl;
			cout<<"Set B: ";
			for(int i=0; i<n; i++){
				if(includeInSet1[i]==false)
					cout<<A[i]<<" ";
			}
		}

		int minPartitionTopDownUtil(vector<int> A, int n, int S1, int S2, bool *includeInSet1, unordered_map<string, int> lookup){
			if(n==0){
				return abs(S1-S2);
			}
	
			// construct a unique map key from dynamic elements of the input
			// Note that key can uniquely identify the sub-problem with n and S1 only,
			// as S2 is nothing but S - S1 where S is sum of all elements
			string key = to_string(n) + "|" + to_string(S1);

			if(lookup.find(key)==lookup.end()){

				includeInSet1[n] = true;
				int include = minPartitionTopDownUtil(A, n-1, S1+A[n], S2, includeInSet1, lookup);

				includeInSet1[n] = false;
				int exclude = minPartitionTopDownUtil(A, n-1, S1, S2+A[n], includeInSet1, lookup);

				if(include<exclude)
					includeInSet1[n] = true;
				lookup[key] = min(include, exclude);
			}

			return lookup[key];
		}

		void minPartitionTopDown(vector<int> A){
			int n = A.size();
			bool includeInSet1[n] = {false};
			int S1 = 0; //sum of set1
			int S2 = 0; //sum of set2
			unordered_map<string, int> lookup;

			int midDiff = minPartitionTopDownUtil(A, n - 1, S1, S2, includeInSet1, lookup);

			cout << "The minimum difference is: " <<midDiff<<endl;

			cout<<"Set A: ";
			for(int i=0; i<n; i++){
				if(includeInSet1[i]==true)
					cout<<A[i]<<" ";
			}
			
			cout<<endl;
			cout<<"Set B: ";
			for(int i=0; i<n; i++){
				if(includeInSet1[i]==false)
					cout<<A[i]<<" ";
			}
		}

		/*
			Approach:
			The problem can be solved in a similar fashion as the subset sum.
			How??
			Construct a 2D array of [N+1][Sum+1] where sum is the sum of all the elements of the given set
			Now, keep this in mind: 
				Sum of set1 is x and 
				therefore sum of set2 is (totalSum-x) and 
				therefore difference of sets is (totalSum-x) - (x) i.e. totalSum-2*x.

			So to get the minimum difference, we have to adjust the x such that the final diff is small.
			So x can range from 0 to totalSum/2 ==>  0<= x <=totalSum/2
		*/

		int minPartitionBottomUp(vector<int> A){
			int totalSum = accumulate(A.begin(), A.end(), 0);
			int n = A.size();

			int lookup[n+1][totalSum+1] = {0};

			for(int i=1; i<=n; i++){
				lookup[i][0] = 1; //we can make a sum 0 by not including element A[i]
			}

			for(int sum=1; sum<=totalSum; sum++){
				lookup[0][sum] = 0; // an empty set cannot make the sum 'sum'
			}

			lookup[0][0] = 1;

			for(int i=1; i<=n; i++){
				for(int sum=1; sum<=totalSum; sum++){
					//Access the array element as A[i-1]
					if(A[i-1]>sum)
						lookup[i][sum] = lookup[i-1][sum];
					else{
						int include = lookup[i-1][sum-A[i-1]];
						int exclude = lookup[i-1][sum];
						lookup[i][sum] = include || exclude;
					}
				}
			}

			int targetSum = 0;
			int diff = INT_MIN;
			for(int sum = totalSum/2; sum>=0; sum--){
				if(lookup[n][sum]==1){
					targetSum = sum;
					diff = abs(totalSum - 2*sum); //difference between 2 sets
					break;
				}
			}

			cout<<"The difference between 2 sets are: "<<diff;
			
			//How to print the sets??
			
		}
};

// main function
int main()
{
	// Input: set of items
	vector<int> A = { 10, 20, 15, 5, 25};

	// number of items
	
    Solution obj;
	obj.minPartition(A);
	cout<<endl;
	
	obj.minPartitionTopDown(A);
	cout<<endl;

	obj.minPartitionBottomUp(A);

	return 0;
}