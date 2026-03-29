#include <bits/stdc++.h>
using namespace std;

/*
    Cut the rod of given length N, into lengths from 1 to N.
    Here we can reuse the lengths.
    It is an exact replica of unbounded knapsack problem
*/

class Solution1{
    public:
        int rodCut(vector<int> &price, int rodLength){
            if(rodLength<=0)
                return 0;
            
            int maxProfit = INT_MIN;

            // one by one partition the given rod of length n into two parts
            // of length (1, n-1), (2, n-2), (3, n-3), .... (n-1 , 1), (n, 0)
            // and take maximum
            for(int i=1; i<=rodLength; i++){

                // rod of length i has a cost price[i-1]
                int costOfCuttingTheRodAtI = price[i-1] + rodCut(price, rodLength-1);
                
                maxProfit = max(maxProfit, costOfCuttingTheRodAtI);
            }
            return maxProfit;
        }
};

class Solution2{
    public:
        int rodCutUtil(vector<int> &price, int rodLength, unordered_map<int, int> &lookup){
            if(rodLength<=0)
                return lookup[rodLength] = 0;
            
            if(lookup.find(rodLength)!=lookup.end())
                return lookup[rodLength];

            int maxProfit = INT_MIN;

            // one by one partition the given rod of length n into two parts
            // of length (1, n-1), (2, n-2), (3, n-3), .... (n-1 , 1), (n, 0)
            // and take maximum
            for(int i=1; i<=rodLength; i++){

                // rod of length i has a cost price[i-1]
                int costOfCuttingTheRodAtI = price[i-1] + rodCutUtil(price, rodLength-1, lookup);
                
                maxProfit = max(maxProfit, costOfCuttingTheRodAtI);
            }
            return lookup[rodLength] = maxProfit;
        }

        int rodCut(vector<int> &price, int rodLength){
            unordered_map<int, int> lookup;
            return rodCutUtil(price, rodLength, lookup);
        }
};

class Solution3{
    public:
        int rodCut(vector<int> &price, int rodLength){
            int N = rodLength;

            // T[i] stores maximum profit achieved from rod of length i
            int DP[N+1];

            // initialize maximum profit to 0
            for(int i=0; i<=N; i++)
                DP[i] = 0;
            
            // consider rod of length i
            for(int i=1; i<=N; i++){

                // divide the rod of length i into two rods of length j
		        // and i-j each and take maximum
                for(int j=1; j<=i; j++){
                    DP[i] = max(DP[i], price[j-1]+DP[i-j]);
                }
            }
            return DP[N];
        }
};

int main(){
    vector<int> price = { 1, 5, 8, 9, 10, 17, 17, 20 };
    int rodLength = 4;

    Solution1 obj1;
    cout<<obj1.rodCut(price, rodLength)<<endl;

    Solution2 obj2;
    cout<<obj2.rodCut(price, rodLength)<<endl;
}