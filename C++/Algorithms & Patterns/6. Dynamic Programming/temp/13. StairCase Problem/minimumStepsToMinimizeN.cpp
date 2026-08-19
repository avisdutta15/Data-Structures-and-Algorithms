#include <bits/stdc++.h>
using namespace std;
/*
    Given a number n, count minimum steps to minimize it to 1 according to the following criteria:

    If n is divisible by 2 then we may reduce n to n/2.
    If n is divisible by 3 then you may reduce n to n/3.
    Decrement n by 1.
    Examples:

    Input : n = 10
    Output : 3

    Input : 6
    Output : 2
*/
int getMinSteps(int n, int *memo){ 
    if (n == 1) 
       return 0; 
    if (memo[n] != -1) 
       return memo[n]; 
  
    // store temp value for n as min( f(n-1), f(n/2), f(n/3)) +1 
    int res = getMinSteps(n-1, memo); 
  
    if (n%2 == 0) 
        res = min(res, getMinSteps(n/2, memo)); 
    if (n%3 == 0) 
        res = min(res, getMinSteps(n/3, memo)); 
  
    // store memo[n] and return 
    memo[n] = 1 + res; 
    return memo[n]; 
} 
   
int getMinSteps(int n){ 
    int memo[n+1]; 
  
    // initialize memoized array 
    for (int i=0; i<=n; i++) 
        memo[i] = -1; 
  
    return  getMinSteps(n, memo); 
} 
  
int main(){ 
    int n = 10; 
    cout << getMinSteps(n); 
    return 0; 
} 
