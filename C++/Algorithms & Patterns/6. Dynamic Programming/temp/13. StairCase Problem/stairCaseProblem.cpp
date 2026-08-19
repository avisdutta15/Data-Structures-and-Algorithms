#include <bits/stdc++.h>
using namespace std;

/*
    https://www.youtube.com/watch?v=5o-kdjv7FD0
    Problem Statement:
    -----------------
    Given N, count the number of ways to express N as sum of 1, 2 and 3.

    Examples:

    Input :  N = 3
    Output : 4 
    Explanation: 1+1+1 
                 1+2
                 2+1
                 3
*/

/*
    Approach:
    --------
    Not a coin change problem. Since repetition is allowed. Eg: Sum = 3 and coins = 1, 2, 3 then
    possible ways are :

    a) 1+1+1
    b) 1+2
    c) 2+1 (Repition of 1+2)
    d) 3

    Note that b) and c) are treated as different ways thus differing from standard coin change problem 
    (where those 2 are treated as one way).

    So the recurrence becomes:
        T(n) = T(n-1) + T(n-2) + T(n-3)
        T(1) = 1
        T(2) = 2 [by taking 1+1 or 2]
        Base Case:
        T(0) = 1 [argument can be you are standing at stair 0, to get to stair 0 your need to take 1 step which is silly]
             __
          __| 3
       __| 2
    __| 1
    0
*/

class Solution
{
    public:
        int countWays(int n){
            if(n<0)
                return 0;
            if(n==0)
                return 1;
            return countWays(n-1) + countWays(n-2) + countWays(n-3);
        }
        
        //  Steps:        1 1 2 4
        //  Stair Number: 0 1 2 3
        int countWaysDP(int n){
            
            int DP[n+1];
            DP[0] = 1;
            DP[1] = 1;
            DP[2] = 2;
            for(int i=1; i<=n; i++)
                DP[i] = DP[i-1] + DP[i-2] + DP[i-3];
            
            return DP[n];
        }

        //if steps = {1, 3, 4} then 
        //num_ways(n) = num_ways(n-1) + num_ways(n-3) + num_ways(n-4)
        //But we have to check if n is greater than the jump size. Because if 
        //n is smaller than the jump size then we will over jump n.
        int countWays(int N, vector<int> steps){
            if(N==0)
                return 1;
            
            int total = 0;
            for(int step: steps){
                //if you can jump then calculate total ways for this stairCase
                if(N-step>=0)
                    total = total + countWays(N-step, steps);       
            } 
            return total;
        }

        int countWaysDP(int N, vector<int> steps){
            if(N==0)
                return 1;
            if(N<0)
                return 0;
            
            int DP[N+1];
            DP[0] = 1;
            int totalWaysForthisStairCase;

            for(int stairCase = 1; stairCase<=N; stairCase++){
                
                totalWaysForthisStairCase = 0;
                
                for(int step: steps){
                    //if you can jump then calculate total ways for this stairCase
                    if(stairCase-step >= 0)
                        totalWaysForthisStairCase = totalWaysForthisStairCase + DP[stairCase - step];
                }
                DP[stairCase] = totalWaysForthisStairCase;
            }
            return DP[N];
        }
};

int main(){
    Solution obj;    
    
    cout<<obj.countWays(4)<<endl;
    cout<<obj.countWaysDP(4)<<endl;

    //Variation: You are given a set of allowed steps and total number of stairs
    //           Find the number of ways you can reach the top with the allowed steps
    vector<int> steps = {1, 2, 3};
    cout<<obj.countWays(4, steps)<<endl;
    cout<<obj.countWaysDP(4, steps);
    return 0;
}