#include<bits/stdc++.h>
using namespace std;

/*
    Given an array A of integers, return the length of the longest arithmetic subsequence in A.

    Recall that a subsequence of A is a list A[i_1], A[i_2], ..., A[i_k] with 
    0 <= i_1 < i_2 < ... < i_k <= A.length - 1, 
    and that a sequence B is arithmetic if B[i+1] - B[i] are all the same value 
    (for 0 <= i < B.length - 1).

    Example:
    Input: A = [20,1,15,3,10,5,8]
    Output: 4
    Explanation: 
    The longest arithmetic subsequence is [20,15,10,5].

    Approach:
    It is very similar to LIS problem, but the catch is here we have more constraints 
    than LIS, we can just add a term to be part of a series like LIS, here it can
    only be part of a series when it also shares the common diff that is there in the series.
    
    Now we just track the max length series diff for each term, then also it wont work, since
    there might be a term later on which completes a longer series if it gets a few more sequences.
    
    EG: 1,2,4,6,8
    for 4, if we save only diff 3 {1,4}, then it wont make the longest length with {2,4,6,8} with 
    diff 2, so we save the max length ending at each term for all the differences encountered.
    with the previous terms.
    
    We save info like: for 4: (3,2){with 1}, (2,2){with2}
    So for 6, we can just see if there was a series with diff=2 ending at 4, that gives
    us dp[indexof(4)][2] = 2, so dp[indexof(6)] = 2 + 1
    
    TC: O(N^2)

    <diff, sizeOfSeq ending with A[i] with diff with any previous A[j]>

    A = {20,     1,     15,   3,      10,     5,       8}
    DP= <0,0> <-19,2> <-5,2> <-17,2> <-10,2> <-15,2> <-12,2>
                      <14,2> < 2 ,2> <9,  2> <4,  2> <9,  2>
                             <-12,2> <-5, 3> <-10,2> <-7, 2>
                                     <7,  2> <2,  2> <5,  2>
                                             <-5, 4> <-2, 2>
                                                     <3,  2>

    MaxSeqLen = 4
*/


class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        int N = A.size();
        
        if(N==0 || N==1)
            return N;
            
        vector<unordered_map<int, int>> DP(N, unordered_map<int,int>());
        
        int maxSeqLen = 0;
        for(int j=1; j<N; j++){
            for(int i=0; i<j; i++){
                int diff = A[j]-A[i];
                int current_len = 2;  //current seq length = 2  <A[i], A[j]>
                
                //if the A[i] is a part of a sequence.
                //just like LIS
                if(DP[i].find(diff)!=DP[i].end())
                    current_len = DP[i][diff] + 1;
                
                //if diff seen first time for A[j] then insert in
                //else update it
                if(DP[j].find(diff)==DP[j].end())
                    DP[j].insert({diff, current_len});
                else
                    DP[j][diff] = max(current_len, DP[j][diff]);
                
                
                //update the global max arithmetic seq length
                maxSeqLen = max(maxSeqLen, DP[j][diff]);
                /*to print the sequence, store the diff of maxSeqLen*/
                /*
                    if(DP[i][diff]>maxSeqLen)
                        maxSeqLen = DP[i][diff]
                        diffOfSeqWithMaxLen = diff;
                */
            }
        }
        return maxSeqLen;
    }

    void printSeq(vector<int> &A, vector<unordered_map<int, int>> &DP, int diff){
        for(int i=0; i<N; i++){
            if(DP[i].find(diff)!=DP[i].end())
                cout<<A[i]<<" ";
        }
    }
};

int main(){
    
}

