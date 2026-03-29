#include <bits/stdc++.h>
using namespace std;

/*
    Given an array arr[] of size N and a given difference diff, the task is to count 
    the number of partitions that we can perform such that the difference between the 
    sum of the two subsets is equal to the given difference.

    Note: A partition in the array means dividing an array into two parts say S1 and S2 
    such that the union of S1 and S2 is equal to the original array and each element 
    is present in only of the subsets.

    Examples:
    Input: N = 4, arr[] = [5, 2, 6, 4], diff = 3
    Output: 1
    Explanation: We can only have a single partition which is shown below:
    {5, 2} and {6, 4} such that S1 = 7 and S2 = 10 and thus the difference is 3

    Input: N = 5, arr[] = [1, 2, 3, 1, 2], diff = 1
    Output: 5
    Explanation: We can have five partitions which is shown below
    {1, 3, 1} and {2, 2} – S1 = 5, S2 = 4
    {1, 2, 2} and {1, 3} – S1 = 5, S2 = 4
    {3, 2} and {1, 1, 2} – S1 = 5, S2 = 4
    {1, 2, 2} and {1, 3} – S1 = 5, S2 = 4
    {3, 2} and {1, 1, 2} – S1 = 5, S2 = 4

    Approach1:
    Find the subsetsum of 2 subsets. Then at N=0 check if their diff = givenDiff
    
    Approach2:
        We have 2 equations:
            subset1_sum + subset2_sum = total_sum
            subset1_sum - subset2_sum = diff
        ------------------------------------------
        =>  2*subset1_sum = total_sum + diff
        =>    subset1_sum = (total_sum + diff) / 2

    herefore, in this case of array the total number of possible ways depends on the 
    number of possible ways to create a subset having sum S1.

    Therefor ans := count ways to get subset sum = subset1_sum;
*/

class Solution{
        int countSubsetsWithGivenDifferenceRecursive(vector<int> &A, int N, int subset1Sum, int &totalSum, int &diff){
            if(N==0){
                int subset2Sum = totalSum - subset1Sum;
                int subsetsumdiff = subset2Sum - subset1Sum;
                if(subsetsumdiff == diff)
                    return 1;
                return 0; 
            }

            int include = 0, exclude = 0;
            include = countSubsetsWithGivenDifferenceRecursive(A, N-1, subset1Sum+A[N-1], totalSum, diff);
            exclude = countSubsetsWithGivenDifferenceRecursive(A, N-1, subset1Sum, totalSum, diff);
            return include + exclude;
        }
        
        int countSubsetsWithGivenDifferenceTopDown(vector<int> &A, int N, int subset1Sum, int &totalSum, int &diff, unordered_map<string, int> &lookup){
            if(N==0){
                int subset2Sum = totalSum - subset1Sum;
                int subsetsumdiff = subset2Sum - subset1Sum;
                if(subsetsumdiff == diff)
                    return 1;
                return 0; 
            }

            string key = to_string(N) + " " + to_string(subset1Sum);
            if(lookup.find(key) != lookup.end())
                return lookup[key];

            int include = 0, exclude = 0;
            include = countSubsetsWithGivenDifferenceTopDown(A, N-1, subset1Sum+A[N-1], totalSum, diff, lookup);
            exclude = countSubsetsWithGivenDifferenceTopDown(A, N-1, subset1Sum, totalSum, diff, lookup);
            return lookup[key] = include + exclude;
        }

        int countSubsetsWithGivenDifferenceTopDown(vector<int> &A, int diff, int N, int totalSum){
            vector<vector<int>> dp(N+1, vector<int>(totalSum + 1, 0));


            //dp[n][sum] denotes the count of subsets with n elements having subset_sum = sum
            for(int n=0; n<=N; n++){
                for(int sum=0; sum<=totalSum; sum++){
                    if(n==0 && sum==0)
                        dp[n][sum] = 1;
                    else if(n==0 && sum!=0)
                        dp[n][sum] = 0;
                    else{
                        int include = 0, exclude = 0;
                        if(A[n-1]<=sum)
                            include = dp[n-1][sum-A[n-1]];
                        exclude = dp[n-1][sum];
                        dp[n][sum] = include + exclude;
                    }
                }
            }

            int count = 0;
            //iterate the last row, as it denotes the number of subset sums that are possible with
            //total N elements.
            for(int sum=0; sum<=totalSum; sum++){
                if(dp[N][sum] != 0){
                    int subset1Sum = sum;
                    int subset2Sum = totalSum - subset1Sum;
                    if(subset2Sum - subset1Sum == diff)
                        count = count + dp[N][subset1Sum];
                }
            }
            return count;
        }
    public:
        int countSubsetsWithGivenDifference(vector<int> &A, int diff){
            int N = A.size();
            int totalSum = accumulate(A.begin(), A.end(), 0);
            int subset1Sum = 0;
            // return countSubsetsWithGivenDifferenceRecursive(A, N, subset1Sum, totalSum, diff);

            // unordered_map<string, int> lookup;
            // return countSubsetsWithGivenDifferenceTopDown(A, N, subset1Sum, totalSum, diff, lookup);
            return countSubsetsWithGivenDifferenceTopDown(A, diff, N, totalSum);
        }
};


int main(){
    Solution obj;
    vector<int> A = {5, 2, 6, 4};
    cout<<obj.countSubsetsWithGivenDifference(A, 3)<<endl;

    A = {1, 2, 3, 1, 2};
    cout<<obj.countSubsetsWithGivenDifference(A, 1)<<endl;
    return 0;
}