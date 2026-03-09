//Pattern 1 : Neetcode - https://www.youtube.com/watch?v=FOyRpNUSFeA
class Solution {
private:
    void dfs(vector<int> &nums, int i, vector<int> &subset, vector<vector<int>> &result){
        if(i == nums.size()){
            result.push_back(subset);
            return;
        }

        //include
        subset.push_back(nums[i]);
        dfs(nums, i+1, subset, result);
        subset.pop_back();

        while(i+1<nums.size() && nums[i] == nums[i+1])
            i++;

        //exclude
        dfs(nums, i+1, subset, result);
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        vector<int> subset;
        dfs(nums, 0, subset, result);
        return result;
    }
};

// Pattern 2: striver
