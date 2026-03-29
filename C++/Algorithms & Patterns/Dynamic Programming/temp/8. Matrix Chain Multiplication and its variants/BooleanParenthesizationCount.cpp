#include <bits/stdc++.h>
using namespace std;

/*
T(i,j) is number of ways expression from i to j can be parenthesized so that it evaluates to True
F(i,j) is number of ways expression evaluates to False. 
Total(i,j) = T(i,j) + F(i,j) is the total number of ways an expression can be parenthesized irrespective of out being True or False

Hence Base Case when i==j then:
T(i,i) = 1 if operand is T
         0 if operand is F

F(i,i) = 0 if operand is T
         1 if operand is F

How to calculate T(i, j) for expression with more than one values and operators between them?  
    This is something familiar to matrix chain multiplication problem. 
    We will put parenthesis at all possible position and count how many 
    ways these two resultant expressions hold True. Once we have count 
    for each expression, we can combine count based on operator between 
    split expression.

    For expression from index i to index j, find k such that i<k<j, 
    and find number of ways expressions from i to k-1 and k+1 to j evaluates to True.
    Here index k represents an operator
            


For & (and) operator
--------------------
Q: When can Expression(i,j) be True if expression is of form Expression(i, k-1) & Expression(k+1, j)?
A: Only if Expression(i,k-1) and Expression(k+1,j) are  both True. 
   Hence, for any k, expression can be True in T(i,k-1) * T(k+1, j) where T(i,k-1) is number of ways Expression(i,k-1) is True 
   and T(k+1, j) is number of ways Expression(k+1, j) is True.

   T(i,j) = Summation(T(i,k-1) x T(k+1,j))  where i<k<j

Q: When can Expression(i,j) be False if expression is of form Expression(i, k) & Expression(k+1, j)?
A: When one of the two expressions evaluate to false.
   
    Total(i,j) = T(i,j) + F(i,j)
    Total(i,j) = Total(i,k) x Total(k+1,j)

    Total(i,j) = T(i,j) + F(i,j)
  =>F(i,j) = Total(i,j) - T(i,j)
  =>F(i,j) = Summation(Total(i,j) - T(i,k) * T(k+1,j)) where i<k<j
  =>F(i,j) = Summation(Total(i,k) x Total(k+1,j) - T(i,k) * T(k+1,j)) where i<k<j

For | (or) operator
-------------------
Q: When can Expression(i,j) be True if expression is of form Expression(i, k) | Expression(k+1, j)?
A: In case, operator is OR, then, whole expression is True if any one of the expressions is True. 
   So, How many ways both Exp(i,k) and Exp(k+1, j) be False.
        F(i,j) = Summation (F(i,k)* F(k+1,j)) for all  i<k<j
   Overall expression is True when both sub-expressions are not False. 
   Hence:
        T(i,j) = Summation ( Total(i,j) - F(i,k)* F(k+1,j)) where i<k<j

For ^ (xor) operator
-------------------
Q: When can Expression(i,j) be True if expression is of form Expression(i, k) ^ Expression(k+1, j)?
A: In case, operator is XOR, then, whole expression is True if 
            1. Expression(i,k) is True and Expression(k+1, j) is False   or
            2. Expression(i,k) is False and Expression(k+1, j) is True
   
   Hence:
        T(i,j) = Summation ( T(i,k)*F(k+1,j)  + F(i,k)*T(k+1,j)) where i<k<j


*/

class Solution1{
    public:
        int waysToGetTrueUtil(string &expr, int i, int j, bool isTrue){
            if(i>j) return 0;

            if(i==j){
                if(isTrue)
                    return expr[i]=='T';
                else
                    return expr[i]=='F';
            }

            int ways = 0;
            for(int K=i+1; K<j; K=K+2){
                int leftTrue = waysToGetTrueUtil(expr, i, K-1, true);
                int leftFalse = waysToGetTrueUtil(expr, i, K-1, false);
                int rightTrue = waysToGetTrueUtil(expr, K+1, j, true);
                int rightFalse = waysToGetTrueUtil(expr, K+1, j, false);

                if(expr[K] == '^'){
                    if(isTrue){
                        ways += leftTrue * rightFalse + rightTrue * leftFalse;
                    }else{
                        ways += leftTrue * rightTrue + leftFalse * rightFalse;
                    }
                }
                else if(expr[K] == '&'){
                    if(isTrue){
                        ways += leftTrue * rightTrue;
                    }else{
                        ways += leftFalse * rightFalse + leftFalse * rightTrue + leftTrue * rightFalse;
                    }
                }
                else if(expr[K] == '|'){
                    if(isTrue){
                        ways += leftTrue * rightTrue + leftTrue * rightFalse + leftFalse * rightTrue;
                    }else{
                        ways += leftFalse * rightFalse;
                    }
                }
            }

            return ways;
        }

        int waysToGetTrue(string expr){
            int start = 0;
            int end = expr.length()-1;
            bool isTrue = true;
            return waysToGetTrueUtil(expr, start, end, isTrue);
        }
};


//Memoization dp[i][j][2] i.e. dp[i][j][isTrue]
class Solution2{
    public:
        int waysToGetTrueUtil(string &expr, int i, int j, bool isTrue, unordered_map<string, int> &lookup){
            string trueFalse = isTrue?"true" : "false";
            string key = to_string(i)+" "+to_string(j)+" "+trueFalse;
            
            if(i>j) return lookup[key]=0;

            if(i==j){
                if(isTrue)
                    return lookup[key]=expr[i]=='T';
                else
                    return lookup[key]=expr[i]=='F';
            }

            if(lookup.count(key)>0)
                return lookup[key];

            int ways = 0;
            for(int K=i+1; K<j; K=K+2){
                int leftTrue = waysToGetTrueUtil(expr, i, K-1, true, lookup);
                int leftFalse = waysToGetTrueUtil(expr, i, K-1, false, lookup);
                int rightTrue = waysToGetTrueUtil(expr, K+1, j, true, lookup);
                int rightFalse = waysToGetTrueUtil(expr, K+1, j, false, lookup);

                if(expr[K] == '^'){
                    if(isTrue){
                        ways += leftTrue * rightFalse + rightTrue * leftFalse;
                    }else{
                        ways += leftTrue * rightTrue + leftFalse * rightFalse;
                    }
                }
                else if(expr[K] == '&'){
                    if(isTrue){
                        ways += leftTrue * rightTrue;
                    }else{
                        ways += leftFalse * rightFalse + leftFalse * rightTrue + leftTrue * rightFalse;
                    }
                }
                else if(expr[K] == '|'){
                    if(isTrue){
                        ways += leftTrue * rightTrue + leftTrue * rightFalse + leftFalse * rightTrue;
                    }else{
                        ways += leftFalse * rightFalse;
                    }
                }
            }

            return lookup[key]=ways;
        }

        int waysToGetTrue(string expr){
            int start = 0;
            int end = expr.length()-1;
            bool isTrue = true;
            unordered_map<string, int> lookup;
            return waysToGetTrueUtil(expr, start, end, isTrue, lookup);
        }
};


class Solution3{
    public:
        int waysToGetTrue(string expr){
                
            int operandsLen = (expr.length());

            
            //int T[operandsLen][operandsLen]
            //int F[operandsLen][operandsLen]
            vector<vector<int>> T (operandsLen, vector<int>(operandsLen, 0));
            vector<vector<int>> F (operandsLen, vector<int>(operandsLen, 0));

            // Fill diaginal entries first 
            // All diagonal entries in T[i][i] are 1 if symbol[i] 
            // is T (true).  Similarly, all F[i][i] entries are 1 if 
            // symbol[i] is F (False) 
            for(int i=0; i<expr.length(); i++){
                
                char operand = expr[i];
                T[i][i] = operand=='T' ? 1 : 0;
                F[i][i] = operand=='F' ? 1 : 0;
            }

            for(int gap = 3; gap<=operandsLen; gap++){ //why gap=3? coz minimum string 'T op F'. length = 3
                for(int start=0; start<=operandsLen-gap; start++){
                    int end = start + gap - 1;
                    
                    for(int K = start+1; K<end; K=K+2){
                        
                        if(expr[K] == '^'){
                            T[start][end] +=  T[start][K-1] * F[K+1][end] + T[K+1][end] * F[start][K-1];
                            F[start][end] +=  T[start][K-1] * T[K+1][end] + F[start][K-1] * F[K+1][end];
                        }
                        else if(expr[K] == '&'){
                            T[start][end] += T[start][K-1] * T[K+1][end];
                            F[start][end] += F[start][K-1] * F[K+1][end] + F[start][K-1] * T[K+1][end] + T[start][K-1] * F[K+1][end];
                        }
                        else if(expr[K] == '|'){
                            T[start][end] += T[start][K-1] * T[K+1][end] + T[start][K-1] * F[K+1][end] + F[start][K-1] * T[K+1][end];
                            F[start][end] += F[start][K-1] * F[K+1][end];
                        }
                    }
                }
            }
            return T[0][operandsLen-1];
        }
};

int main(){
    Solution1 obj1;
    Solution2 obj2;
    Solution3 obj3;
    
    string expr = "T|T&F^T";
    cout<<obj1.waysToGetTrue(expr)<<endl;
    
    expr = "T^F|F";
    cout<<obj1.waysToGetTrue(expr)<<endl;

    expr = "T|T&F^T";
    cout<<obj2.waysToGetTrue(expr)<<endl;
    
    expr = "T^F|F";
    cout<<obj2.waysToGetTrue(expr)<<endl;
    
    expr = "T|T&F^T";
    cout<<obj3.waysToGetTrue(expr)<<endl;
    
    expr = "T^F|F";
    cout<<obj3.waysToGetTrue(expr)<<endl;
}