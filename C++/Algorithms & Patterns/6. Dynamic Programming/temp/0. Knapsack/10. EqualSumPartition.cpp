#include <bits/stdc++.h>
using namespace std;


class Solution{
    bool equalSumPartitionRecursive(vector<int> &A, int N, int sum){
        if(N == 0 && sum ==0)
            return true; 
        if(N == 0 && sum!=0)
            return false;
        
        bool include = false, exclude = false;
        if(A[N-1]<=sum)
            include = equalSumPartitionRecursive(A, N-1, sum - A[N-1]);
        exclude = equalSumPartitionRecursive(A, N-1, sum);
        return include || exclude;
    }

    bool equalSumPartitionTopDown(vector<int> &A, int N, int sum, unordered_map<string, bool> &lookup){
        if(N == 0 && sum ==0)
            return true; 
        if(N == 0 && sum!=0)
            return false;
        
        string key = to_string(N) + " " + to_string(sum);
        if(lookup.find(key) != lookup.end())
            return lookup[key];

        bool include = false, exclude = false;
        if(A[N-1]<=sum)
            include = equalSumPartitionTopDown(A, N-1, sum - A[N-1], lookup);
        exclude = equalSumPartitionTopDown(A, N-1, sum, lookup);

        lookup[key] = include || exclude;
        
        return lookup[key];
    }

    bool equalSumPartitionBottomUp(vector<int> &A, int N, int sum){
        vector<vector<bool>> dp(N+1, vector<bool>(sum+1, false));

        for(int n=0; n<=N; n++){
            for(int w=0; w<=sum; w++){
                if(n == 0 && w == 0)
                    dp[n][w] = true;
                else if(n == 0 && w != 0)
                    dp[n][w] = false;
                else{
                    bool include = false, exclude = false;
                    if(A[n-1] <= w)
                        include = dp[n-1][w-A[n-1]];
                    exclude = dp[n-1][w];
                    dp[n][w] = include || exclude;
                }
            }
        }
        return dp[N][sum];
    }

public:
    bool equalSumPartition(vector<int> A){
        int N = A.size();
        int sum = accumulate(A.begin(), A.end(), 0);
        //if the total sum of array elements can be divided into 2 parts then
        //the total sum will be even. else not possible.
        if(sum % 2!=0)
            return false;
        //return equalSumPartitionRecursive(A, N, sum/2);        
        // unordered_map<string, bool> lookup;
        // return equalSumPartitionTopDown(A, N, sum/2, lookup); 
        return equalSumPartitionBottomUp(A, N, sum/2);
    }
};


int main(){
    Solution obj;
    vector<int> A = {1, 5, 11, 5};
    obj.equalSumPartition(A) == true? cout<<"Possible"<<endl : cout<<"Not Possible"<<endl;
}