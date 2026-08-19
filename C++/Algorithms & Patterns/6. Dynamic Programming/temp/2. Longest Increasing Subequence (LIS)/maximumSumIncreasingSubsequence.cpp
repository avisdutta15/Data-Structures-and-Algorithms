#include <bits/stdc++.h>
using namespace std;

/*
    A = {8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11}

    sequence[0] – 8
    sequence[1] – 4
    sequence[2] – 8 12
    sequence[3] – 2
    sequence[4] – 8 10
    sequence[5] – 4 6
    sequence[6] – 8 12 14
    sequence[7] – 1
    sequence[8] – 4 6 9
    sequence[9] – 4 5
    sequence[10] – 8 12 13
    sequence[11] – 2 3
    sequence[12] – 4 6 9 11
*/


class Solution
{
    int utilNaive(vector<int> A, int i, int sum, int prev){
        if(i==A.size())
            return sum;
        
        int include = 0;
        //include this element if it is greater than the previous element
        if(A[i]>prev)
            include = utilNaive(A, i+1, sum+A[i], A[i]);
        int exclude = utilNaive(A, i+1, sum, prev);
        return max(include, exclude);
    }
    public:
        
        int maximumSumIncreasingSubsequenceNaive(vector<int> A){
            return utilNaive(A, 0, 0, INT_MIN);
        }

        int maximumSumIncreasingSubsequence(vector<int> A){
            //initialize the MISS array with the elemnts of A 
            //this is because a single element itself is an increasing
            //subsequence of length 1
            vector<int>MISS(A.begin(), A.end());
            int maxMISS = A[0];
            
            for(int i=1; i<A.size(); i++){
                for(int j=0; j<=i-1; j++){
                    if(A[i]>A[j]){
                        if(MISS[i]<MISS[j]+A[i]){
                            MISS[i] = MISS[j] + A[i];
                            maxMISS = max(MISS[i], maxMISS);
                        }
                    }
                }
            }
            return maxMISS;
        }

        void printMISS(vector<int> A){
            if(A.size()==0){
                cout<<"There is no MISS"<<endl;
                return;
            }
            vector<int>MISS(A.begin(), A.end());
            vector<int> sequence[A.size()];
            sequence[0].push_back(A[0]);
            
            int maxMISS = A[0];
            int sequenceIndex = 0;
            
            for(int i=1; i<A.size(); i++){
                for(int j=0; j<=i-1; j++){
                    if(A[i]>A[j]){
                        if(MISS[i]<MISS[j]+A[i]){
                            sequence[i] = sequence[j];
                            MISS[i] = MISS[j] + A[i];
                            maxMISS = max(MISS[i], maxMISS);
                        }
                    }
                }
                sequence[i].push_back(A[i]);
                if(maxMISS == MISS[i])
                    sequenceIndex = i;
            }

            for(int i: sequence[sequenceIndex])
                cout<<i<<" ";            
            cout<<"\nMax MISS: "<<maxMISS;
        }
};

int main(){
    Solution obj;
    
    vector<int> A = {1, 101, 2, 3, 100, 4, 5};
    obj.printMISS(A);
    
    cout<<endl;
    A = {3, 4, 5, 10};
    obj.printMISS(A);
    
    cout<<endl;
    A = {10, 5, 4, 3};
    obj.printMISS(A);
    
    return 0;
}

