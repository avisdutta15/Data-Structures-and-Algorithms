#include <bits/stdc++.h>
using namespace std;

/*
    Partition problem is to determine whether a given set can be partitioned into 
    two subsets such that the sum of elements in both subsets is same.
    Example:
        arr[] = {1, 5, 11, 5}
        Output: true 
        The array can be partitioned as {1, 5, 5} and {11}
    
    Approach:
        Maintain 2 sets. set1 and set2.
        First try to include A[i] to set1 and recurse for the rest of the elements.
        If by including A[i] into set1 we can reach to a solution where sum1==sum2 then return true.

        Else remove A[i] from set1.
        Include A[i] to set2 and recurse for the rest of the elements.
        If by including A[i] into set2 we can reach to a solution where sum1==sum2 then return true.
        else return false.

        base case: when both the sum (sum of set1 and sum of set2 becomes equal)
                   and there are no more elements left to include then print the 2 sets are retrun true.
                   Else if both the sums are not same and there are no more elements left to include then return false.
*/


class Solution{
    bool subsetSum(vector<int> A, int sum, int i){
        if(sum==0)
            return true;
        if(i<0 || sum<0)
            return false;
        
        bool include = false;
        if(sum-A[i]>=0)
            include = subsetSum(A, sum-A[i], i-1);
        bool exclude = subsetSum(A, sum, i-1);
        return include||exclude;
    }
    public:
        bool isPartitionPossible(vector<int> A){
            int N = A.size();
            if(N==0)
                return false;
            int sum = accumulate(A.begin(), A.end(), 0);
            if(sum%2!=0)
                return false;
            return subsetSum(A, sum/2, N-1);
        }

        void printSubsets(vector<int> s1, vector<int> s2){
            cout<<"\nSet 1: \n";
            for(int i: s1)
                cout<<i<<" ";
            cout<<"\nSet 2: \n";
            for(int i: s2)
                cout<<i<<" ";
        }

        bool printEqualSumSubsetsUtil(vector<int> A, int sum1, int sum2, vector<int> set1, vector<int> set2, int i){
            if(i==-1){
                if(sum1==sum2){
                    printSubsets(set1, set2);
                    return true;
                }else   
                    return false;
            }
            if(i<-1)
                return false;
            
            set1.push_back(A[i]);
            bool includeSet1 = printEqualSumSubsetsUtil(A, sum1+A[i], sum2, set1, set2, i-1);

            if(includeSet1==true)
                return true;
            
            //exclude from set1 and include in set2
            set1.pop_back();
            set2.push_back(A[i]);

            bool includeSet2 = printEqualSumSubsetsUtil(A, sum1, sum2+A[i], set1, set2, i-1);
            return includeSet2;
        }

        void printEqualSumSubsets(vector<int> A){
            int N = A.size();
            if(N==0){
                cout<<"\nEqual Sum subsets doesnot exist";
                return;
            }
            int sum = accumulate(A.begin(), A.end(), 0);
            if(sum%2!=0){
                cout<<"\nEqual Sum subsets doesnot exist";
                return;
            }
            int sum1 = 0;
            int sum2 = 0;
            vector<int>set1, set2;
            return printEqualSumSubsetsUtil(A, sum1, sum2, set1, set2, N-1);
        }
};

int main()
{
    vector<int> A = {1, 5, 11, 5};
    Solution obj;
    obj.isPartitionPossible(A)==true?cout<<"\nPossible":cout<<"\nNot Possible";

    cout<<endl;

    obj.printEqualSumSubsets(A);

    return 0;
}
