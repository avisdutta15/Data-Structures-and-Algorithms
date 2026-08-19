#include <bits/stdc++.h>
using namespace std;

/*
    We need to find the size of the maximum size subset whose sum is equal to the given sum.

    Examples:  
    Input : set[] = {2, 3, 5, 7, 10, 15},
            sum  = 10
    Output : 3
    The largest sized subset with sum 10
    is {2, 3, 5}

    Input : set[] = {1, 2, 3, 4, 5}
            sum = 4
    Output : 2


    Approach:
    To solve the subset sum problem, use the same DP approach as given in the subset sum problem. 
    To further count the maximal subset, we use another DP array (called as ‘count array’) where 
    count[i][j] is maximal of  

    count[i][j-1]. Here current element is not considered.
    count[i- X][j-1] + 1. Here X is the value of the current element selected for the subset.
*/

class Solution{
        //What is the maximum size subset you can make with N elements and subset sum = sum.
        int maximumSizeSubsetWithSumKRecursive(vector<int> &A, int N, int sum){
            if(N == 0 && sum == 0)
                return 0;
            
            //return Int_Min to denote not possible
            if(N == 0 && sum != 0)
                return INT_MIN;
            
            int include = INT_MIN, exclude = INT_MIN;
            if(A[N-1] <= sum){
                int canReachSumByIncludingCurrentElem = maximumSizeSubsetWithSumKRecursive(A, N-1, sum - A[N-1]);
                if(canReachSumByIncludingCurrentElem != INT_MIN)
                    include = 1 + canReachSumByIncludingCurrentElem;
            }

            exclude = maximumSizeSubsetWithSumKRecursive(A, N-1, sum);

            return max(include, exclude);            
        }

        int maximumSizeSubsetWithSumKTopDown(vector<int> &A, int N, int sum, unordered_map<string, int> &lookup){
            if(N == 0 && sum == 0)
                return 0;
            
            //return Int_Min to denote not possible
            if(N == 0 && sum != 0)
                return INT_MIN;
            
            string key = to_string(N) + " " + to_string(sum);
            if(lookup.find(key) != lookup.end())
                return lookup[key];

            int include = INT_MIN, exclude = INT_MIN;
            if(A[N-1] <= sum){
                int canReachSumByIncludingCurrentElem = maximumSizeSubsetWithSumKTopDown(A, N-1, sum - A[N-1], lookup);
                if(canReachSumByIncludingCurrentElem != INT_MIN)
                    include = 1 + canReachSumByIncludingCurrentElem;
            }

            exclude = maximumSizeSubsetWithSumKTopDown(A, N-1, sum, lookup);

            return lookup[key] = max(include, exclude);            
        }

        void printMatrix(const vector<vector<int>>& matrix) {
            for (const auto& row : matrix) { // Loop through each row
                for (const auto& element : row) { // Loop through each element in the row
                    cout << element << "\t"; // Print element with space
                }
                cout << endl; // Move to the next line after each row
            }
        }

        void printItems(vector<int> A, int N, int targetSum, vector<vector<int>>& dp){
            int n = N; 
            int sum = targetSum;

            while(n>0 && sum>0){
                int excluded = dp[n-1][sum];
                if(dp[n][sum] == excluded)
                    n = n-1;
                else{
                    cout<<A[n-1]<<" ";
                    //once this item is included, goto the next item with reduced sum.
                    sum = sum - A[n-1];
                    n = n - 1; 
                }
            } 
        }

        int maximumSizeSubsetWithSumKBottomUp(vector<int> &A, int N, int target){
            vector<vector<int>> subarraySize(N+1, vector<int>(target+1, 0));

            for(int n=0; n<=N; n++){
                for(int sum=0; sum<=target; sum++){
                    if(n==0 && sum==0){
                        subarraySize[n][sum] = 0;       //denote possible
                    }
                    else if(n==0 && sum!=0){
                        subarraySize[n][sum] = -1;      //denote not possible
                    }
                    else{
                        int sizeIfIncluded = -1, sizeIfExcluded = -1;
                        if(A[n-1]<=sum){
                            if(subarraySize[n-1][sum-A[n-1]] != -1){
                                sizeIfIncluded = 1 + subarraySize[n-1][sum-A[n-1]];
                            }
                        } 
                        sizeIfExcluded = subarraySize[n-1][sum];
                        subarraySize[n][sum] = max(sizeIfIncluded, sizeIfExcluded);
                    }
                }
            }
            // printMatrix(subarraySize);
            cout<<endl<<"Items: ";
            printItems(A, N, target, subarraySize);
            cout<<endl<<"Length: ";
            return subarraySize[N][target];
        }

    public:
        int maximumSizeSubsetWithSumK(vector<int> &A, int sum){
            int N = A.size();
            //return maximumSizeSubsetWithSumKRecursive(A, N, sum);

            // unordered_map<string, int> lookup;
            // return maximumSizeSubsetWithSumKTopDown(A, N, sum, lookup);

            return maximumSizeSubsetWithSumKBottomUp(A, N, sum);
        }
};


int main(){
    Solution obj;
    vector<int> A = {2, 3, 5, 7, 10, 15};
    cout<<obj.maximumSizeSubsetWithSumK(A, 10)<<endl;   //3 {2, 3, 5}

    A = {1, 2, 3, 4, 5};
    cout<<obj.maximumSizeSubsetWithSumK(A, 4)<<endl;    //2 {1, 3}

    return 0;
}