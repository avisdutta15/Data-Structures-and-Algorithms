#include <bits/stdc++.h>
using namespace std;

int C(int N, int K){
    if(K==0 || K==N)
        return 1;
    else    
        return C(N-1, K-1) + C(N-1, K);
}

int BC(int N, int K){
    int C[N+1][K+1];
    for(int i=0; i<=N; i++){
        for(int j=0; j<=min(i,K); j++){
            if(j==0 || j==i)
                C[i][j] = 1;
            else
                C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
    return C[N][K];
}

int main(){
    cout<<BC(5, 3);
}