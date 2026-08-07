#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	You are given an integer array nums and an integer target.

	You want to build an expression out of nums by adding one of the symbols '+' and '-' 
	before each integer in nums and then concatenate all the integers.

	For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and 
	concatenate them to build the expression "+2-1".
	Return the number of different expressions that you can build, which evaluates to target.


	Examples:
	---------
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


	Approach 1: Global Total Ways
	-----------------------------
	Include and exclude


	Approach 2: Each function call returns the total ways from that subtree
	------------------------------------------------------------------------

	Approach 3: Each function call returns the total ways from that subtree + Memoization
	-------------------------
	nums = [a, b, c].

	Here is the corresponding recursion tree:

	├── (+a)
	│   ├── (+b)^
	│   │   ├── (+c)
	│   │   └── (-c)
	│   └── (-b)~
	│       ├── (+c)
	│       └── (-c)
	└── (-a)
		├── (+b)^
		│   ├── (+c)
		│   └── (-c)
		└── (-b)~
			├── (+c)
			└── (-c)

	As illustrated, the subtrees marked by ^ and ~ are solved twice.
	To avoid this redundancy, we introduce a memoization table (a 2D array) 
	where memo[index][currentSum] stores the number of ways to reach the target starting 
	from the index with the currentSum.

	Approach 4 : Optimized to Subset Sum
	------------------------------------
	As a bonus, the most optimal way to solve this specific problem is by mathematically turning it 
	into a "Subset Sum" problem.
	If P is the subset of positive numbers and N is the subset of negative numbers:
		Sum(P) + (-Sum(N)) = target
		Sum(P) - Sum(N) = target
		Sum(P) + Sum(N) = total_sum
		-----------------------------
		Adding the above eqs:
		2 * Sum(P) = target + total_sum
		=>  Sum(P) = (target + total_sum) / 2.

	This proves that you only need to :
		find the number of ways to pick a subset of numbers that adds up strictly to (target + total_sum) / 2.

	Below is a recap of subset sum:
	-------------------------------
	recursive(A, n, target)
		// if no elements left and target sum = 0 then return 1 as 1 subset can be created. {}
		if (n == 0 && target == 0)
			return 1;
		// if there is no elements and target sum !=0 then return 0 meaning no subset can be created.
		if n == 0 && target != 0
			return 0;
		
		include = recursive(A, n-1, target - A[n-1]);
		exclude = recursive(A, n-1, target);
		return include + exclude

	bottom_up(A, n, target)
		DP(N+1, vector<int>(target+1, 0));

        for(int n=0; n<=N; n++){
            for(int sum=0; sum<=target; sum++){
                if(n == 0 && sum == 0)
                    dp[n][sum] = 1;
                else if(n == 0 && sum!=0)
                    dp[n][sum] = 0;
                else{
                    bool include = 0, exclude = 0;
                    if(A[n-1]<=sum){
                        include = dp[n-1][sum-A[n-1]];
                    }
                    exclude = dp[n-1][sum];
                    dp[n][sum] = include + exclude;
                }
            }
        }
        
        return dp[N][target];


	We will use this bottom up approach.
		Target Sum now boils down to 
			Find the number of subsets in nums whose sum equals S = (target + total_sum)/2.

		total_sum = SUM(A[0..N])
		base case 1: 
			if target > total_sum
				return 0;	// not possible to achieve target
		SumOfPositives = (target + total_sum)/2;		based on the above equations.
		base case 2:
			the SumOfPositives must be even and non-negative. Why?
				If target + total_sum is an odd number, dividing it by 2 will result in a fraction.
				Example: Let's say the total sum of your array is 5 and your target is 2.
				5 + 2 = 7$$7 / 2 = 3.5
				Since it is impossible to pick a combination of whole numbers that add up to exactly 3.5
				there are 0 ways to reach the target.
			
			In this specific problem (LeetCode 494: Target Sum), the array nums only contains non-negative 
			integers (0 and positive numbers).
			Because of this, the sum of any subset you pick (Sum(P)) can never be less than zero.
				- If target + total_sum results in a negative number, dividing it by 2 would mean Sum(P) is negative.
				- Since you cannot add positive numbers and zeros together to get a negative subset sum, this scenario 
				is structurally impossible, so there are 0 ways.
			
			if (target + total_sum) % 2 != 0  ||  (target + total_sum) < 0
				return 0;

			targetSum = SumOfPositives = (target + total_sum)/2;
			now bottomup DP for subset sum with targetSum
			
*/

// Keep a global total_ways + include / exclude
class Solution1{
private:
	void calculateWays(const vector<int>& nums, int i, int current_subset_sum, int target, int &total_ways){
		if(i == nums.size()){
			if(current_subset_sum == target)
				total_ways++;
			return;
		}

		// include +
		calculateWays(nums, i+1, current_subset_sum + nums[i], target, total_ways);
		// include -
		calculateWays(nums, i+1, current_subset_sum - nums[i], target, total_ways);
	}

public:
	int findTargetSumWays(vector<int>& nums, int target) {
		int i = 0;
		int current_subset_sum = 0;
		int total_ways = 0;
		calculateWays(nums, i, current_subset_sum, target, total_ways);
		return total_ways;
	}
};

// instead of a global total ways, let the leaf node of 
// recursion return the result. if successful, then that leaf returns 1 else returns 0
class Solution2 {
private:
	int calculateWays(vector<int>& nums, int i, int current_subset_sum, int& target) {
		//exhausted all the elements
		if (i == nums.size()) {
			// if target sum == current_subset_sum
			if (current_subset_sum == target)
				return 1;
			else if (current_subset_sum != target)
				return 0;
		}

		//include +
		int plus = calculateWays(nums, i + 1, current_subset_sum + nums[i], target);

		//include -
		int minus = calculateWays(nums, i + 1, current_subset_sum + (-nums[i]), target);

		//return total ways from this node
		return plus + minus;
	}

public:
	int findTargetSumWays(vector<int>& nums, int target) {
		int i = 0;
		int current_subset_sum = 0;

		return calculateWays(nums, i, current_subset_sum, target);
	}
};

// Memoization
class Solution3{
private:
	int calculateWays(vector<int>& nums, int i, int current_subset_sum, int& target, vector<vector<int>> &waysCache, int &total_sum) {
		//exhausted all the elements
		if (i == nums.size()) {
			// if target sum == current_subset_sum
			if (current_subset_sum == target)
				return waysCache[i][current_subset_sum + total_sum] = 1;
			else if (current_subset_sum != target)
				return waysCache[i][current_subset_sum + total_sum] = 0;
		}
		
		// if cache is not empty
		if (waysCache[i][current_subset_sum + total_sum] != -1){
			return waysCache[i][current_subset_sum + total_sum];
		}

		//include +
		int plus = calculateWays(nums, i + 1, current_subset_sum + nums[i], target, waysCache, total_sum);

		//include -
		int minus = calculateWays(nums, i + 1, current_subset_sum + (-nums[i]), target, waysCache, total_sum);

		//return total ways from this node
		return waysCache[i][current_subset_sum + total_sum] = plus + minus;
	}

public:
	int findTargetSumWays(vector<int>& nums, int target) {
		int i = 0;
		int current_subset_sum = 0;
		int total_sum = accumulate(nums.begin(), nums.end(), 0);
		int N = nums.size();
		vector<vector<int>> waysCache (N+1, vector<int>(2 * total_sum + 1, -1));

		// Why 2 * total_sum + 1 in waysCache[N+1][2 * total_sum + 1]?
		// maximum bound of the current_subset_sum is : -total_sum to +total_sum
		// Since current_subset_sum can become negative, we cannot have a -ve index in array
		// to make that +ve, we will do current_subset_sum + total_sum
		// So the +ve sums will also be current_subset_sum + total_sum
		// Hence 2 * total_sum + 1

		return calculateWays(nums, i, current_subset_sum, target, waysCache, total_sum);
	}
};

class Solution4{
private:
public:
	int findTargetSumWays(vector<int> &A, int target){
		int total_sum = accumulate(A.begin(), A.end(), 0);

		// Edge Case 1: Target is impossible if its absolute value exceeds total_sum
		if (target > total_sum)
			return 0;
		
		// Edge Case 2: (target + total_sum) must be non-negative and even.
		if( (target + total_sum) % 2 != 0 || (target + total_sum) < 0)
			return 0;
		
		// The target subset sum we need to find
		int targetSubsetSum = (target + total_sum) / 2;
        int N = A.size();

		vector<vector<int>> DP(N+1, vector<int>(targetSubsetSum+1, 0));

		for(int n = 0; n<= N; n++){
			for(int sum = 0; sum <= targetSubsetSum; sum++){
				if (n == 0 && sum == 0)
					DP[n][sum] = 1;
				else if (n == 0 && sum != 0)
					DP[n][sum] = 0;
				else{
					int include = 0, exclude = 0;
					if(A[n-1] <= sum)
						include = DP[n-1][sum - A[n-1]];
					exclude = DP[n-1][sum];
					DP[n][sum] = include + exclude;
				}
			}
		}

		// return the number of subsets possible with
		// N numbers and target sum = targetSubsetSum
		return DP[N][targetSubsetSum];
	}
};



int main() {
	Solution obj;
	vector<int> A = { 1,1,1,1,1 };
	cout << obj.findTargetSumWays(A, 3);
}
