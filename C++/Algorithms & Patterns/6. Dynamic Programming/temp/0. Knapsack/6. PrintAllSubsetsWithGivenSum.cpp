#include <bits/stdc++.h>
using namespace std;

/*
    Ref: https://www.youtube.com/watch?v=qtqMTgmDpQg

    ════════════════════════════════════════════════════════════════════════
    BFS ON THE 2D DP TABLE — How it works (Example)
    ════════════════════════════════════════════════════════════════════════

    A = [2, 3, 5], target = 5

    Step 1: Build the DP table (dp[n][sum] = can we form sum using first n items?)

              sum=0  sum=1  sum=2  sum=3  sum=4  sum=5
    n=0 ({}):   T      F      F      F      F      F
    n=1 ({2}):  T      F      T      F      F      F
    n=2 ({2,3}):T      F      T      T      F      T
    n=3 ({2,3,5}):T    F      T      T      F      T ← dp[3][5]=T, answer exists

    Step 2: BFS from dp[N][target] = dp[3][5]

    We start at (n=3, sum=5) and trace BACKWARDS through the table.
    At each cell (n, sum), we ask: "did we get here by INCLUDING or EXCLUDING A[n-1]?"

    - If dp[n-1][sum] == T → we could EXCLUDE A[n-1] → push (n-1, sum) to queue
    - If A[n-1] <= sum && dp[n-1][sum-A[n-1]] == T → we could INCLUDE A[n-1]
      → push (n-1, sum-A[n-1]) to queue with A[n-1] added to items

    If BOTH are true, we push BOTH paths → this gives us ALL subsets.

    BFS Trace:
    ──────────
    Queue starts: {(n=3, sum=5, items=[])}

    Pop (3, 5, []):
      A[2]=5. Check exclude: dp[2][5]=T → push (2, 5, [])
      A[2]=5. Check include: dp[2][0]=T → push (2, 0, [5])

    Pop (2, 5, []):
      A[1]=3. Check exclude: dp[1][5]=F → skip
      A[1]=3. Check include: dp[1][2]=T → push (1, 2, [3])

    Pop (2, 0, [5]):
      n=2, sum=0. Check exclude: dp[1][0]=T → push (1, 0, [5])
      A[1]=3. 3 <= 0? No → skip include.

    Pop (1, 2, [3]):
      A[0]=2. Check exclude: dp[0][2]=F → skip
      A[0]=2. Check include: dp[0][0]=T → push (0, 0, [3, 2])

    Pop (1, 0, [5]):
      n=1, sum=0. Check exclude: dp[0][0]=T → push (0, 0, [5])
      A[0]=2. 2 <= 0? No → skip include.

    Pop (0, 0, [3, 2]):
      n==0 && sum==0 → FOUND SUBSET: {3, 2}  (which sums to 5 ✓)

    Pop (0, 0, [5]):
      n==0 && sum==0 → FOUND SUBSET: {5}  (which sums to 5 ✓)

    Result: [[3, 2], [5]] ✓

    Visual on the DP table (tracing paths):
    ────────────────────────────────────────
              sum=0  sum=1  sum=2  sum=3  sum=4  sum=5
    n=0:       T                                      
    n=1:       T             T(←)                     
    n=2:       T(←)          T      T             T(START)
    n=3:                                          ↑

    Path 1 (subset {5}):  dp[3][5] → exclude A[2] → dp[2][5]
                          dp[2][5] → include A[1]=3 → dp[1][2]
                          dp[1][2] → include A[0]=2 → dp[0][0] ✓
                          Wait — this gives {3,2}. Let me redo.

    Path 1 (subset {5}):  dp[3][5] → include A[2]=5 → dp[2][0]
                          dp[2][0] → exclude A[1] → dp[1][0]
                          dp[1][0] → exclude A[0] → dp[0][0] ✓

    Path 2 (subset {3,2}): dp[3][5] → exclude A[2] → dp[2][5]
                           dp[2][5] → include A[1]=3 → dp[1][2]
                           dp[1][2] → include A[0]=2 → dp[0][0] ✓

    The BFS explores ALL valid paths through the DP table, collecting items
    along "include" edges. Each path that reaches dp[0][0] is a valid subset.

    ════════════════════════════════════════════════════════════════════════
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