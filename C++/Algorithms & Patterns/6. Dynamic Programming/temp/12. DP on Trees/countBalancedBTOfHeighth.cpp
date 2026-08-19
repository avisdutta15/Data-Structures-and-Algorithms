#include <bits/stdc++.h>
using namespace std;

/*
    Count Balanced Binary Trees of Height h
    ---------------------------------------
    Height of tree, h = 1 + max(left height, right height)
    Since the difference between the heights of left and right 
    subtree is not more than one, possible heights of left and 
    right part can be one of the following:

    (h-1), (h-2)
    (h-2), (h-1)
    (h-1), (h-1)

    count(h) =  count(h-1) * count(h-2) + 
                count(h-2) * count(h-1) + 
                count(h-1) * count(h-1)
             =  2 * count(h-1) * count(h-2) +  count(h-1) * count(h-1)
             =  count(h-1) * (2*count(h - 2) + count(h - 1))
*/

int countTrees(int n){
    if(n==0 || n==1)
        return 1;
    return countTrees(n-1)*(2*countTrees(n-2) + countTrees(n-1));
}

int countTreesDP(int n){
    int DP[n+1] = {0};
    DP[0] = DP[1] = 1;
    for(int i=2; i<=n; i++)
        DP[i] = DP[i-1] * (2 * DP[i-2] + DP[i-1]);
    return DP[n];
}

int main(){
    cout<<countTrees(3)<<endl;
    cout<<countTreesDP(3)<<endl;
}