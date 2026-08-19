#include <bits/stdc++.h>
using namespace std;

/*
    Given N elements, write a program that prints the length of the longest increasing 
    subsequence whose adjacent element difference is one.

    Examples:
    Input : a[] = {3, 10, 3, 11, 4, 5, 6, 7, 8, 12}
    Output : 6
    Explanation: 3, 4, 5, 6, 7, 8 is the longest increasing subsequence whose 
    adjacent element differs by one.
*/

class Solution{
    public:
        int LICS(vector<int> A){
            if(A.size()==0)
                return 0;
            
            vector<int> DP(A.size(), 1);

            for(int i=1; i<A.size(); i++){
                for(int j=0; j<i; j++){
                    if(A[j]+1 == A[i]){
                        if(DP[j]+1 > DP[i])
                            DP[i] = DP[j]+1;
                    }
                }
            }

            return *max_element(DP.begin(), DP.end());
        }
};

//In the above solution, all we are doing is searching the A[j] such that A[j]+1 = A[i].
//We can reduce the search time and make it O(1) using a hash map.
class Solution2{
    public:
        int LICS(vector<int> A){
            if(A.size()==0)
                return 0;
            
            unordered_map<int, int> hashMap;
            int maxLength = -1;

            hashMap.insert({A[0], 1});
            
            for(int i=1; i<A.size(); i++){
                hashMap.insert({A[i], 1});
                int num = A[i];
                int prevNum = A[i]-1;
                
                if(hashMap.count(prevNum)>0){
                    int count = hashMap[prevNum];
                    if(count+1 > hashMap[num]){
                        hashMap[num] = count+1;
                    }
                    if(hashMap[num]>maxLength){
                        maxLength = hashMap[num];
                    }
                }
            }
            return maxLength;
        }

        vector<int> printLICS(vector<int> A){
            if(A.size()==0)
                return vector<int>();
            
            vector<vector<int>>LICS(A.size(), vector<int>());
            unordered_map<int, pair<int,int>> hashMap;
            int maxLengthIndex = -1;
            int maxLength = -1;

            LICS[0].push_back(A[0]);
            hashMap[A[0]] = {1,0};
            for(int i=1; i<A.size(); i++){
                hashMap[A[i]] = {1,i};

                if(hashMap.count(A[i]-1)>0){
                    int count = hashMap[A[i] - 1].first;
                    int index = hashMap[A[i] - 1].second;
                    if(count + 1 > hashMap[A[i]].first){
                        hashMap[A[i]].first = count + 1;
                        LICS[i].insert(LICS[i].begin(), LICS[index].begin(),LICS[index].end());
                    }
                }
                LICS[i].push_back(A[i]);        
                if(maxLength<(int)LICS[i].size()){
                    maxLength = LICS[i].size();
                    maxLengthIndex = i;
                }
            }

            return LICS[maxLengthIndex];
        }
};

int main(){
    Solution2 obj;
    vector<int> A = {3, 10, 3, 11, 4, 5, 6, 7, 8, 12};
    cout<<obj.LICS(A)<<endl;
    vector<int> v = obj.printLICS(A);
    for(int i: v)   cout<<i<<" ";

    cout<<endl;
    A = {6, 7, 8, 3, 4, 5, 9, 10};
    cout<<obj.LICS(A)<<endl;
    v = obj.printLICS(A);
    for(int i: v)   cout<<i<<" ";
}

