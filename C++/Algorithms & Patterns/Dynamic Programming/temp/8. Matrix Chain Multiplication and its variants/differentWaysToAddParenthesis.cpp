#include <bits/stdc++.h>
using namespace std;

/*
    Given a string that represents an expression constituting numbers and binary operator +, – and * only. 
    We need to parenthesize the expression in all possible way and return all evaluated values.

    Input : expr = "5*4-3*2"
    Output : {-10, 10, 14, 10, 34}
    (5*(4-(3*2))) = -10
    (5*((4-3)*2)) = 10
    ((5*4)-(3*2)) = 14
    ((5*(4-3))*2) = 10
    (((5*4)-3)*2) = 34

    Approach:
    We will use a divide and conquer approach.
    Whenever we encounter an operator, we will divide the expression into two halves. 
        Left half  = expr[0...i] 
        operator 
        Right half = expr[i+2...end]
    We will recursively calculate each sub part.
    Note the left and right half may return more than 1 result. So we will use vectors to store them.
    E.g.    5 * 4 - 3 * 2
        Left Part = (5)
        Right Part = (4-3*2) This right part can be further broken down into 2 ways 
                     (4)-(3*2)  and  (4-3)*2
        So in (5 * 4 - 3 * 2) the left part (5) can be combined with 2 right parts :- (5) * (4)-(3*2)  and  (5) * (4-3)*2
        Hence for all elements in left.
                 for all elements in right.
                    store element left [operator] element right

    Slight modification, if we analyse the recursion tree, we can observe one sub problem is computed multiple times.
    So we can use a top down DP approach along with the recursion, where we store the expression and its vector in a map.
*/





class Solution{
    unordered_map<string, vector<int>> Hash;
    public:
        vector<int> diffWaysToCompute(string expr){
            vector<int> ans;
            int isOnlyNum = true;

            if(Hash.find(expr)!=Hash.end())
                return Hash[expr];

            for(int i=0; i<expr.length(); i++){
                //if the current character is an operator, then break the expression here into 2 parts
                if(expr[i]=='+' || expr[i]=='-' || expr[i]=='*'){
                    isOnlyNum =false;
                    vector<int> leftRecur = diffWaysToCompute(expr.substr(0, i));
                    vector<int> rightRecur = diffWaysToCompute(expr.substr(i+1, expr.length()-i+1));

                    //combine all the combinations
                    for(int l : leftRecur){
                        for(int r : rightRecur){
                            if(expr[i] == '+') ans.push_back(l+r);
                            else if(expr[i] == '-') ans.push_back(l-r);
                            else if(expr[i] == '*') ans.push_back(l*r);
                        }
                    }
                }
            }

            if(isOnlyNum)
                ans.push_back(stoi(expr));

            Hash[expr] = ans;
            return ans;
        }
};

int main(){
    string expr = "5*4-3*2";
    Solution obj;

    vector<int> ans = obj.diffWaysToCompute(expr);
    for(int i:ans)
        cout<<i<<" ";
}