#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/*
    Problem Statement:
    -----------------
    Find and Replace Pattern
    
    Given a list of strings words and a string pattern, return a list of words[i] that match pattern.
    You may return the answer in any order.
    
    A word matches the pattern if there exists a permutation of letters p so that after replacing 
    every letter x in the pattern with p(x), we get the desired word.
    
    Recall that a permutation of letters is a bijection from letters to letters: 
    every letter maps to another letter, and no two letters map to the same letter.

    Examples:
    --------
    Example 1:
        Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
        Output: ["mee","aqq"]
        Explanation: 
        "mee" matches because {a->m, b->e} is a valid bijection
        "aqq" matches because {a->a, b->q} is a valid bijection
        "ccc" doesn't match because {a->c, b->c} is not bijection (two letters map to same)

    Example 2:
        Input: words = ["a","b","c"], pattern = "a"
        Output: ["a","b","c"]
        Explanation: Any single character can map to any single character

    Constraints:
    1 <= pattern.length <= 20
    1 <= words.length <= 50
    words[i].length == pattern.length
    pattern and words[i] are lowercase English letters.

    Approach:
    ---------
    1. Bijection Validation
        For each word, check if there exists a valid bijection:
        1. Create mapping from pattern[i] -> word[i]
        2. Create reverse mapping from word[i] -> pattern[i]  
        3. Ensure both mappings are consistent (bijection property)
        4. If any conflict found, word doesn't match pattern
    
        T.C. : O(N * M) where N = number of words, M = pattern length
        S.C. : O(1) - fixed size maps for 26 lowercase letters

    2. Normalization Approach
        Normalize the strings to create a numeric pattern
        ["abc",     "deq",    "mee",    "aqq",    "dkd",    "ccc"]
         1#2#3      1#2#3     1#2#2     1#2#2     1#2#1     1#1#1

        PATTERN : "abb" -> 1#2#2
        So, we can clearly see 2 words have same pattern that is 1#2#2

        How to normalize a word?
        counter=0
        hash_map[char, int] map
        for each char c
            if c is present in the map
                signature = signature + '#' + to_string(map[c]);
            else
                map[c] = ++counter;
                signature = signature + '#' + to_string(map[c]);
        
        T.C. : O(N * M) where N = number of words, M = pattern length
        S.C. : O(1) - fixed size maps for 26 lowercase letters

*/

class Solution {
private:
    //aabc -> 1#1#2#3
    string normalize(string word) {
        string signature;
        unordered_map<char, long long> charIntMap;
        signature.reserve(word.length());

        int index = 1;
        for (auto c : word) {
            if (charIntMap.find(c) == charIntMap.end()) {
                charIntMap[c] = index++;
                signature = signature + '#' + to_string(charIntMap[c]);
            }
            else {
                signature = signature + '#' + to_string(charIntMap[c]);
            }
        }
        cout << word << " : " << signature << endl;
        return signature;
    }

    bool sameWordPatternHaveSameBijection(const string &word, const string &pattern) {
        vector<char> w2p(26, 0);
        vector<char> p2w(26, 0);

        for (int i = 0; i < pattern.length(); i++) {
            char w = word[i], p = pattern[i];

            //w2p mapping
            if (w2p[w - 'a'] == 0) {
                w2p[w - 'a'] = p;
            }
            else if (w2p[w - 'a'] != p) {
                return false;
            }

            //p2w mapping
            if (p2w[p - 'a'] == 0) {
                p2w[p - 'a'] = w;
            }
            else if (p2w[p - 'a'] != w) {
                return false;
            }
        }
        //cout << word << " : " << pattern << endl;
        return true;
    }

public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        string patternSignature = normalize(pattern);

        vector<string> answer;
        for (auto word : words) {
            if (normalize(word) == patternSignature) {
                answer.push_back(word);
            }
        }
        return answer;
    }

    vector<string> findAndReplacePattern2(vector<string>& words, string pattern) {
        vector<string> answer;
        for (string &word : words) {
            if (sameWordPatternHaveSameBijection(word, pattern)) {
                answer.push_back(move(word));
            }
        }
        return answer;
    }

};

int main() {
    Solution obj;
    vector<string> words = { "abc","deq","mee","aqq","dkd","ccc" };
    string pattern = "abb";
    auto matches = obj.findAndReplacePattern2(words, pattern);
    for (auto& word : matches) {
        cout << word << " ";
    }
    cout << endl;

    words = { "a","b","c" };
    pattern = "a";
    matches = obj.findAndReplacePattern2(words, pattern);
    for (auto& word : matches) {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}