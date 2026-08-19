#include <bits/stdc++.h>
using namespace std;

/*
    Given an array find the maximum sum of a subsequence with the constraint that no 2 numbers 
    in the sequence should be adjacent in the array.

    A = {5, 5, 10, 40, 50, 35};
    max_sum = 80   =>  5 + 40 + 35

    Approach:
        include = maximum sum including the previous element
        exclude = maximum sum excluding the previous element

    Lets see how we calculate include and exclude.
    Exclude:
        5, 5, 10, 40.     
        suppose our current element is 40
        include = 15 (maximum sum including the previous element 10)
        exclude = 5  (maximum sum excluding the previous element 10)
        Since we are excluding the current element, we can add the previous element as per the 
        constraint. So we are excluding the current element and including the previous element.
        So we will consider what ever is maximum of include and exclude of the previous element.

        so exclude = max(include 10, exclude 10)
                   = max(15, 5)
                   = 15
    
    Include:
        5, 5, 10, 40
        suppose our current element is 40
        include = 15 (maximum sum including the previous element 10)
        exclude = 5  (maximum sum excluding the previous element 10)
 
        We have to find a sum including the current element. Since our constraint says that we
        cannot have adjacent element, hence we have to add this element to the max sum we got by
        excluding the previous element.
 
        so include = max sum exclude 10  + 40
                   = 5 + 40
                   = 45
*/



class Solution{
    public:
        int maxSumNonAdjacent(vector<int> A){
            int include = A[0];
            int exclude = 0;
            int prevInclude = include;
            for(int i=1; i<A.size(); i++){
                prevInclude = include;
                include = exclude + A[i];
                exclude = max(exclude, prevInclude);
            }
            return max(include, exclude);
        }
};

int main(){
    Solution obj;
    vector<int> A = {5, 5, 10, 40, 50, 35};
    cout<<obj.maxSumNonAdjacent(A);
}