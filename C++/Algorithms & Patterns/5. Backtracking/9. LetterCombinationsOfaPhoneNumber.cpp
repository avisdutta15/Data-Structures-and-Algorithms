
/*
    Problem Statement:
    ------------------
    Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. 
    Return the answer in any order.
    A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

         1       2        3
        " "    "abc"    "def"
         4       5        6
       "ghi"   "jkl"    "mno"
         7       8        9
       "pqrs"  "tuv"    "wxyz"
    
    Example:
    -------
    Input: digits = "23"
    Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]


    Input: digits = "2"
    Output: ["a","b","c"]

    Approach:
    ---------
    

*/
class Solution {
private:
    unordered_map<int, string> mapping;
public:
    void setupMapping(){
        mapping.clear();
        mapping[2]="abc";
        mapping[3]="def";
        mapping[4]="ghi";
        mapping[5]="jkl";
        mapping[6]="mno";
        mapping[7]="pqrs";
        mapping[8]="tuv";
        mapping[9]="wxyz";
    }

    //idx denotes the current index of digit being processed.
    void letterCombinationUtil(string &digits, int idx, string &combination, vector<string> &allCombinations){
        if(idx == digits.length()){
            allCombinations.push_back(combination);
            return;
        }

        string letterSet = mapping[digits[idx] - '0'];
        for(int i=0; i<letterSet.length(); i++){
            combination.push_back(letterSet[i]);
            letterCombinationUtil(digits, idx+1, combination, allCombinations);
            combination.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        setupMapping();
        int idx = 0;
        vector<string> allCombinations;
        string combination = "";
        letterCombinationUtil(digits, idx, combination, allCombinations);
        return allCombinations;
    }
};