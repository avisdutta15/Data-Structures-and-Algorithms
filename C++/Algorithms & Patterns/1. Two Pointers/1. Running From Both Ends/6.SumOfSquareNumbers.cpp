#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
    https://www.youtube.com/watch?v=B0UrG_X2faA
    Problem Statement:
    ------------------
    Given a non-negative integer c, decide whether there're two integers a and b such that a^2 + b^2 = c.

    Examples:
    --------
    Input: c = 5
    Output: true
    Explanation: 1 * 1 + 2 * 2 = 5

    Input: c = 3
    Output: false

    Constraints:
    ------------
    0 <= c <= 2^31 - 1

    Approach:
    ----------
    Using two pointers approach to find if there exist two integers a and b such that a^2 + b^2 = c
    lower_limit = a = 0 
    upper_limit = b = sqrt(c)
*/

class Solution {
public:
    bool judgeSquareSum(int c) {
        int a = 0;
        int b = sqrt(c);    // why sqrt of c?
        // a2 and b2 are both lying between 0 to c
        // that means a and b are both lying between 0 to sqrt(c)
        // Why upper limit of a and b is sqrt(c)?
        // Lets say (a) <= sqrt(c)
        // then (b) = 0.
        // (a)^2 + (b)^2 = c
        // So the max limit of either a or b is sqrt(c)

        while(a <= b){
            long long int sum = (long long)a*a + (long long)b*b;
            if(sum == c)
                return true;
            else if (sum < c)
                a++;
            else
                b--;
        }
        return false;
    }
};

int main()
{
    Solution obj;
    cout << obj.judgeSquareSum(5) <<endl;
    cout << obj.judgeSquareSum(3) <<endl;

    return 0;
}