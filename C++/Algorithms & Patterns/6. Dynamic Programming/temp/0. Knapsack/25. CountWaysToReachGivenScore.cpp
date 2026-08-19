#include <bits/stdc++.h>
using namespace std;

/*
    Consider a game where players can score 3, 5, or 10 points in a move. 
    Given a total score of n, the task is to find the number of ways to 
    reach the given score.

    Examples: 
    Input: n = 20
    Output: 4
    Explanation: There are following 4 ways to reach 20: (10, 10), (5, 5, 10), 
    (5, 5, 5, 5), (3, 3, 3, 3, 3, 5)

    Input: n = 13
    Output: 2
    Explanation: There are following 2 ways to reach 13: (3, 5, 5), (3, 10)

Approach:
    The given problem is a variation of the coin change problem.
    The idea is to use a recursive function that explores all possible combinations of 
    scoring points by making choices at each step. For each point value (3, 5, or 10), 
    we have two options: either take that point value or skip it. The function will 
    recursively explore these choices. When the total score reaches exactly 0, we count 
    it as a valid combination and if it goes below 0, return 0.
*/

class Solution{
    int countWaysToReachScoreRecursive(vector<int> &points, int totalScore, int N){
        if(N==0 && totalScore==0)
            return 1;
        if(N==0 && totalScore!=0)
            return 0;

        int include = 0, exclude = 0;
        if(points[N-1]<=totalScore)
            include = countWaysToReachScoreRecursive(points, totalScore-points[N-1], N);
        exclude = countWaysToReachScoreRecursive(points, totalScore, N-1);
        return include + exclude;
    }

    int countWaysToReachScoreTopDown(vector<int> &points, int totalScore, int N, unordered_map<string, int> &lookup){
        if(N==0 && totalScore==0)
            return 1;
        if(N==0 && totalScore!=0)
            return 0;

        string key = to_string(N) + " " + to_string(totalScore);
        if(lookup.find(key)!=lookup.end())
            return lookup[key];

        int include = 0, exclude = 0;
        if(points[N-1]<=totalScore)
            include = countWaysToReachScoreTopDown(points, totalScore-points[N-1], N, lookup);
        exclude = countWaysToReachScoreTopDown(points, totalScore, N-1, lookup);
        return lookup[key] = include + exclude;
    }

    int countWaysToReachScoreBottomUp(vector<int> &points, int totalScore, int N){
        vector<vector<int>> dp(N+1, vector<int>(totalScore + 1, 0));

        for(int n=0; n<=N; n++){
            for(int score = 0; score <= totalScore; score++){
                if(n==0 && score==0)
                    dp[n][score] = 1;
                else if(n==0 && score!=0)
                    dp[n][score] = 0;
                else{
                    int include = 0, exclude = 0;
                    if(points[n-1]<=score)
                        include = dp[n][score-points[n-1]];
                    exclude = dp[n-1][score];
                    dp[n][score] = include + exclude;
                }                
            }
        }
        return dp[N][totalScore];
    }

    public:
        int countWaysToReachScore(int n){
            vector<int> points = {3, 5, 10};
            int totalScore = n;
            int N = points.size();
            // return countWaysToReachScoreRecursive(points, totalScore, N);

            // unordered_map<string, int> lookup;
            // return countWaysToReachScoreTopDown(points, totalScore, N, lookup);

            return countWaysToReachScoreBottomUp(points, totalScore, N);
        }
};


int main(){
    Solution obj;
    cout<<obj.countWaysToReachScore(20)<<endl;  //4
    cout<<obj.countWaysToReachScore(13)<<endl;  //2
}