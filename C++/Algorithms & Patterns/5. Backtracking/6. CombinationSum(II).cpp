#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//Pattern 1 : Neetcode - https://www.youtube.com/watch?v=FOyRpNUSFeA
class Solution {
    void dfs(vector<int>& candidates, int i, vector<int> &combination, vector<vector<int>> &result, int target){
        if(target == 0){
            result.push_back(combination);
            return;
        }

        if(target < 0 || i>=candidates.size())
            return;

        //include
        if(target - candidates[i]>=0)
        {
            combination.push_back(candidates[i]);
            target = target - candidates[i];
            dfs(candidates, i+1, combination, result, target);
            combination.pop_back();
            target = target + candidates[i];
        }

        //exclude
        while(i+1 < candidates.size() && candidates[i] == candidates[i+1])
            i++;
        dfs(candidates, i+1, combination, result, target); 
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        vector<int> combination;
        dfs(candidates, 0, combination, result, target);
        return result;
    }
};

//Pattern 2: striver https://www.youtube.com/watch?v=G1fRTGRxXU8&list=PLgUwDviBIf0rGlzIn_7rsaR2FQ5e6ZOL9&index=11
class Solution {
    void dfs(vector<int>& candidates, int idx, vector<int> &combination, vector<vector<int>> &result, int target){
        //if reached target then save this combination
        if(target == 0){
            result.push_back(combination);
            return;
        }

        //if target or index is out of bounds
        if(target < 0 || idx>=candidates.size())
            return;

        for(int i=idx; i<candidates.size(); i++){
            //if target is possible to achieve?
            if(target - candidates[i] < 0)
                break;
            
            if(i!=idx && candidates[i] == candidates[i-1])
                continue;
            
            combination.push_back(candidates[i]);
            target = target - candidates[i];
            dfs(candidates, i+1, combination, result, target);
            combination.pop_back();
            target = target + candidates[i];
        }
        
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        //sort the candidates
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        vector<int> combination;
        dfs(candidates, 0, combination, result, target);
        return result;
    }
};