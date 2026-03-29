#include <bits/stdc++.h>
using namespace std;

/*
    Given a number n, we can divide it in only three parts n/2, n/3 and n/4 (we will 
    consider only integer part). The task is to find the maximum sum we can make by 
    dividing number in three parts recursively and summing up them together.

    Examples:
    Input : n = 12
    Output : 13
    // We break n = 12 in three parts {12/2, 12/3, 12/4} 
    // = {6, 4, 3},  now current sum is = (6 + 4 + 3) = 13 
    // again we break 6 = {6/2, 6/3, 6/4} = {3, 2, 1} = 3 + 
    // 2 + 1 = 6 and further breaking 3, 2 and 1 we get maximum
    // summation as 1, so breaking 6 in three parts produces
    // maximum sum 6 only similarly breaking 4 in three   
    // parts we can get maximum sum 4 and same for 3 also.
    // Thus maximum sum by breaking number in parts  is=13
*/

class Solution{
    public:
        int breakSum(int N){
            if(N==0 || N==1)
                return N;
            return max(breakSum(N/2) + breakSum(N/3) + breakSum(N/4) , N);
        }
};

class Solution2{
    public:
        int breakSum(int N){
            if(N==0 || N==1)
                return N;
            int DP[N+1];
            DP[0] = 0;
            DP[1] = 1;
            for(int i=2; i<=N; i++){
                DP[i] = max(DP[i/2]+DP[i/3]+DP[i/4], i);
            }
            return DP[N];
        }
};

int main(){
    
}