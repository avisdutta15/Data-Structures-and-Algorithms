#include <bits/stdc++.h>
using namespace std;

/*
    Given two natural number n and m. The task is to find the number of ways in 
    which the numbers that are greater than or equal to m can be added to get the sum n.

    Examples:

    Input : n = 3, m = 1
    Output : 3
    Following are three different ways
    to get sum n such that each term is
    greater than or equal to m
    1 + 1 + 1, 1 + 2, 3 

    Input : n = 2, m = 1
    Output : 2
    Two ways are 1 + 1 and 2

    Recurrence:
        ways(sum, num) = 0 if num>sum
        ways(sum, num) = 1 if num==sum
        ways(sum, num) = ways(sum, num+1) + ways(sum-num, num)
*/

class Solution{
    public:
        int ways(int sum, int num){
            if(num>sum) return 0;
            if(sum==num) return 1;
            return ways(sum, num+1) + ways(sum-num, num);
        }
};

int main(){

}