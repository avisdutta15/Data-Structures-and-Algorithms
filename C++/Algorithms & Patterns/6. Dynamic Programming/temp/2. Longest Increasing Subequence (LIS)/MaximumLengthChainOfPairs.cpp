#include <bits/stdc++.h>
using namespace std;

/*
    Maximum Length Chain of Pairs 

    You are given n pairs of numbers. In every pair, the first number is always smaller 
    than the second number. A pair (c, d) can follow another pair (a, b) if b < c. 
    Chain of pairs can be formed in this fashion. Find the longest chain which can be 
    formed from a given set of pairs.


    For example, if the given pairs are {{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90} }, 
    then the longest chain that can be formed is of length 3, and the chain is 
    {{5, 24}, {27, 40}, {50, 90}}

    Approach:
    This problem is a variation of standard Longest Increasing Subsequence problem. 
    Following is a simple two step process.
    1) Sort given pairs in increasing order of first (or smaller) element.
    2) Now run a modified LIS process where we compare the second element of already 
    finalized LIS with the first element of new LIS being constructed.

    Input:  (5, 24), (39, 60), (15, 28), (27, 40), (50, 90)
    Output: (5, 24), (27, 40), (50, 90)

*/

struct Pair{ 
    public: 
    int a;  
    int b;  
};

int maxChainLength(vector<Pair>arr){  

    sort(arr.begin(), arr.end(), [](Pair p1, Pair p2)->bool{
        return p1.a<p2.a;
    });

    vector<int> mcl(arr.size(), 1);
    int maxLength = INT_MIN;    
    
    /* Compute optimized chain length values in bottom up manner */
    for (int i = 1; i <arr.size(); i++ ){  
        for (int j = 0; j < i; j++ ){  
            if (arr[i].a > arr[j].b && mcl[i] < mcl[j] + 1)  
                mcl[i] = mcl[j] + 1; 
            maxLength = max(maxLength, mcl[i]);
        }
    } 
    
    return maxLength;  
}  
int main(){
    vector<Pair> pairs = {{5, 24}, {15, 25}, {27, 40}, {50, 60}};
    cout<<maxChainLength(pairs);
}