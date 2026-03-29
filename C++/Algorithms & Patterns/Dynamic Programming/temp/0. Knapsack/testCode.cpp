#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;


class Solution{
    void countDistinctSubsetSumsRecursive(vector<int> &A, int N, int subsetSum, unordered_set<int> &distinctSums){
        if(N==0){
            distinctSums.insert(subsetSum);
            return;
        }
        countDistinctSubsetSumsRecursive(A, N-1, subsetSum + A[N-1], distinctSums);
        countDistinctSubsetSumsRecursive(A, N-1, subsetSum, distinctSums);
    }

    void countDistinctSubsetSumsTopDown(vector<int> &A, int N, int sum, unordered_map<int, vector<int, bool>> &lookup){
        if(N == 0)
            return 
        if(lookup[N][sum] == true)
    }

public:
    vector<int> countDistinctSubsetSums(vector<int> &A){
        int N = A.size();
        unordered_set<int> distinctSums;
        countDistinctSubsetSumsRecursive(A, N, 0, distinctSums);

        vector<int> ans;
        for(int i: distinctSums)
            ans.push_back(i);
        
        sort(ans.begin(), ans.end());
        return ans;
    }
};


int main(){
    Solution obj;
    vector<int> A = {1, 2};
    auto distinctSums = obj.countDistinctSubsetSums(A);
    for(int i: distinctSums)
        cout<<i<<" ";
    
    cout<<endl;
    A = {1, 2, 3};
    distinctSums = obj.countDistinctSubsetSums(A);
    for(int i: distinctSums)
        cout<<i<<" ";
        
    return 0;
}