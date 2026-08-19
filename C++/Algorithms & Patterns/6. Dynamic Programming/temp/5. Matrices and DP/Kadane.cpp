#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    -----------------
    Write an efficient program to find the sum of contiguous subarray within a one-dimensional array of 
    numbers which has the largest sum.

*/

/*
    Approach:
    --------
    Kadane's Algorithm:
    At an index i, we have 2 options.
        1)  extend the maximum sum till now  including this element
        2)  start a new subarry from this element
        maximumSumTillNow = max(maximumSumTillNow+A[i], A[i]);
        globalMaximumSum  = max(globalMaximumSum, maximumSumTillNow)

        -2   1  -3   4  -1   2   1   -5   4
temp[]  -2   1  -2   4   3   5   6    1   5
        
        globalMaximumSum = 6
*/

class Solution
{
    public:
        void print_Kadane(vector<int> A){
            int max_ending_here = A[0];
            int max_so_far = A[0];

            // stores end-points of maximum sum subarray found so far
            int start=0, end=0;

            // stores starting index of a positive sum sequence
            int max_ending_here_beginning = 0;

            for(int i=1; i<A.size(); i++){
                max_ending_here = max_ending_here + A[i];
               
                if(max_ending_here < A[i]){
                    max_ending_here = A[i];
                    max_ending_here_beginning = i;
                }

                if(max_so_far < max_ending_here){
                    max_so_far = max_ending_here;
                    start = max_ending_here_beginning;
                    end = i;
                }
            }

            cout<<"Maximum Sum of subarry: "<<max_so_far<<endl;
            cout<<"Subarray with max sum is: "<<endl;
            for(int i=start; i<=end; i++)
                cout<<A[i]<<" ";
        }
};

int main(){
    Solution obj;    
    vector<int> A = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    obj.print_Kadane(A);
    
    cout<<endl;

    A = {-2, -1, -3, -4, -1, -2, -1, -5, -4};
    obj.print_Kadane(A);
    
    return 0;
}


/*
    Follow up:
    Maximum subarray sum in an array created after repeated concatenation

    Given an array and a number k, find the largest sum of contiguous array 
    in the modified array which is formed by repeating the given array k times.

    Appraoch1 : Concatenate the array K times and then apply Kadane
    TC: O(n*k)
    SC: O(n*k)

    Approach2 : Use Modular approach and apply Kadane
    for(int i=0; i<n*k; i++)
        num = A[i%n];

    TC : O(n*k)
    SC : O(n)
*/