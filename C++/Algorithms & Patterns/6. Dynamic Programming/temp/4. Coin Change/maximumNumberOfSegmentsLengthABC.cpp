#include <bits/stdc++.h>
using namespace std;

/*
    Given a positive integer N, find the maximum number of segments of lengths 
    a, b and c that can be formed from N .

    Input : N = 17, a = 2, b = 1, c = 3 
    Output : 17 
    N can be divided into 17 segments of 1 or 8 
    segments of 2 and 1 segment of 1. But 17 segments
    of 1 is greater than 9 segments of 2 and 1. 

    Intuition:
    Basically the max number of coins to represent a sum


*/


class Solution{
    public:
        int coinChangeUtil(int N, int A, int B, int C){
            if(N==0)
                return 0;
            if(N<0)
                return INT_MIN;
                
            int a = INT_MIN, b = INT_MIN, c = INT_MIN;
            int maxCount = INT_MIN;

            if(N-A>=0){
                int maxWaysInWhichNCanBeAchievedUsingA = coinChangeUtil(N-A, A, B, C);
                if(maxWaysInWhichNCanBeAchievedUsingA!=INT_MIN)
                    a = 1 + maxWaysInWhichNCanBeAchievedUsingA;
            }
            
            if(N-B>=0){
                int maxWaysInWhichNCanBeAchievedUsingB = coinChangeUtil(N-B, A, B, C);
                if(maxWaysInWhichNCanBeAchievedUsingB!=INT_MIN)
                    b = 1 + maxWaysInWhichNCanBeAchievedUsingB;
            }
                
            if(N-C>=0){
                int maxWaysInWhichNCanBeAchievedUsingC = coinChangeUtil(N-C, A, B, C);
                if(maxWaysInWhichNCanBeAchievedUsingC!=INT_MIN)
                    c = 1 + maxWaysInWhichNCanBeAchievedUsingC;
            }
            
            maxCount = max(a, max(b,c));
            return maxCount;
        }

        int coinChange(int N, int A, int B, int C){
            int maxWaysInWhichNCanBeAchieved = coinChangeUtil(N, A, B, C);
            return maxWaysInWhichNCanBeAchieved == INT_MIN ? 0 : maxWaysInWhichNCanBeAchieved;
        }
};

int main(){
    Solution obj;
    cout<<obj.maxSegments(3, 5, 2, 5);
}