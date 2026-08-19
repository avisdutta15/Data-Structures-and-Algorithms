#include <bits/stdc++.h>
using namespace std;

/*
    Longest Alternating Sequence

    A sequence of numbers is called a zigzag sequence if 
    differences between successive numbers strictly alternate 
    between positive and negative value. In other words, 
    zigzag subsequence is where elements of subsequence are 
    alternate increasing and decreasing order, means, they 
    satisfy below conditions:

    x1 < x2 > x3 < x4 > x5 < ….  x2 < x3 > x4 < x5 > …. xn

    To add ith as next element in subsequence, consider two cases. 
    First, ith element can be greater than previous element in 
    longest zigzag subsequence till j where j < i. In this case, 
    we are looking for all such j where A[j] < A[i]. Another 
    criteria for j should be that A[j] less than previous element 
    in sequence, that means, at j, we are looking exactly opposite 
    condition than that i.

    Second, ith element can be less than previous element in longest 
    zigzag subsequence till j where j < i. In this case, we are looking 
    for all such j where A[j] > A[i]. Another criteria for j should be 
    that A[j] is greater than previous element in sequence, that means, 
    at j again, we are looking exactly opposite condition than that at i.
    For each i store this two cases.

    Let’s say increase[i] describes LZS, for the first case and decrease[i] describes it for the second case.

    increase[i] = max(decrease[j] + 1) for all j< i && A[j] < A[i]
    decrease[i] = max(increase[j] + 1) for all j< i && A[j] > A[i]

    Time Complexity : O(n^2)

    Approach 2: O(n) using signum function.
    We shall proceed by comparing the mathematical signs(negative or positive) 
    of the difference of two consecutive elements of arr. To achieve this, we 
    shall store the sign of (arr[i] – arr[i-1]) in a variable, subsequently 
    comparing it with that of (arr[i+1] – arr[i]). If it is different, we shall 
    increment our result.
                |  1    if n>0
    signum(n) = |  0    if n=0
                | -1    if n<0

    Input integer array seq[N].
    Initialize integer lastSign to 0. 
    FOR i in range 1 to N - 1
        integer sign = signum(seq[i] - seq[i-1])
        IF sign != lastSign AND IF sign != 0
            increment length by 1. lastSign = sign.
        END IF
    END FOR
    return length.

*/

class Solution{
    public:
        int longestZigZagSequence(vector<int> A){
            if(A.size()==0)
                return 0;

            int n = A.size();
            int increasing[n] = {0};
            int decreasing[n] = {0};
            
            //increasing[i] = max(decreasing[j] + 1) where j<i
            //decreasing[i] = max(increasing[j] + 1) where j<i

            increasing[0] = 1;
            decreasing[0] = 1;
            int res = INT_MIN;
            
            for(int i=1; i<n; i++){
                for(int j=0; j<i; j++){
                    if(A[j] < A[i] && decreasing[j]+1 > increasing[i]){
                        increasing[i] = decreasing[j]+1;
                    }
                    if(A[j] > A[i] && increasing[j]+1 > decreasing[i]){
                        decreasing[i] = increasing[j]+1;
                    }
                }

                res = max(res, max(increasing[i], decreasing[i]));
            }
            
            return res;
        }
        

        int signum(int n){
            if(n>0) return 1;
            if(n==0) return 0;
            if(n<0) return -1;
        }

        int longestZigZagSequenceLinear(vector<int> A){
            int n = A.size();
            if(n==0)
                return 0;
            
            int lastSign = 0;
            int length = 1;
            for(int i=1; i<n; i++){
                int sign = signum(A[i] - A[i-1]);
                if(sign!=0 && sign!=lastSign){
                    lastSign = sign;
                    length++;
                }
            }
            return length;
        }
};

int main(){
    vector<int> A = { 10, 22, 9, 33, 49, 50, 31, 60 }; 
    Solution obj;
    cout<<obj.longestZigZagSequence(A);
}