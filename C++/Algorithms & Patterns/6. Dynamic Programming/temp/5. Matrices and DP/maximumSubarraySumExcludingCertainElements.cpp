#include <bits/stdc++.h>
using namespace std;

/*
    Given an array of A of n integers and an array B of m integers find the Maximum Contiguous Subarray Sum of 
    array A such that any element of array B is not present in that subarray.

    Input : A = {1, 7, -10, 6, 2}, B = {5, 6, 7, 1}
    Output : 2
    Explanation Since the Maximum Sum Subarray of A is not allowed to have any element that is present in array B.
    The Maximum Sum Subarray satisfying this is {2} as the only allowed subarrays are:{-10} and {2}. 
    The Maximum Sum Subarray being {2} which sums to 2

    Input : A = {3, 4, 5, -4, 6}, B = {1, 8, 5}
    Output : 7

    Explanation
    The Maximum Sum Subarray satisfying this is {3, 4} as the only allowed subarrays are {3}, {4}, {3, 4}, {-4}, {6}, {-4, 6}. 
    The Maximum Sum subarray being {3, 4} which sums to 7


*/


class Solution{
    public:
        void MaximumSumSubarray(vector<int> A, vector<int> B){
            unordered_set<int> lookup(B.begin(), B.end());

            int max_so_far = INT_MIN;
            int max_ending_here = INT_MIN;
            int beg = 0, start=0, end=0;
            
            for(int i=0; i<A.size(); i++){
                //if the current element is present in B then 
                //mark the end as i-1 and make the max_ending_here = 0 for the next batch
                //make beg = i+1 for the next batch
                if(lookup.find(A[i]) != lookup.end()){
                    end = i-1;
                    max_ending_here = 0;
                    beg = i+1;
                }

                else{
                    max_ending_here = max_ending_here + A[i];
                    if(max_ending_here<A[i]){
                        max_ending_here = A[i];
                        beg = i;
                    }
                    if(max_so_far<max_ending_here){
                        start = beg;
                        end = i;
                        max_so_far = max_ending_here;
                    }
                }
            }
            for(int i=start; i<=end; i++)
                cout<<A[i]<<" ";
        }
};

int main(){
    Solution obj;
    vector<int> A = {3, 4, 5, -4, 6};
    vector<int> B = {1, 8, 5};

    obj.MaximumSumSubarray(A, B);
}