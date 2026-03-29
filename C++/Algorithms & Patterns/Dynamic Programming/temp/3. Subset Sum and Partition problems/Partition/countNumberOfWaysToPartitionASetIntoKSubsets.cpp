#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    -----------------
    Given two numbers n and k where n represents number of elements in a set, 
    find number of ways to partition the set into k subsets.
    
    Input: n = 3, k = 2
    Output: 3
    Explanation: Let the set be {1, 2, 3}, we can partition
                 it into 2 subsets in following ways
                 {{1,2}, {3}},  {{1}, {2,3}},  {{1,3}, {2}}  
    
    Input: n = 3, k = 1
    Output: 1
    Explanation: There is only one way {{1, 2, 3}}
    
    Analysis and Solution:
    ---------------------
    When we add a (n+1)’th element to k partitions, there are two possibilities.
    1) It is added as a single element set to existing partitions, i.e, S(n, k-1)
    2) It is added to all sets of every partition, i.e., k*S(n, k)
    
    Therefore S(n+1, k) = k*S(n, k) + S(n, k-1) 
    which means 
              S(n, k) = k*S(n-1, k) + S(n-1, k-1)  -> S(n, k) is called Stirling numbers of the second kind

    
    Overlapping subproblems:
            CP(10,7)
           /        \
       CP(9,7)       CP(9,6) 
       /    \       /    \
  CP(8,7) CP(8,6) CP(8,6)  CP(8,5)
    / \    / \     / \       / \
*/


class Solution{
    unordered_map<string, int> lookup;
    public:
        int countWays2PartitionAsetIntoKSubsets(int n, int k){
            
            //Base Case:
            //If numbers = 0 or numberOfSubsets = 0 then return 0.
            //If numberOfSubsets > numbers then not possible.
            //e.g. divide {1,2,3} into 4 subsets. Not possible
            if(n==0 || k==0 || k>n)
                return 0;
                
            //Base Case:
            //If If numbers = 1 or numberOfSubsets = 1 then return 1
            //e.g. {1}. Divide it into 1 subset. only 1 way possible.
            //e.g. {1,2}. Divide it into 1 subset. only 1 way possible {1,2}.
            if(n==1 || k==1)
                return 1;
            return countWays2PartitionAsetIntoKSubsets(n-1, k-1) + 
                   k*countWays2PartitionAsetIntoKSubsets(n-1, k);
        }
        
        int countWays2PartitionAsetIntoKSubsetsDP(int n, int k){
            //Base Case:
            //If numbers = 0 or numberOfSubsets = 0 then return 0.
            //If numberOfSubsets > numbers then not possible.
            //e.g. divide {1,2,3} into 4 subsets. Not possible
            if(n==0 || k==0 || k>n)
                return 0;
                
            //Base Case:
            //If If numbers = 1 or numberOfSubsets = 1 then return 1
            //e.g. {1}. Divide it into 1 subset. only 1 way possible.
            //e.g. {1,2}. Divide it into 1 subset. only 1 way possible {1,2}.
            if(n==1 || k==1)
                return 1;
            
            string key = to_string(n) + '|' + to_string(k);
            if(lookup.find(key)==lookup.end()){
                lookup[key] = countWays2PartitionAsetIntoKSubsetsDP(n-1, k-1) + 
                              k*countWays2PartitionAsetIntoKSubsetsDP(n-1, k);
            }
            return lookup[key];
        }

};

int main(){
    Solution obj;
    int n = 3, k = 2;
    cout<<obj.countWays2PartitionAsetIntoKSubsets(n, k)<<endl;
    cout<<obj.countWays2PartitionAsetIntoKSubsetsDP(n, k);
    
    return 0;
}