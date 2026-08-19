#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
        bool subsetSum(vector<int> A, int sum1, int sum2, int sum3, vector<int> &numIndexToBucketMap, int i){
            if(i<0 && sum1==sum2==sum3)
                return true;
            if(i<0)
                return false;
            
            //include it in set1 and try.
            bool includeSetA = false;
            if(A[i]<=sum1){
                numIndexToBucketMap[i] = 1;
                includeSetA = subsetSum(A, sum1-A[i], sum2, sum3, numIndexToBucketMap, i-1);
            }
                        
            bool includeSetB = false;
            if(!includeSetA && A[i]<=sum2){
                numIndexToBucketMap[i] = 2;
                includeSetB = subsetSum(A, sum1, sum2-A[i], sum3, numIndexToBucketMap, i-1);
            }

            bool includeSetC = false;
            if(!includeSetA && !includeSetB && A[i]<=sum3){
                numIndexToBucketMap[i] = 3;
                includeSetC = subsetSum(A, sum1, sum2, sum3-A[i], numIndexToBucketMap, i-1);
            }

            return includeSetA || includeSetB || includeSetC;
        }

        void printPartitions(vector<int> A){
            int totalSum = accumulate(A.begin(), A.end(), 0);
            bool isPossible = A.size()>3 && totalSum%3==0;
            
            if(!isPossible)
                cout<<"Not Possible";
            else{
                vector<int>numIndexToBucketMap(A.size(), 0);
                int sum1 = sum2 = sum3 = totalSum/3;
                isPossible = subsetSum(A, sum1, sum2, sum3, numIndexToBucketMap, A.size()-1);

                //print the numIndexToBucketMap
                if(isPossible == true){
                    for(int i=1; i<=3; i++){
                        cout<<"\nPartition "<<i<<":"<<endl;
                        for(int j=0; j<numIndexToBucketMap.size(); j++){
                            if(numIndexToBucketMap[j]==i)
                                cout<<A[j]<<" ";
                        }
                    }
                }
            }    
        }
};

int main(){
    vector<int> A = {7, 3, 2, 1, 5, 4, 8};
    Solution obj;
    obj.printPartitions(A);
}