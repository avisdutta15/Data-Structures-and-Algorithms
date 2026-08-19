#include <bits/stdc++.h>
using namespace std;

/*
    The approach is interesting! How to identify if the A[i] and A[j] are of opposite nature?
    i.e. one of them is odd and the other is even?
    Remember: odd + even = odd.
    So check if A[i]+A[j] is odd.

*/

class Solution{
    public:
        int longestOddEvenSequence(vector<int> A){
            int n = A.size();
            if(n==0)
                return 0;
            int DP[n] = {1};
            
            for(int i=1; i<n; i++){
                for(int j=0; j<i; j++){
                    if(A[j]<A[i] && (A[i]+A[j])%2==1)
                        DP[i] = max(DP[j]+1, DP[i]);
                }
            }

            return *max_element(DP, DP+n);
        }
};

int main(){
    Solution obj;
    //vector<int> A = {5, 6, 9, 4, 7, 8};
    vector<int> A = {1, 12, 2, 22, 5, 30, 31, 14, 17, 11};
    cout<<obj.longestOddEvenSequence(A);
    return 0;
}