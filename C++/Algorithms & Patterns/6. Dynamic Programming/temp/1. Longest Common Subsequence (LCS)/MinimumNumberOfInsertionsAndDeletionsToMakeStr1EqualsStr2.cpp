#include<bits/stdc++.h>
using namespace std;

/*
    PROBLEM STATEMENT:
    -----------------
    Given two strings ‘str1’ and ‘str2’ of size m and n respectively. The task is to remove/delete 
    and insert minimum number of characters from/in str1 so as to transform it into str2.
    It could be possible that the same character needs to be removed/deleted from one point of str1 
    and inserted to some another point.

    Input : str1 = "heap", str2 = "pea" 
    Output : Minimum Deletion = 2 and
             Minimum Insertion = 1
    p and h deleted from heap
    Then, p is inserted at the beginning
    One thing to note, though p was required yet
    it was removed/deleted first from its position and
    then it is inserted to some other position.
    Thus, p contributes one to the deletion_count
    and one to the insertion_count.


    Approach:
    --------
    -->str1 and str2 be the given strings.
    -->m and n be their lengths respectively.
    -->len be the length of the longest common subsequence of str1 and str2
    -->// minimum number of deletions 
          minDel = m - len
    -->// minimum number of Insertions 
          minInsert = n - len


*/



class Solution{
    private:
        int **DP;
        int LCS(string X, string Y){
            int M = X.length();
            int N = Y.length();

            DP = new int *[M+1];
            for(int i=0; i<=M; i++){
                DP[i] = new int[N+1]();
            }

            for(int i=0; i<=M; i++){
                for(int j=0; j<=N; j++){
                    if(i==0 || j==0)
                        DP[i][j] = 0;
                    else if (X[i-1] == Y[j-1])
                        DP[i][j] = DP[i-1][j-1] + 1;
                    else    
                        DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
                }
            }
            return DP[M][N];
        }
    public:
        void minInsertionsAndDeletions(string X, string Y){
            
            int LCSlength = LCS(X, Y);

            cout<<"Number of deletions: "<<(X.length()-LCSlength);
            cout<<"\nNumber of insertions: "<<(Y.length()-LCSlength);
        }
};

int main(){
    Solution obj;
    obj.minInsertionsAndDeletions("heap", "pea");
}