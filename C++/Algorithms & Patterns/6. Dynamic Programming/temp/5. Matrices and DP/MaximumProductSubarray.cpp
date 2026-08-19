#include <bits/stdc++.h>
using namespace std;

/*
    Maximum Product Subarray:
    ------------------------
    A = {-1, 6, 2, 0, 7, 9};

    Lets see the cases:
    Till now we have seen -1, 6, 2 
    Since we are asked about the maximum product, we have kept the maximum product till now i.e.12
    So,
    -1, 6, 2
    currentMaxTillNow[i-1] = 12
    Now if the next element is a positive number then we should multiply it with this product
    currentMaxTillNow[i] = max(A[i], currentMaxTillNow[i-1]*A[i]);

    But if the next element is a negative number (suppose -2) then multiplying with 12 will make it less
    So we should also keep track of currentMinTillNow which is -12.
    currentMinTillNow[i] = max(A[i], currentMinTillNow[i-1]*A[i]);

    Hence the modified equation becomes
        currentMaxTillNow[i] = max(nums[i], max(currentMaxTillNow[i-1] * nums[i], currentMinTillNow[i-1] * nums[i]));
        currentMinTillNow[i] = min(nums[i], min(currentMaxTillNow[i-1] * nums[i], currentMinTillNow[i-1] * nums[i]));

    Atlast find the maximum of all currentMaxTillNow.
*/

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if(nums.size()==0)
            return 0;
        vector<int> currentMaxTillNow(nums.size(), 0);
        vector<int> currentMinTillNow(nums.size(), 0);
        
        currentMaxTillNow[0] = nums[0];
        currentMinTillNow[0] = nums[0];
        
        for(int i=1; i<nums.size(); i++){
            currentMaxTillNow[i] = max(nums[i], max(currentMaxTillNow[i-1] * nums[i], 
                                                currentMinTillNow[i-1] * nums[i]));
            
            currentMinTillNow[i] = min(nums[i], min(currentMaxTillNow[i-1] * nums[i], 
                                                currentMinTillNow[i-1] * nums[i]));
        }
        
        int maxProduct = INT_MIN;
        for(int i: currentMaxTillNow)
            maxProduct = max (maxProduct, i);
        
        return maxProduct;
    }
};