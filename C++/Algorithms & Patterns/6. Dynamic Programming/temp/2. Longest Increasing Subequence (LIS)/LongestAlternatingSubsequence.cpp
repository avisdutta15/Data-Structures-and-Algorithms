#include <bits/stdc++.h>
using namespace std;

/*
  A sequence {x1, x2, .. xn} is alternating sequence if its elements satisfy one of the following relations :

  x1 < x2 > x3 < x4 > x5 < …. xn or 
  x1 > x2 < x3 > x4 < x5 > …. xn 
  
    Input: arr[] = {1, 5, 4}
    Output: 3
    The whole arrays is of the form  x1 < x2 > x3 
    
    Input: arr[] = {1, 4, 5}
    Output: 2
    All subsequences of length 2 are either of the form 
    x1 < x2; or x1 > x2
    
    Input: arr[] = {10, 22, 9, 33, 49, 50, 31, 60}
    Output: 6
    The subsequences {10, 22, 9, 33, 31, 60} or
    {10, 22, 9, 49, 31, 60} or {10, 22, 9, 50, 31, 60}
    are longest subsequence of length 6.
    
    Solution:
    Approach is done using LIS concept.
    At each A[i] we check if we want a smaller element from start or greater element.
    This decision is done by a flag.
*/

class Solution{
    public:
        int longestAlternatingSubsequence(vector<int> A){
            int n = A.size();
            if(n==0)
                return 0;
            
            //Create a DP array to store the LAS value ending at A[i].
            //DP[i] denotes the LAS ending at element A[i].
            int DP[n] = {1};

            DP[0] = 1;
            
            //Set a flag to alter the switch. It helps us to decide whether we want 
            //a smaller or greater element than the current element.
            string flag;
            if(A[1]>A[0]) //if 2nd element is > 1st element then we want a smaller element for A[1]
                flag = "min";
            else          //if 2nd element is < 1st element then we want a greater element for A[1]
                flag = "max";
                
            for(int i=1; i<n; i++){
                for(int j=0; j<i; j++){
                    
                    //if flag == min it means we are searching for a element less than A[i]
                    if(flag=="min" && A[j] < A[i]){
                        DP[i] = max(DP[j]+1, DP[i]);
                    }
                    //if flag == max it means we are searching for a element greater than A[i]
                    else if(flag == "max" && A[j] > A[i]){
                        DP[i] = max(DP[j]+1, DP[i]);
                    }
                }
                
                //Switch the flag
                if(flag=="min")
                    flag = "max";
                else    
                    flag = "min";
            }
            
            return *max_element(DP, DP+n);
        }
};

int main(){
    Solution obj;
    vector<int> A = {8, 9, 6, 4, 5, 7, 3, 2, 4};
    //vector<int> A = {1, 5, 4};
    //vector<int> A = {1, 4, 5};
    //vector<int> A = {1, 2};
    cout<<obj.longestAlternatingSubsequence(A);

    return 0;
}