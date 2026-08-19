#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    Given a string, find the length of the longest repeating subsequence such 
    that the two subsequences don’t have same string character at the same 
    position, i.e., any i’th character in the two subsequences shouldn’t have 
    the same index in the original string.

    str = AABB
    O/p = AB
    Explanation:               0 1 2 3
                        seq1 = A A B B
                        seq2 = A A B B
    Here the repeating seq can be A(0)B(1) or A(1)B(2)


*/

class Solution{
    private:
        int **DP;
        int M, N;
        string X;
        int modifiedLCS(string X, int M, string Y, int N){
            this->M = M;
            this->N = N;
            
            //allocate memory for rows
            DP = new int *[M+1];

            //allocate memory for each column
            for(int i=0; i<=M; i++)
                DP[i] = new int [N+1];

            for(int i=0; i<=M; i++){
                for(int j=0; j<=N; j++){
                    if(i==0 || j==0)
                        DP[i][j] = 0;
                    else if(X[i-1] == Y[j-1] && i!=j)
                        DP[i][j] = 1 + DP[i-1][j-1];
                    else
                        DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
                }
            }
            return DP[M][N];
        }
    public:
        int LRSLength(string X){
            this->X = X;
            string Y = X;
            return modifiedLCS(X, X.length(), Y, Y.length());
        }

        string printLRS(){
            int index = DP[M][N];
            int i=M, j=N;
            string ans;
            while(i>0 && j>0){
                if(X[i-1] == X[j-1] && i!=j){
                    ans.push_back(X[i-1]);
                    i--;
                    j--;
                }else if(DP[i-1][j] > DP[i][j-1])
                    i--;
                else
                    j--;
            }
            reverse(ans.begin(), ans.end());
            return ans;
        }
};

int main(){
    Solution obj;
    string input1 = "ATACTCGGA";
    cout<<obj.LRSLength(input1)<<endl;
    cout<<obj.printLRS()<<endl;
    
    input1 = "abc";
    cout<<obj.LRSLength(input1)<<endl;
    cout<<obj.printLRS()<<endl;
    
    input1 = "aab";
    cout<<obj.LRSLength(input1)<<endl;
    cout<<obj.printLRS()<<endl;
    
    input1 = "aabb";
    cout<<obj.LRSLength(input1)<<endl;
    cout<<obj.printLRS()<<endl;
    
    input1 = "axxxy";
    cout<<obj.LRSLength(input1)<<endl;
    cout<<obj.printLRS()<<endl;
}
