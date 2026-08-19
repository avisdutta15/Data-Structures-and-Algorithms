#include<bits/stdc++.h>
using namespace std;

/*

    Lookup:
        0  1  2  3  4
    0   1  0  0  0  0 
    1   1  1  0  0  0 
    2   1  1  1  1  0 
    3   1  1  1  1  1 
    4   1  1  1  1  1 
    5   1  1  1  1  1 

    Count:
        0  1  2  3  4
    0   0  0  0  0  0
    1   0  1  0  0  0 
    2   0  1  1  2  0 
    3   0  1  1  2  2 
    4   0  1  1  2  2 
    5   0  1  1  2  2 
    
    Inititalize the first row/column with 0 denoting subset of size 0.
    
    While excluding the current element, count[i][j] = count[i-1][j]
    If the sum is possible by including/excluding the current element then, 
        if(DP[i][j]==1){
            countByExcluding = count[i-1][j];
            countByIncluding = count[i-1][j-A[i-1]] + 1;   //+1 because including current element
            count[i][j] = max(countByExcluding, countByIncluding);
        }
 
*/

class Solution{
    public:
        int maxSizeSubsetWithSumKUtil(vector<int> A, int sum, int index, int count){
            if(sum==0)
                return count;
            
            if(sum<0 || index>=A.size())
                return INT_MIN;

            //if the current element cannot be included then exclude
            if(sum < A[index])
                return maxSizeSubsetWithSumKUtil(A, sum, index+1, count);
            
            //else return the maximum subset size with sum K by either including / excluding the current element
            return max(maxSizeSubsetWithSumKUtil(A, sum, index+1, count), 
                       maxSizeSubsetWithSumKUtil(A, sum-A[index], index+1, count+1));
        }
        int maxSizeSubsetWithSumK(vector<int> A, int sum){
            int subsetSize = maxSizeSubsetWithSumKUtil(A, sum, 0, 0);
            return subsetSize==INT_MIN?0:subsetSize;
        }
};

class Solution2{
    unordered_map<int, int> lookup;
    public:
        int maxSizeSubsetWithSumKUtil(vector<int> A, int sum, int index, int count){
            if(sum==0)
                return count;
            
            if(sum<0 || index>=A.size())
                return INT_MIN;

            if(lookup.count(index)>0)
                return lookup[index];

            //if the current element cannot be included then exclude
            if(sum < A[index])
                return lookup[index] = maxSizeSubsetWithSumKUtil(A, sum, index+1, count);
            
            //else return the maximum subset size with sum K by either including / excluding the current element
            return lookup[index] = max(maxSizeSubsetWithSumKUtil(A, sum, index+1, count), 
                       maxSizeSubsetWithSumKUtil(A, sum-A[index], index+1, count+1));
        }
        int maxSizeSubsetWithSumK(vector<int> A, int sum){
            int subsetSize = maxSizeSubsetWithSumKUtil(A, sum, 0, 0);
            return subsetSize==INT_MIN?0:subsetSize;
        }
};


class Solution3{
    public:
        int maxSizeSubset(vector<int> A, int totalSum){
            int n = A.size();

            int lookup[n+1][totalSum+1] = {0};
            int count[n+1][totalSum+1] = {-1};

            for(int i=0; i<=n; i++){
                lookup[i][0] = 1;
                count[i][0] = 0;
            }

            for(int sum=1; sum<=totalSum; sum++){
                lookup[0][sum] = 0;
                count[0][sum] = -1;
            }
            lookup[0][0] = 1;
            count[0][0] = 0;
            for(int i=1; i<=n; i++){
                for(int sum=1; sum<=totalSum; sum++){
                    if(A[i-1]>sum){
                        lookup[i][sum] = lookup[i-1][sum];
                        count[i][sum] = count[i-1][sum];
                    }
                    else{
                        int include = lookup[i-1][sum-A[i-1]];
                        int exclude = lookup[i-1][sum];
                        lookup[i][sum] = include||exclude;
                    }

                    //if sum is possible by either including / excluding the current element
                    //then count the max subset size.
                    if(lookup[i][sum]==1){
                        count[i][sum] = max(count[i-1][sum-A[i-1]]+1 , count[i-1][sum]);
                    }
                }
            }
            
            /*
            for(int i=0; i<=n; i++){
                for(int j=0; j<=totalSum; j++)
                    cout<<lookup[i][j]<<" ";
                cout<<endl;
            }
            for(int i=0; i<=n; i++){
                for(int j=0; j<=totalSum; j++)
                    cout<<count[i][j]<<" ";
                cout<<endl;
            }*/
            
            return count[n][totalSum];
        }
};

int main(){
    vector<int> A = {1, 2, 3, 4, 5};
    int sum = 4;

    Solution obj;
    int size = obj.maxSizeSubset(A, sum);
    if(size==-1)
        cout<<"No Subset possible";
    else    
        cout<<size;
}