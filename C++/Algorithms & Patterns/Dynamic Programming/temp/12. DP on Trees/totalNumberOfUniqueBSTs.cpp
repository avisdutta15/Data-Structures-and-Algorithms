#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    How many structurally unique binary search trees(BSTs) are possible that store 'n' distinct values?

    If f(n) denotes the total number of BSTs for 'n' distinct keys then we can re-write f(n) as -

    f(n) = total number of BSTs with '1' as root + 
            total number of BSTs with '2' as root + ... + 
            total number of BSTs with 'n' as root
        = f(0)f(n-1) + f(1)f(n-2) + f(2)f(n-3) + ... + f(n-2)f(1) + f(n-1)f(0)

    why total number of BSTs with '1' as root = f(0)f(n-1)? Because the left subtree of 1 will have 0 nodes and right subtree will have n-1 nodes
    why total number of BSTs with '2' as root = f(1)f(n-2)? Because the left subtree of 2 will have 1 nodes and right subtree will have n-2 nodes

    For this recurrence relation, base cases are defined as f(0) = 1 and f(1) = 1, since number 
    of BSTs possible with 0 or 1 distinct keys is 1. Notice that many of the terms like f(n-1),
    f(n-2) in above equation are re-computed. In fact half of the terms in above equation would 
    be computed twice. To avoid these redundant computations, we store the computed values in 
    an array indexed by 'i' and re-use these if required.

*/

class Solution{
    public:        
        int totalNumberOfUniqueBSTs(int N){
            if(N<0)
                return 0;
            if(N==0 || N==1) //if N=0 then Bst = Null. Hence return 1
                return 1;

            int totalBSTs = 0;  //store the number of unique bsts possible for N
            for(int i=1; i<=N; i++){
                totalBSTs += totalNumberOfUniqueBSTs(i-1) * totalNumberOfUniqueBSTs(N-i);
            }
            return totalBSTs;             
        }

        //TopDown : Memoization
        int totalNumberOfUniqueBSTsUtil(vector<int> &lookup, int N){
            if(N<0)
                return 0;
            if(N==0 || N==1)
                return 1;

            int totalBSTs = 0;  //store the number of unique bsts possible for N
            for(int i=1; i<=N; i++){
                if(lookup[i-1] == -1)
                    lookup[i-1] = totalNumberOfUniqueBSTsUtil(lookup, i-1);
                if(lookup[N-i] == -1)
                    lookup[N-i] = totalNumberOfUniqueBSTsUtil(lookup, N-i);
                totalBSTs += (lookup[i-1] * lookup[N-i]);
            }
            return totalBSTs;             
        }

        int totalNumberOfUniqueBSTs(int N){
            vector<int> lookup(N+1, -1);   //why N+1? for N=0
            return totalNumberOfUniqueBSTsUtil(lookup, N);
        }
};


int main(){
    Solution obj;
}