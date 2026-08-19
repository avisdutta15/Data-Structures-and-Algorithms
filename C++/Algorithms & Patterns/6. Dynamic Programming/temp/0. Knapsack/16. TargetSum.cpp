#include <bits/stdc++.h>
using namespace std;

/*
    You are given an integer array nums and an integer target.

    You want to build an expression out of nums by adding one of the symbols '+' and '-' 
    before each integer in nums and then concatenate all the integers.

    For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and 
    concatenate them to build the expression "+2-1".
    Return the number of different expressions that you can build, which evaluates to target.

    Example 1:
    Input: nums = [1,1,1,1,1], target = 3
    Output: 5
    Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
    -1 + 1 + 1 + 1 + 1 = 3
    +1 - 1 + 1 + 1 + 1 = 3
    +1 + 1 - 1 + 1 + 1 = 3
    +1 + 1 + 1 - 1 + 1 = 3
    +1 + 1 + 1 + 1 - 1 = 3

    Example 2:
    Input: nums = [1], target = 1
    Output: 1
    

    Constraints:
    1 <= nums.length <= 20
    0 <= nums[i] <= 1000
    0 <= sum(nums[i]) <= 1000
    -1000 <= target <= 1000

Approach 1:
    1.  Recursive.
    func(A, current_sum, N, targetSum) :- Returns In how many ways we can reach targetsum by 
                                        plus and minus signs to N elements of array A.

        Keep a variable called current_sum. (running sum of elements)
        base case:
            if(n==0 && sum == targetsum)
                return 1;
            if(n==0 && sum != targetsum)
                return 0;
        assign plus sign to the current element. This makes the sum by current_sum + A[n-1] and recur
        assign minus sign to the current element. This makes the sum by current_sum - A[n-1] and recur
        return count of possibilities of reaching target sum by doing plus and minus. 
            i.e. return plus + minus

    2.  Top Down
        Overlapping subproblem and 
        optimal substructure observed. 
        func(N, currentSum) has overlapping subproblem.

        keep a lookup table where key = "N + _ + currentSum", value = number of possibilities.

    3.  Bottom Up.


    
    Define the DP Table:

    Let dp[i][sum] represent the number of ways to achieve the target sum sum using the 
    first i elements in nums.
    The target sum must lie between -totalsum and +totalsum.
    If not then return 0.

    Translate Recursive Relation:
    dp[N+1][totalSum+1]
        The recursive relation is:
            plus = 0, minus = 0;
            plus = dp[i-1][sum - nums[i-1]]
            minus= dp[i-1][sum + nums[i-1]]
            dp[i][sum] = plus + minus.
        
    return dp[N][targetsum]

    In the DP table, adjust indices accordingly.
    Offset Negative Indices:
        To handle negative sums, shift the target sum by an offset equal to the total sum of nums (total_sum). 
        This ensures all sums are positive.
    Iterative Filling:
        Fill the DP table iteratively for all indices and possible target sums.

    Why is the offset needed?
    The inner loop has to run from -totalSum to totalSum.
    We cannot have a -ve index in dp array. so we need to map 
        -totalsum = 0
        0 = totalsum
        totalsum  = 2*totalsum
    in the dp array.
    To visialize
        sum range:                      - totalsum              0                totalsum
        mappedSum in dp array:              0                totalSum           2*totalSum

    To do this we need to take an offset = totalsum

    Example
    Input:  nums = {1, 1, 2, 3};    target = 1;
    Possible Sums:
        -7  -6  -5  -4  -3  -2  -1   0   1   2   3   4   5   6   7
    Mapped Indices (Offset = 7)
         0   1   2   3   4   5   6   7   8   9  10  11  12  13  14

    sum = -7 maps to index 0
    sum = 0 maps to index 7
    sum = 7 maps to index 14
    target = 1 is stored at index 8 (since 1 + offset = 8).

    Thus the size of the dp table will be dp[N+1][2*totalsum + 1]  

    Thus, when checking for the number of ways to reach target, we return:
    return dp[nums.size()][target + offset];  // dp[4][8]

    This ensures all sums fit into valid indices.
    T.C: O(n∗totalSum)
    S.C: O(n∗2*totalSum)

Approach 2:
    target sum with + - assigned means, the array will be divided into
    2 subsets such that the difference between the sum of those 2 subsets will be target.
    Let P be the positive subset and N be the negative subset
        sum(P) + sum(N) = totalSum          .....(i)
        sum(P) - sum(N) = targetSum         .....(ii)
    ----------------------------------
        2sum(P)         = totalSum + targetSum           .....(i+ii)
        sum(P)          = (totalSum + targetSum)/2

    This means:
    We need to count subsets with sum S1= (totalSum + targetSum)/2.

    For example:
    Given nums = [1, 2, 3, 4, 5] and target = 3 
    then one possible solution is +1-2+3-4+5 = 3
    Here positive subset is P = [1, 3, 5] and negative subset is N = [2, 4] 

*/

class Solution1{
        int targetSumRecursive(vector<int> &A, int N, int currentSum, int targetSum){
            if(N==0 && currentSum == targetSum)
                return 1;
            if(N==0 && currentSum!=targetSum)
                return 0;

            int plus = 0, minus = 0;
            plus = targetSumRecursive(A, N-1, currentSum + A[N-1], targetSum);
            minus = targetSumRecursive(A, N-1, currentSum - A[N-1], targetSum);
            return plus + minus;
        }

        int targetSumTopDown(vector<int> &A, int N, int currentSum, int targetSum, unordered_map<string, int> &lookup){
            if(N==0 && currentSum == targetSum)
                return 1;
            if(N==0 && currentSum!=targetSum)
                return 0;

            string key = to_string(N) + " " + to_string(currentSum);
            if(lookup.find(key)!=lookup.end())
                return lookup[key];

            int plus = 0, minus = 0;
            plus = targetSumRecursive(A, N-1, currentSum + A[N-1], targetSum);
            minus = targetSumRecursive(A, N-1, currentSum - A[N-1], targetSum);
            return lookup[key] = plus + minus;
        }

        void printMatrix(vector<vector<int>> dp){
            int N = dp.size(), M = dp[0].size();
            for(int i=0; i<N; i++){
                for(int j=0; j<M; j++)
                    cout<<dp[i][j]<<" ";
                cout<<endl;
            }
        }

        int targetSumBottomUp(vector<int> &A, int N, int targetSum){
            int totalSum = accumulate(A.begin(), A.end(), 0);
            int offset = totalSum;

            //if target sum not possible then return 0.
            if (abs(targetSum) > totalSum) 
                return 0;

            vector<vector<int>> dp(N+1, vector<int>(2 * totalSum + 1, 0));
            for(int n=0; n<=N; n++)
            {
                for(int sum=-totalSum; sum<=totalSum; sum++)
                {
                    int mappedSum = sum + offset;
                    if(n == 0 && sum == 0)
                        dp[n][mappedSum] = 1;
                    else if(n==0 && sum!=0)
                        dp[n][mappedSum] = 0; 
                    else{
                        int plus = 0, minus = 0;
                        //check if the index is within range. Why do we do this? 
                        //So that dp[][mappedSum - A[n-1]] doesnot fail
                        if(mappedSum - A[n-1] >= 0)
                            minus = dp[n - 1][mappedSum - A[n-1]];

                        //check if the index is within range. Why do we do this? 
                        //So that dp[][mappedSum + A[n-1]] doesnot fail
                        if(mappedSum + A[n-1] <= 2 * totalSum)
                            plus = dp[n - 1][mappedSum + A[n-1]];

                        dp[n][mappedSum] = plus + minus;
                    }
                }
            }

            //For debugging
            // printMatrix(dp);          
            return dp[N][targetSum + offset];
        }

    public:
        int findTargetSumWays(vector<int> &A, int targetSum) {
            int N = A.size();
            //return targetSumRecursive(A, N, 0, targetSum);

            // unordered_map<string, int> lookup;
            // return targetSumTopDown(A, N, 0, targetSum, lookup);

            return targetSumBottomUp(A, N, targetSum);
        } 
};

class Solution2{
    int findTargetSumWaysBottomUp(vector<int> &A, int target){
        int N = A.size();
        int totalSum = accumulate(A.begin(), A.end(), 0);

        // If (target + totalSum) is odd, return 0 (impossible as we cannot the array into 2 subsets)
        if((totalSum + target) %2 !=0)
            return 0;
        int targetSum = (totalSum + target) / 2;

        // If subsetSum is negative or larger than totalSum, return 0
        if (targetSum < 0 || totalSum < targetSum) 
            return 0;

        vector<vector<int>> dp(N+1, vector<int> (targetSum + 1, 0));
        for(int n=0; n<=N; n++){
            for(int sum=0; sum<=targetSum; sum++){
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

        return dp[N][targetSum];
    }
    public:
        int findTargetSumWays(vector<int> &A, int target){
            return findTargetSumWaysBottomUp(A, target);
        }
};

int main(){
    Solution1 obj1;
    vector<int> A = {1,1,1,1,1};
    cout<<obj1.findTargetSumWays(A, 3)<<endl;

    Solution2 obj2;
    cout<<obj2.findTargetSumWays(A, 3)<<endl;

    A={100};
    cout<<obj2.findTargetSumWays(A, -200)<<endl;

    return 0;
}