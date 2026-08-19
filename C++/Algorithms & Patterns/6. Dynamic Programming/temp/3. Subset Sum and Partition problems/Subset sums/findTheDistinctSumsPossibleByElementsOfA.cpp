#include <bits/stdc++.h>
using namespace std;

/*
    Find all distinct subset (or subsequence) sums of an array

    Given a set of integers, find distinct sum that can be generated from the subsets 
    of the given sets and print them in an increasing order. 
    It is given that sum of array elements is small.

    Input : arr[] = {2, 3, 4, 5, 6}
    Output : 0 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 20

                0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
            0   1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 
            2   1  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 
            3   1  0  1  1  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 
            4   1  0  1  1  1  1  1  1  0  1  0  0  0  0  0  0  0  0  0  0  0 
            5   1  0  1  1  1  1  1  1  1  1  1  1  1  0  1  0  0  0  0  0  0 
            6   1  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  0  1 
    
    Approach 1:
    The naive solution for this problem is to generate all the subsets, store 
    their sums in a hash set and finally print all keys from hash set.

    Approach 2:
    We can either make a sum j bu including element A[i] or by excluding element
    A[i]. We will store the possible truth value in dp[i][j].

    The last row will contain the information if sum j can be achieved by any subset 
    of A i.e. if dp[n][j] == 1 then sum j can be achieved.
*/


class Solution{
        void countDistinctSubsetSumsUtil(vector<int> A, int i, int sum, unordered_set<int> &hash){
            if(i==A.size()){
                hash.insert(sum);
                return;
            }
            countDistinctSubsetSumsUtil(A, i+1, sum+A[i], hash);
            countDistinctSubsetSumsUtil(A, i+1, sum, hash);
        }
    public:
        int countDistinctSubsetSums(vector<int> A){
            int i = 0;
            int sum = 0;
            unordered_set<int> hash;
            countDistinctSubsetSumsUtil(A, i, sum, hash);
            
            /*sorting the resultant set is optional*/
            vector<int> ans(hash.begin(), hash.end());
            sort(ans.begin(), ans.end());
            
            for(int i : ans)
                cout<<i<<" ";
            cout<<endl;
            return hash.size();
        }
        int countDistinctSubsetSumsDP(vector<int> A){
            int sum = 0;
            int n = A.size();
            for(int i: A)
                sum += i;
            
            vector<vector<int>> dp(n+1, vector<int>(sum+1, 0));
            for(int i=0; i<=n; i++)
                dp[i][0] = 1;
            
            for(int i=1; i<=sum; i++)
                dp[0][i] = 0;

            for(int i=1; i<=n; i++){
                for(int j=1; j<=sum; j++){
                    //can you make a sum j by excluding A[i-1]?
                    if(dp[i-1][j]==1)
                        dp[i][j] = 1;
                    //can you make a sum j by including A[i-1]?
                    else if(dp[i-1][j-A[i-1]] ==1 )
                        dp[i][j] = 1;
                }
            }  
            
            int sumCount = 0;
            for(int i=0; i<=sum; i++){
                if(dp[n][i] == 1){
                    cout<<i<<" ";
                    sumCount++;
                }
            }
            cout<<endl;
            return sumCount;
        }
};

int main(){
    Solution obj;
    vector<int> A = {2, 3, 4, 5, 6};
    cout<<obj.countDistinctSubsetSums(A)<<endl;
    cout<<obj.countDistinctSubsetSumsDP(A);
}