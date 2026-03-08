#include<bits/stdc++.h>

using namespace std;

class Solution{
    private:
        bool binarySearchRecursiveHelper(vector<int> &arr, int left, int right, int target){
            // If we reach here, then element was not present
            if(left > right)
                return false;
            
            int mid = left + (right - left)/2;

            // Check if x is present at mid
            if(target == arr[mid])
                return true;
            
            // If x is smaller, ignore right half
            if(target < arr[mid])
                return binarySearchRecursiveHelper(arr, left, mid-1, target);
            
            // If x greater, ignore left half
            return binarySearchRecursiveHelper(arr, mid+1, right, target);
        }

    public:
        bool binarySearchIterative(vector<int> &arr, int target){
            if(arr.size() == 0 || target<arr[0] || target>arr[arr.size()-1])
                return false;

            int left = 0;
            int right = arr.size()-1;
            int mid  = left;

            while(left<=right){
                mid = left + (right - left)/2;

                // Check if x is present at mid
                if(arr[mid] == target)  return true;

                // If x is smaller, ignore right half
                if(target < arr[mid]) right = mid - 1;

                // If x greater, ignore left half
                else left = mid + 1;
            }   

            // If we reach here, then element was not present
            return false;
        }

        bool binarySearchRecursive(vector<int> &arr, int target){
            if(arr.size()==0 || target<arr[0] || target>arr[arr.size()-1])
                return false;
            return binarySearchRecursiveHelper(arr, 0, arr.size()-1, target);
        }
};

int main(){
    Solution obj;
    
    vector<int> arr = {1, 2, 4, 5, 6};
    if(obj.binarySearchIterative(arr, 2) == true){
        cout<<"Found"<<endl;
    }
    else{
        cout<<"Not Found"<<endl;
    }

    if(obj.binarySearchIterative(arr, 0) == true){
        cout<<"Found"<<endl;
    }
    else{
        cout<<"Not Found"<<endl;
    }

    if(obj.binarySearchIterative(arr, 7) == true){
        cout<<"Found"<<endl;
    }
    else{
        cout<<"Not Found"<<endl;
    }

    if(obj.binarySearchIterative(arr, 3) == true){
        cout<<"Found"<<endl;
    }
    else{
        cout<<"Not Found"<<endl;
    }

    if(obj.binarySearchRecursive(arr, 2) == true){
        cout<<"Found"<<endl;
    }
    else{
        cout<<"Not Found"<<endl;
    }

    if(obj.binarySearchRecursive(arr, 0) == true){
        cout<<"Found"<<endl;
    }
    else{
        cout<<"Not Found"<<endl;
    }

    if(obj.binarySearchRecursive(arr, 7) == true){
        cout<<"Found"<<endl;
    }
    else{
        cout<<"Not Found"<<endl;
    }

    if(obj.binarySearchRecursive(arr, 3) == true){
        cout<<"Found"<<endl;
    }
    else{
        cout<<"Not Found"<<endl;
    }
}
