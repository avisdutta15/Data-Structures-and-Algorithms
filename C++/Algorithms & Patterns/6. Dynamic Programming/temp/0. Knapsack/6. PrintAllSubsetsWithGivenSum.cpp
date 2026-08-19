#include <bits/stdc++.h>
using namespace std;

/*
    Ref: https://www.youtube.com/watch?v=qtqMTgmDpQg
         
 */

class Solution{
        bool getAllSubsetsWithGivenSumRecursive(vector<int> &A, int N, int target, vector<int> &subset, vector<vector<int>> &allSubsets){
            if(N==0 && target==0){
                allSubsets.push_back(subset);
                return true;
            }

            if(N==0 && target!=0)
                return false;

            bool include = false, exclude = false;

            /*Include*/
            if(A[N-1]<=target){
                subset.push_back(A[N-1]);
                include = getAllSubsetsWithGivenSumRecursive(A, N-1, target-A[N-1], subset, allSubsets);
                subset.pop_back();
            }

            /*Exclude*/
            exclude = getAllSubsetsWithGivenSumRecursive(A, N-1, target, subset, allSubsets);

            return include || exclude;
        }

        bool getAllSubsetsWithGivenSumTopDown(vector<int> &A, int N, int target, vector<int> &subset, vector<vector<int>> &allSubsets, unordered_map<string, bool> &lookup){
            if(N==0 && target==0){
                allSubsets.push_back(subset);
                return true;
            }

            if(N==0 && target!=0)
                return false;

            string key = to_string(N) + " " + to_string(target);
            if(lookup.find(key)!=lookup.end())
                return lookup[key];

            bool include = false, exclude = false;
            
            /*Include*/
            if(A[N-1] <= target){
                subset.push_back(A[N-1]);
                getAllSubsetsWithGivenSumTopDown(A, N-1, target-A[N-1], subset, allSubsets, lookup);
                subset.pop_back();
            }
            
            /*Exclude*/
            exclude = getAllSubsetsWithGivenSumTopDown(A, N-1, target, subset, allSubsets, lookup);
            
            lookup[key] = include || exclude;
            return lookup[key];
        }

        void printMatrix(vector<vector<bool>> &lookup){
            for(int i=0; i<lookup.size(); i++){
                for(int j=0; j<lookup[0].size(); j++)
                    lookup[i][j]==true ? cout<<" T " : cout<<" F ";
                cout<<endl;
            }
        }

        vector<vector<int>> getAllSubsetsWithGivenSumBottomUp(vector<int> &A, int N, int target){
            vector<vector<bool>> dp(N+1, vector<bool>(target+1, false));
            
            for(int n=0; n<=N; n++){
                for(int sum=0; sum<=target; sum++){
                    if(n==0 && sum==0)
                        dp[n][sum] = true;
                    else if(n==0 && sum!=0)
                        dp[n][sum] = false;
                    else{
                        bool include = false, exclude = false;
                        if(A[n-1]<=sum)
                            include = dp[n-1][sum-A[n-1]];
                        exclude = dp[n-1][sum];
                        dp[n][sum] = include || exclude;
                    }
                }
            }
            //For debugging
            //printMatrix(dp);
            vector<vector<int>> allSubsets;
            
            //Do a bfs from the bottom right element.
            //insert into the queue if the target can be reached by including or excluding current
            //element. Remember current element in array is A[n-1] and in dp is dp[n][sum].
            //Q{n, sum, [items]}
            queue<pair<int, pair<int, vector<int>>>> Q;
            int n = N, sum = target;
            Q.push({n, {sum, vector<int>()}});
            while(!Q.empty()){
                auto top = Q.front();
                Q.pop();

                n = top.first;
                sum = top.second.first;
                auto items = top.second.second;

                //base case. if n==0 and sum==0 then we got the subset. insert it into all subsets.
                if(n == 0 && sum == 0){
                    allSubsets.push_back(items);
                }
                //need to check this case using dry run.
                else if(n == 1 && sum!=0 && dp[1][sum]==true){
                    items.push_back(A[n-1]);
                    if(A[n-1] == sum)
                        allSubsets.push_back(items);
                }
                else{
                    bool excluded = dp[n-1][sum];

                    //if we can reach the target by excluding the current element
                    //then push it to Q.
                    if(excluded == true){
                        Q.push({n-1, {sum, items}});
                    }
                    
                    //if we can reach the target by including the current element
                    //then push it to Q.
                    if(A[n-1]<=sum){
                        bool included = dp[n-1][sum-A[n-1]];
                        if(included == true){
                            items.push_back(A[n-1]);
                            Q.push({n - 1, {sum - A[n-1], items}});
                        }
                    }
                }
            }
            return allSubsets;
        }

    public:
        vector<vector<int>> getAllSubsetsWithGivenSum(vector<int> &A, int target){
            int N = A.size();
            vector<vector<int>> allSubsets;
            // vector<int> subset;
            // unordered_map<string, bool> lookup;

            // getAllSubsetsWithGivenSumRecursive(A, N, target, subset, allSubsets);
            // getAllSubsetsWithGivenSumTopDown(A, N, target, subset, allSubsets, lookup);

            allSubsets = getAllSubsetsWithGivenSumBottomUp(A, N, target);
            return allSubsets;
        }
};


int main(){
    Solution obj;
    vector<int> A = {24, 1, -1};
    auto allSubsets = obj.getAllSubsetsWithGivenSum(A, 24); //{24}, {24, 1, -1}
    for(auto subset: allSubsets){
        for(int i: subset)
            cout<<i<<" ";
        cout<<endl;
    }
    return 0;
}