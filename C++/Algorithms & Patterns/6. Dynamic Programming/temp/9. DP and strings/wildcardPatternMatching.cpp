#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    Given a text and a wildcard pattern, implement wildcard pattern matching algorithm that finds if 
    wildcard pattern is matched with text. The matching should cover the entire text (not partial text).

    The wildcard pattern can include the characters ‘?’ and ‘*’
    ‘?’ – matches any single character
    ‘*’ – Matches any sequence of characters (including the empty sequence)

    For example,

        Text = "baaabab",
        Pattern = “*****ba*****ab", output : true
        Pattern = "baaa?ab", output : true
        Pattern = "ba*a?", output : true
        Pattern = "a*ab", output : false 
*/

/*
        Approach:
            Base Cases:
                if pattern and text are empty then
                    return true;
                if pattern is empty and text is not then 
                    return false;
                if text is empty 
                    if pattern contains only * then
                        return true;
                    elese
                        return false;
            
            Other Cases:
                if pattern[N] == '*'
                    case 1: we can include either include * and match i.e.
                            recurse for N, M-1
                    case 2: we can exclude * and match i.e.
                            recurse for N-1, M 
                if pattern[N] == '?' or pattern[N]==text[M]
                    recurse for N-1, M-1
                else
                    return false

*/

class Solution
{
    private:
        int lookup[100][100];
    public:
        int util(string text, string pattern, int n, int m){
            
            //if both pattern and text reaches their end then return true.
            if(n<0 && m<0)
                return 1;

            //if pattern reaches and text remains then return false
            if(m<0)
                return 0;

            //if text reaches end but pattern remains then pattern should only contain *
            if(n<0){
                while(m>=0){
                    if(pattern[m]!='*')
                        return 0;
                    m--;
                }
                return 1;
            } 

            //Case 1: current character in pattern is *
            //         a. * matches with current characters in the input string.
            //            Then we will move to the next character in the input string
            //         b. Ignore * and move to the next character in the pattern
            if(pattern[m]=='*'){
                int include = util(text, pattern, n-1, m);
                int exclude = util(text, pattern, n, m-1);
                return include || exclude;
            }
            //Case 2: current character in pattern is ? 
            //        recur for next character in the pattern and text
            else if(pattern[m]=='?') {
                return util(text, pattern, n-1, m-1);
            }
            //Case 3: current character is not a wildcard character 
            else if(pattern[m] == text[n]){
                return util(text, pattern, n-1, m-1); 
            }
            return false;
        }
        int utilTopDown(string text, string pattern, int n, int m){
            
            //if both pattern and text reaches their end then return true.
            if(n<0 && m<0)
                return 1;

            //if pattern reaches and text remains then return false
            if(m<0)
                return 0;

            //if text reaches end but pattern remains then pattern should only contain *
            if(n<0){
                while(m>=0){
                    if(pattern[m]!='*')
                        return 0;
                    m--;
                }
                return 1;
            } 

            if(lookup[m][n]==-1){
                //Case 1: current character in pattern is *
                //         a. * matches with current characters in the input string.
                //            Then we will move to the next character in the input string
                //         b. Ignore * and move to the next character in the pattern
                if(pattern[m]=='*'){                    
                    int include = utilTopDown(text, pattern, n-1, m);
                    int exclude = utilTopDown(text, pattern, n, m-1);
                    lookup[m][n] = include || exclude;
                    
                }
                //Case 2: current character in pattern is ? 
                //        recur for next character in the pattern and text
                else if(pattern[m]=='?') {
                    
                    lookup[m][n] = utilTopDown(text, pattern, n-1, m-1);
                    
                }
                //Case 3: current character is not a wildcard character 
                else{
                    if(pattern[m]!=text[n]){
                        lookup[m][n] = 0;
                    }
                    else
                        lookup[m][n] = utilTopDown(text, pattern, n-1, m-1);                
                }
            }
            return lookup[m][n];
        }

        bool wildcardMatchingTopDown(string text, string pattern){
            int n = text.length();
            int m = pattern.length();

            memset(lookup, -1, sizeof(lookup));           

            return utilTopDown(text, pattern, n-1, m-1);
        }

        bool wildcardMatchingBottomUp(string text, string pattern){
            int n = text.size();
            int m = pattern.size();
            bool DP[n+1][m+1];

            //when both text and pattern are empty then true
            DP[0][0] = true;

            //when pattern is empty then true.
            for(int i=1; i<=n; i++)
                DP[i][0] = false;

            //when text is empty and pattern contains *
            //	    0	*	b	*	a	b
            //  0	T	T	F	F	F	F

            for(int j=1; j<=m; j++){
                if(pattern[j-1]=='*')
                    DP[0][j] = DP[0][j-1];
                else
                    DP[0][j] = false;
            }
            
            for(int i=1; i<=text.length(); i++){
                for(int j=1; j<=pattern.length(); j++){
                    
                    //If pattern[j-1] is * then we can either include * or exclude * 
                    if(pattern[j-1]=='*')
                        DP[i][j] = DP[i-1][j] || DP[i][j-1];
                    
                    //If pattern[j-1] is ? or pattern[j-1]==text[j-1] then recurse for n-1 m-1
                    else if(pattern[j-1]=='?' || pattern[j-1]==text[i-1])
                        DP[i][j] = DP[i-1][j-1];
                    
                    //pattern[j-1]!=text[j-1] then it is false
                    else if(pattern[j-1]!=text[i-1])
                        DP[i][j] = false;
                }
            }
            
            return DP[n][m];
        }

        bool wildcardMatching(string text, string pattern){
            int n = text.length();
            int m = pattern.length();

            return util(text, pattern, n-1, m-1);
        }
};

int main(){
    Solution obj;
    
    vector<string> patterns = {"*****ba*****ab", 
                               "ba*****ab",
                               "ba*ab",
                               "a*ab",
                               "a*****ab",
                               "*a*****ab",
                               "ba*ab****",
                               "****",
                               "*",
                               "aa?ab",
                               "b*b",
                               "a*a",
                               "baaabab",
                               "?baaabab",
                               "*baaaba*"
                            };
    
    string text = "baaabab";

    for(string pattern: patterns){
        cout<<"Text: "<<text<<" "<<"Pattern: "<<pattern;
        obj.wildcardMatchingBottomUp(text, pattern)==true?cout<<" Matched"<<endl:cout<<" Not Matched"<<endl;
    }

    return 0;
}