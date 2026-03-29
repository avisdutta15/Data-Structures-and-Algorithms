#include<bits/stdc++.h>
using namespace std;

/*
    Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number 
    on it represented by array nums. You are asked to burst all the balloons. If 
    the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. 
    Here left and right are adjacent indices of i. After the burst, the left and 
    right then becomes adjacent.

    Find the maximum coins you can collect by bursting the balloons wisely.
    Note: 
    (1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
    (2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
    
    Example:
    Given [3, 1, 5, 8]
    Return 167
    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
    coins =  3*1*5   +  3*5*8 +  1*3*8   + 1*8*1   = 167

Approach
    max_coins = 0
    for every balloons[i] in balloons:
        burst its left part
        burst its right part
        burst balloons[i] after all other balloons are bursted
        coins = add up all the coins gained in this process
        if max_coins < coins:
            max_coins = coins
    return max_coins


    Pay attention to the bursting at x between i and j. X should be considered as 
    the last one to burst, otherwise (if it is the first one to be burst) it will 
    affect the result for [I,x-1], and [I,x+1], as the adjacent balloons will change 
    after x is burst. For example balloon at x-1 and x+1 will become adjacent. So 
    let x be the last one to be burst will void this problem.
*/


class Solution {
    public:
        int maxCoins(vector<int>& nums){
            nums.insert(nums.begin(),1);
            nums.push_back(1);
            return SolveDP(nums,1,nums.size()-2);
        }

        int SolveDP(vector<int>& nums, int i, int j){
            if(i>j)
                return 0;

            int maxCoinCollectedWithAvailableBallons = 0;
            for(int x=i; x<=j; x++){
                int coinsByBurstingXAtLast = nums[i-1]*nums[x]*nums[j+1];
                coinsByBurstingXAtLast += SolveDP(dp, nums, i, x-1);
                coinsByBurstingXAtLast += SolveDP(dp, nums, x+1, j);
                
                if(maxCoinCollectedWithAvailableBallons< coinsByBurstingXAtLast)
                    maxCoinCollectedWithAvailableBallons = coinsByBurstingXAtLast;
            }
            return maxCoinCollectedWithAvailableBallons;
        }
};

class Solution2{
    public:
        int maxCoins(vector<int>& nums){
            nums.insert(nums.begin(),1);
            nums.push_back(1);
            vector<vector<int>> dp(nums.size(),vector<int>(nums.size(),0));
            return SolveDP(dp,nums,1,nums.size()-2);
        }

        int SolveDP(vector<vector<int>> &dp, vector<int>& nums, int i, int j){
            if(i>j)
                return 0;
            if(dp[i][j]>0)
                return dp[i][j];

            int maxCoinCollectedWithAvailableBallons = 0;
            for(int x=i; x<=j; x++){
                int coinsByBurstingXAtLast = nums[i-1]*nums[x]*nums[j+1];
                coinsByBurstingXAtLast += SolveDP(dp, nums, i, x-1);
                coinsByBurstingXAtLast += SolveDP(dp, nums, x+1, j);
                
                if(maxCoinCollectedWithAvailableBallons< coinsByBurstingXAtLast)
                    maxCoinCollectedWithAvailableBallons = coinsByBurstingXAtLast;
            }
            return dp[i][j] = maxCoinCollectedWithAvailableBallons;
        }
};

/*
    Use a length variable to control the length of the bursting balloons. 
    Begin with length 1, and continue until it reaches to length of n.
*/

class Solution3{
    public:
        int maxCoins(vector<int>& nums){
            int numLen = nums.size();
            nums.insert(nums.begin(),1);
            nums.push_back(1);
            vector<vector<int>> dp(nums.size(),vector<int>(nums.size(),0));

            for(int K=1; K<=numLen; K++){
                int maxCoinCollectedWithAvailableBallons = 0;
                
                for(int left=1; left<=numLen+1-K; left++){
                    int right = left + K - 1;

                    for(int x=left; x<=right; x++){
                        int coinsByBurstingXAtLast = nums[left-1]*nums[x]*nums[right+1];
                        dp[left][right] = max(dp[left][right], dp[left][x-1] + coinsByBurstingXAtLast + dp[x+1][right]);
                    }
                }
            }
            return dp[1][numLen];
        }
};

int main(){
    vector<int> A = {3,1,5,8};
    Solution obj;
    cout<<obj.maxCoins(A);
}