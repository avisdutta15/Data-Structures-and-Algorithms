#include <bits/stdc++.h>
using namespace std;

/*

    dims[] = {4, 10, 3, 12, 20, 7};
    This means we have 5 matrices. 
    M1 = 4  x 10
    M2 = 10 x 3
    M3 = 3  x 12
    M4 = 12 x 20
    M5 = 20 x 7

    We start i=1 to denote M1. M1 has dims[i-1] and dims[i].
    Now lets analyse for 2 matrices. M1 and M2.
    We put a bracket at i=1 to get (M1)M2 and recur for 

    DP Matrix

    0	0	0	0	0	  0	
    0	0	120	264	1080  1344	
    0	0	0	360	1320  1350	
    0	0	0	0	720	  1140	
    0	0	0	0	0	  1680	
    0	0	0	0	0	  0


*/

/*Naive*/
class Solution1{
    public:
        int matrixChainOrderUtil(vector<int> &dims, int i, int j){
            if(i==j)
                return 0;
            
            int minCost = INT_MAX;
            for(int K = i; K<j; K++){
                int costIfWePlaceABracketAtK = matrixChainOrderUtil(dims, i, K) + 
                                               matrixChainOrderUtil(dims, K+1, j) + 
                                               (dims[i-1]*dims[K]*dims[j]);
                minCost = min(minCost, costIfWePlaceABracketAtK);
            }
            return minCost;
        }

        int matrixChainOrder(vector<int> dims){
            int N = dims.size()-1; //number of matrices.
            int i = 1;
            int j = N;
            return matrixChainOrderUtil(dims, i, j);
        }
};

/*Top Down*/
class Solution2{
    public:
        int matrixChainOrderUtil(vector<int> &dims, int i, int j, unordered_map<string, int> &lookup){
            string key = to_string(i)+" "+to_string(j);
            
            if(i==j)
                return lookup[key] = 0;
            
            if(lookup.count(key)>0)
                return lookup[key];

            int minCost = INT_MAX;
            for(int K = i; K<j; K++){
                int costIfWePlaceABracketAtK = matrixChainOrderUtil(dims, i, K, lookup) + 
                                               matrixChainOrderUtil(dims, K+1, j, lookup) + 
                                               (dims[i-1]*dims[K]*dims[j]);
                minCost = min(minCost, costIfWePlaceABracketAtK);
            }

            return lookup[key] = minCost;
        }

        int matrixChainOrder(vector<int> dims){
            int N = dims.size()-1; //there are dims.size()-1 matrics indexed 1 to N.
            int i = 1;
            int j = N;
            unordered_map<string, int> lookup;
            return matrixChainOrderUtil(dims, i, j, lookup);
        }
};


class Solution3{
    public:
        int matrixChainOrder(vector<int> dims){
            int N = dims.size()-1;  //N is the number of matrices which is 1 less than dims.size()
                                    //M1 * M2   2 matrices but 3 orders
                                    //M1.....MN

            
            vector<vector<int>> DP(N+1, vector<int> (N+1, 0));   //DP[i][j] represents the min cost to multiply matrices from i to j
            vector<vector<int>> brackets(N+1, vector<int> (N+1, 0));
                        
            //Calculating for chain length more than 1
            for(int cu rr_len=2; curr_len<=N; curr_len++){
                for(int i=1; i<=N-curr_len+1; i++){
                    
                    int j = i + curr_len - 1;
                    DP[i][j] = INT_MAX;
                    
                    for(int k=i; k<j; k++){
                        int costIfWePlaceABracketAtK = DP[i][k]+DP[k+1][j]+(dims[i-1]*dims[k]*dims[j]);
                        if(costIfWePlaceABracketAtK < DP[i][j]){
                            DP[i][j] = costIfWePlaceABracketAtK;
                            brackets[i][j] = k;
                        }
                    }
                }
            }
                        
            for(int i=0; i<=N; i++){
                for(int j=0; j<=N; j++)
                    cout<<DP[i][j]<<"\t";
                cout<<endl;
            }
            
            printBrackets(brackets, 1, N);

            //return the minCost to multiply matrices M1 to MN.
            return DP[1][N]; 
        }

        void printBrackets(vector<vector<int>> &brackets, int i, int j){
            if(i==j){
                cout<<"A" + i;
                return;
            }

            cout<<"(";
            printBrackets(brackets, i, brackets[i][j]);   //i.....K
            printBrackets(brackets, brackets[i][j]+1, j); //K+1...j
            cout<<")";
        }
};

int main(){
    Solution1 obj1;
    Solution2 obj2;
    Solution3 obj3;

    vector<int> dims = {4, 10, 3, 12, 20, 7};
    cout<<obj1.matrixChainOrder(dims)<<endl;
    cout<<obj2.matrixChainOrder(dims)<<endl;
    cout<<obj3.matrixChainOrder(dims)<<endl;
}