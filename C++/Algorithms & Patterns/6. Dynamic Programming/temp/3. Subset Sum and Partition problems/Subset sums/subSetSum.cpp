#define __USE_MINGW_ANSI_STDIO 0
#include <bits/stdc++.h>
using namespace std;

/*
    printing the subset:
    
    void display(vector<int> &elements){
        if(elements.size()==0){
            cout<<"No Set"<<endl;
            return;
        }
        for(int i=0; i<elements.size(); i++)
            cout<<elements[i]<<" ";
    }

    void printSubset(vector<int> A, int n, int sum, vector<vector<bool>> &lookup, vector<int> &elements){
        if(sum==0){
            display(elements);
            return;
        }
            
        if(sum<0)
            return;
        
        if(lookup[n][sum]){
            elements.push_back(A[n-1]);
            printSubset(A, n-1, sum-A[n-1], lookup, elements);
            elements.pop_back();
            printSubset(A, n-1, sum,lookup, elements);
        }
    }


    Note: This will print all the subsets.
*/



class Solution{
    private:
        unordered_map<string, bool> lookup;
        bool naiveUtil(vector<int> A, int N, int sum){
            if(sum==0)
                return true;
            if(N<0 || sum<0)
                return false;
            
            bool include = naiveUtil(A, N-1, sum-A[N]);
            bool exclude = naiveUtil(A, N-1, sum);

            return include || exclude;
        }

        bool topDownUtil(vector<int> A, int N, int sum){
            //return true if sum becomes 0
            if(sum==0)
                return true;

            //return false if sum is -ve or we run out of elements                
            if(N<0 || sum<0)
                return false;
            
            //create a key for the lookup table. Key = <A[i], Remaining sum/sum>
            //The lookup table contains the info whether we can make a subset for the sum/remaining sum
            string key = to_string(N) + "|" + to_string(sum);

            if(lookup.find(key)==lookup.end()){
                bool include = topDownUtil(A, N-1, sum-A[N]);
                bool exclude = topDownUtil(A, N-1, sum);
                lookup[key] = (include || exclude);
                return include || exclude;
            }
            return lookup[key];
        }

    public:
        bool naive(vector<int> A, int sum){
            return naiveUtil(A, A.size()-1, sum);
        }

        bool topDown(vector<int> A, int sum){
            return topDownUtil(A, A.size()-1, sum);
        }

        bool bottomUp(vector<int> A, int sum){
            //create a lookup table of size (N+1, sum+1)
            int N = A.size();
            bool lookup[N+1][sum+1];

            //fill up the table for target sum 0
            //all the elements can make a target sum 0.
            for(int i=0; i<=N; i++){
                lookup[i][0] = true;
            }

            //fill up the table for element 0.
            //0 can only make the target sum 0 but not all target sum.
            //Note: even if 0 is not there in our input set, we add it just to make computations easy
            for(int i=1; i<=sum; i++){
                lookup[0][i] = false;
            }

            for(int i=1; i<=N; i++){
                for(int j=1; j<=sum; j++){
                    //if you cannot include A[i-1] then exclude it
                    if(j-A[i-1]<0)
                        lookup[i][j] = lookup[i-1][j];
                    else //if you can include A[i-1] then check whether sum j can be achieved by including or excluding A[i-1]
                        lookup[i][j] = lookup[i-1][j-A[i-1]] || lookup[i-1][j];
                }
            }
            return lookup[N][sum];
        }
};

int main(){
    Solution obj;
    int sum = 10;
    vector<int> A = {1, 3, 9, 2};

    obj.bottomUp(A, sum)==true?cout<<"Subset exists": cout<<"Subset does not exists";

    return 0;
}
