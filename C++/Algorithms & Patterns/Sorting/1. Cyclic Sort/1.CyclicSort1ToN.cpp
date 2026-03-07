#include <iostream>
#include <vector>

using namespace std;

// Cyclic sort is used to sort an array where elements are in range 1 to N in O(N) time complexity


class Solution {
private:
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
public:
    //correct position of A[i] = i-1
    void cyclicSort(vector<int>& A) {
        
        //in each cycle we try to place the correct element in index i
        for(int i=0; i<A.size(); i++){
            
            //In a 1 to N range correct position of A[i] = value at A[i] - 1
            int correctIndexOfAi = A[i] - 1;

            //check if A[i] is in its correct position or not
            while (A[i] != A[correctIndexOfAi]) {
                swap(A[i], A[correctIndexOfAi]);
                correctIndexOfAi = A[i] - 1;
            }
        }
    }
};

int main()
{
    Solution obj;
    vector<int> A = {3, 5, 2, 1, 4};

    cout << "\nBefore sorting: "<<endl;
    for (int i : A) {
        cout << i << " ";
    }

    obj.cyclicSort(A);
    
    cout << "\nAfter sorting: "<<endl;
    for (int i : A) {
        cout << i << " ";
    }
    return 0;
}