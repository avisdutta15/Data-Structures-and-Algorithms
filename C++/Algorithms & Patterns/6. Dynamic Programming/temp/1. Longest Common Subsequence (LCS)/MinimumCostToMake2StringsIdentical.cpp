#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    Given two strings X and Y, and two values costX and costY. 
    We need to find minimum cost required to make the given two strings identical. 
    We can delete characters from both the strings. The cost of deleting a character 
    from string X is costX and from Y is costY. Cost of removing all characters from 
    a string is same.

    Input :  X = "abcd", Y = "acdb", costX = 10, costY = 20.
    Output:  30
    For Making both strings identical we have to delete 
    character 'b' from both the string, hence cost will
    be = 10 + 20 = 30.

    Input :  X = "ef", Y = "gh", costX = 10, costY = 20.
    Output:  60
    For making both strings identical, we have to delete 2+2
    characters from both the strings, hence cost will be =
    10 + 10 + 20 + 20 = 60.
*/

/*
    Approach:
    This problem is a variation of Longest Common Subsequence ( LCS ). The idea is simple, 
    we first find the length of longest common subsequence of strings X and Y. Now subtracting 
    len_LCS with lengths of individual strings gives us number of characters to be removed to 
    make them identical.
*/

int LCS(string X, string Y){
    int M = X.length(), N = Y.length();
    int DP[M+1][N+1]={0};

    for(int i=0; i<=M; i++){
        for(int j=0; j<=N; j++){
            if(i==0 || j==0)
                DP[i][j] = 0;
            else if(X[i-1]==Y[j-1])
                DP[i][j] = DP[i-1][j-1]+1;
            else
                DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
        }
    }
    return DP[M][N];
}

int minCost(string X, string Y, int costX, int costY){

    //Find the LCS
    int lcsLength = LCS(X, Y);

    int M = X.length(), N = Y.length();
    return costX*(M-lcsLength) + 
           costY*(N-lcsLength);
}

int main(){
    string X = "ef";
    string Y = "gh";

    int costX = 10;
    int costY = 20;
    cout<<"Minimum Cost : "<<minCost(X, Y, costX, costY);
}