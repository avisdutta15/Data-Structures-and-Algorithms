#include <iostream>
#include <vector>

using namespace std;

// Cyclic sort is used to sort an array where elements are in range 0 to N-1 in O(N) time complexity


class Solution {
private:
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
public:
    //correct position of A[i] = i
    void cyclicSort(vector<int>& A) {
        
        //in each cycle we try to place the correct element in index i
        for(int i=0; i<A.size(); i++){
            
            //In a 0 to N range correct position of A[i] = value at A[i]
            int correctIndexOfAi = A[i];

            //check if A[i] is in its correct position or not
            while (A[i] != A[correctIndexOfAi]) {
                swap(A[i], A[correctIndexOfAi]);
                correctIndexOfAi = A[i];
            }
        }
    }
};

int main()
{
    Solution obj;
    vector<int> A = {2, 4, 1, 0, 3};

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