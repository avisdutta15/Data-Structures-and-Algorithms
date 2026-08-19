#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
        int getCeil(vector<int> A, int left, int right, int X){
            while(left<right){
                int mid = left + (right-left)/2;
                if(A[mid]<X)
                    left = mid+1;
                else
                    right = mid;
            }

            return right;
        }

        int LIS(vector<int> A){
            int n = A.size();
            if(n==0)
                return 0;
            int lisLength = 0;
            vector<int> lisArray;
            lisArray.push_back(A[0]);
            lisLength = 1;

            for(int i=1; i<n; i++){
                
                //if the current element is less than the first element of lisArray
                //then replace the first element with current element
                if(A[i]<lisArray[0])
                    lisArray[0] = A[i];
                    
                //if current element is greater than the last element of the lisArray
                //then push it into the lisArray
                else if(A[i]>lisArray[lisLength-1]){
                    lisArray.push_back(A[i]);
                    lisLength++;
                }
                
                //else get the index of the largest element in lisArray
                //that is smaller than the current element. Place current element
                //in its place.
                else{
                    int ceilIndex = getCeil(lisArray, 0, lisLength-1, A[i]);
                    lisArray[ceilIndex] = A[i];
                }
            }            
            return lisLength;
        }

        int LISSTL(vector<int> A){
            int n = A.size();
            if(n==0)
                return 0;
            vector<int> lisArray;
            
            for(int i=0; i<n; i++){
                auto it = lower_bound(lisArray.begin(), lisArray.end(), A[i]);
                if(it==lisArray.end())
                    lisArray.push_back(A[i]);
                else
                    *it = A[i];
            }
            return lisArray.size();
        }
};

int main(){
    vector<int> A = {50, 3, 10, 7, 40, 80};    
    Solution obj; 
    cout<<obj.LISSTL(A)<<endl;  //4
    
    A = {3, 2};
    cout<<obj.LISSTL(A)<<endl;  //1
    
    A = {3, 10, 2, 1, 20};
    cout<<obj.LISSTL(A)<<endl;  //3
}   