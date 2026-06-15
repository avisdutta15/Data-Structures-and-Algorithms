#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given a string s, reverse only all the vowels in the string and return it.
    The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both 
    lower and upper cases, more than once.

 

	Examples:
	---------
	Input: s = "IceCreAm"
    Output: "AceCreIm"
    Explanation: 
    The vowels in s are ['I', 'e', 'e', 'A']. On reversing the vowels, s becomes "AceCreIm".

	Input: s = "leetcode"
    Output: "leotcede"

	Constraints:
	------------
		1 <= s.length <= 3 * 10^5
		s consists only of printable ASCII characters


	Approach 
	--------


*/

class Solution {
private:
    bool isVowel(char c) {
        unordered_set<char> vowels;
        vowels.insert('A');
        vowels.insert('a');
        vowels.insert('E');
        vowels.insert('e');
        vowels.insert('I');
        vowels.insert('i');
        vowels.insert('O');
        vowels.insert('o');
        vowels.insert('U');
        vowels.insert('u');
        if (vowels.find(c) != vowels.end())
            return true;
        return false;
    }
public:
    string reverseVowels(string s) {
        int i = 0; int j = s.length() - 1;
        while (i < j) {
            if (isVowel(s[i]) == false)
                i++;
            if (isVowel(s[j]) == false)
                j--;
            else if (isVowel(s[i]) && isVowel(s[j])) {
                char temp = s[i];
                s[i] = s[j];
                s[j] = temp;
                i++; j--;
            }
        }
        return s;
    }
};

int main() {
	Solution obj;
	cout<<obj.reverseVowels("IceCreAm")<<endl;
	cout<<obj.reverseVowels("leetcode")<<endl;

	return 0;
}
