#include <bits/stdc++.h>
using namespace std;

class Solution{
    int **lookup;

    int SCSRecursionUtil(string X, int M, string Y, int N){
        //if the control reaches the end of either strings
        //return the length of the other string that is remaining
        if(M==0)
            return N;
        if(N==0)
            return M;

        //if the last character of X == last character of Y then
        //call SCS(X[1...M-2], Y[1...N-2]) + 1
        if(X[M-1] == Y[N-1])
            return 1 + SCSRecursionUtil(X, M-1, Y, N-1);
        
        else
            return min(SCSRecursionUtil(X, M-1, Y, N) + 1,
                       SCSRecursionUtil(X, M, Y, N-1) + 1);
    }

    int SCSTopDownUtil(string X, int M, string Y, int N, unordered_map<string,int> &lookup){
        if(M==0 || N==0)
            return M+N;

        string key = to_string(M) + "|" + to_string(N);

        //if the key is not seen before then
        if(lookup.find(key) == lookup.end()){
            
            if(X[M-1]==Y[N-1])
                lookup[key] = SCSTopDownUtil(X, M-1, Y, N-1, lookup) + 1;
            else
                lookup[key] = min(SCSTopDownUtil(X, M-1, Y, N, lookup) + 1,
                                  SCSTopDownUtil(X, M, Y, N-1, lookup) + 1);
        }
        
        return lookup[key];
    }

    int SCSBottomUpUtil(string X, int M, string Y, int N, int **lookup){

        //initialize the lookup table
        for(int i=0; i<=M; i++)
            lookup[i][0] = i;
        
        for(int j=0; j<=N; j++)
            lookup[0][j] = j;


        //traverse the lookup and fill it up
        for(int i=1; i<=M; i++){
            for(int j=1; j<=N; j++){
                if(X[i-1] == Y[j-1])
                    lookup[i][j] = lookup[i-1][j-1] + 1;
                else
                    lookup[i][j] = min(lookup[i-1][j]+1,
                                       lookup[i][j-1]+1);
            }
        }
        return lookup[M][N];
    }

    public:
        int SCSRecursion(string X, string Y){
            int M = X.length();
            int N = Y.length();

            return SCSRecursionUtil(X, M, Y, N);
        }

        int SCSTopDown(string X, string Y){
            int M = X.length();
            int N = Y.length();
            
            unordered_map<string,int>lookup;

            return SCSTopDownUtil(X, M, Y, N, lookup);
        }

        int SCSBottomUp(string X, string Y){
            int M = X.length();
            int N = Y.length();

            lookup = new int*[M+1];
            for(int i=0; i<=M; i++)
                lookup[i] = new int[N+1]();

            return SCSBottomUpUtil(X, M, Y, N, lookup);    
        }
        
        string printSCS(string X, string Y){
            int M = X.length();
            int N = Y.length();
            
            string ans;
            int i = M, j = N;
            
            while(i>0 && j>0){
                if(X[i-1] == Y[j-1]){
                    ans.push_back(X[i-1]);
                    i--;
                    j--;
                }
                // If not same, then find the smaller of two and
                // go in the direction of smaller value
                else if(lookup[i-1][j] < lookup[i][j-1]){
                    ans.push_back(X[i-1]);
                    i--;
                }
                else{
                    ans.push_back(Y[j-1]);
                    j--;
                }
            }

            // Copy remaining characters of string 'X'
            while (i > 0){
                ans.push_back(X[i-1]);
                i--;  
            }
            
            // Copy remaining characters of string 'Y'
            while (j > 0){
                ans.push_back(Y[j-1]);
                j--; 
            }
            return ans;
        }
};

int main(){
    Solution obj;
    cout<<obj.printSCS("AGGTAB", "GXTXAYB")<<endl;
    //cout<<obj.SCSTopDown("AGGTAB", "GXTXAYB");
    //cout<<obj.SCSBottomUp("AGGTAB", "GXTXAYB");
}