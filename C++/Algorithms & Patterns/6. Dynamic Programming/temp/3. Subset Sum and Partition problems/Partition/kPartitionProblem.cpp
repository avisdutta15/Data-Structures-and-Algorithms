#include <bits/stdc++.h>
using namespace std;

/*
    Given an array of integers nums and a positive integer k, find whether it's 
    possible to divide this array into k non-empty subsets whose sums are all equal.

    Example 1:

    Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
    Output: True
    Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
*/

class Solution{

    public:
        vector<int> canPartitionKSubsets(vector<int> A, int K){
            if(A.size()==0 || K<=0)
                return vector<int>();
            
            vector<bool> visited(A.size(), false);
            vector<int> numsIndexToBucketMap(A.size(), -1);
            int totalSubsetSum = accumulate(A.begin(), A.end(), 0);
            
            if(totalSubsetSum % K !=0)
                return vector<int>();
            int targetSubsetSum = totalSubsetSum / K;
            int currentSubsetSum = 0;
            int startIndex = 0;
            
            bool isPartitionPossible =  dfs(A, visited, numsIndexToBucketMap, startIndex, K, currentSubsetSum, targetSubsetSum);
            if(!isPartitionPossible)
                return vector<int>();
            return numsIndexToBucketMap;
        } 

        bool dfs(vector<int> &A, vector<bool> &visited, vector<int> &numsIndexToBucketMap, int startIndex, int K, int currentSubsetSum, int targetSubsetSum){
            /*if only 1 bucket is left then return true*/
            if(K==1){
                for(int &i: numsIndexToBucketMap){
                    if(i==-1)
                        i = 1;
                }
                return true;
            }
            
            /*If we have reached the target sum for one bucket then go to another bucket*/
            if(currentSubsetSum == targetSubsetSum)
                return dfs(A, visited, numsIndexToBucketMap, 0, K-1, 0, targetSubsetSum);
            
            for(int i=startIndex; i<A.size(); i++){
                if(visited[i]==false){
                    visited[i] = true;
                    numsIndexToBucketMap[i] = K;
                    if(dfs(A, visited, numsIndexToBucketMap, i+1, K, currentSubsetSum+A[i], targetSubsetSum)==true)
                        return true;
                    visited[i] = false;
                    numsIndexToBucketMap[i] = -1;
                }
            }
            return false;
        }
};

void printBucketItems(vector<int> A, vector<int> numsIndexToBucketMap, int K){
    if(numsIndexToBucketMap.size()==0)
        cout<<"Partition not Possible"<<endl;
    else{
        for(int bucketId = 1; bucketId<=K; bucketId++){
            cout<<"Bucket "<<bucketId<<" : ";
            for(int i=0; i<numsIndexToBucketMap.size(); i++){
                if(numsIndexToBucketMap[i] == bucketId)
                    cout<<A[i]<<" ";
            }
            cout<<endl;
        }        
    }
}

int main(){
    vector<int> A = {2, 1, 4, 5, 6};
    int K = 3;
    Solution obj;
    vector<int> numsIndexToBucketMap = obj.canPartitionKSubsets(A, K);
    printBucketItems(A, numsIndexToBucketMap, K);
    
    cout<<endl;
    
    A = {2, 1, 5, 5, 6};
    K = 3;
    numsIndexToBucketMap = obj.canPartitionKSubsets(A, K);
    printBucketItems(A, numsIndexToBucketMap, K);
}