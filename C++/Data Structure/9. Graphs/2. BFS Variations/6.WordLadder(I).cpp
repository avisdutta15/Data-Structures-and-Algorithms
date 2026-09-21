#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    https://www.youtube.com/watch?v=tRPda0rcf8E

    Problem Statement:
    -----------------
    A transformation sequence from word beginWord to word endWord using a dictionary wordList is a 
    sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
    - Every adjacent pair of words differs by a single letter.
    - Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
    - sk == endWord
    
    Given two words, beginWord and endWord, and a dictionary wordList, return the number of 
    words in the shortest transformation sequence from beginWord to endWord, or 0 if no such 
    sequence exists.

 
    Examples:
    --------
    Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
    Output: 5
    Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", 
                 which is 5 words long.


    Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
    Output: 0
    Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.

    Approach:
    ---------
    Example: beginWord="hit", endWord="cog", wordList=["hot","dot","dog","lot","cog"]

    ---------------------------------------------------------------------------------
    Backtracking (Solution1, Solution2)
    ---------------------------------------------------------------------------------
    At each word, try replacing every character position with 'a'-'z'.
    If the new word is in wordSet and not visited in the current path, recurse.
    Use a visited set to avoid cycles (hit->hot->hit->...).
    Explore ALL paths to endWord and track the minimum chain length.

    Why it is slow:
      At each word we try wordLength * 26 transformations.          => O(L * 26)
      Each valid transformation leads to a recursive call.
      In the worst case we explore every permutation of valid words. => O(N!)
      At each node of the recursion tree we do a wordSet lookup.    => O(L) per lookup
      T.C = O(N! * L * 26)  where N = wordList size, L = word length

      Backtracking explores paths like hit->hot->lot->dot->dog->cog AND
      hit->hot->dot->lot->... (revisiting lot via a different route).
      It wastes time re-exploring longer paths even after finding a shorter one.
      BFS avoids this by guaranteeing the FIRST time we reach a word is via
      the shortest path, so we never need to revisit it.

    Top-down recursive diagram (only valid wordSet transitions shown):

                              backtrack("hit", len=1)
                              try all L*26 transformations, hit->ait->bit...then hat->hbt...hot
                              only "hot" found in wordSet
                                       |
                              i->o: "hot" in set
                                       |
                         backtrack("hot", len=2)
                         try all L*26 transformations, hot->aot->bot..->dot..->lot
                         "dot" and "lot" found in wordSet
                        /                        \
               h->d: "dot"                   h->l: "lot"
                    |                              |
          backtrack("dot",len=3)        backtrack("lot",len=3)
          try all L*26,                 try all L*26,
          "lot" and "dog" found         "dot"(visited) and "dog" found
              /          \                  /          \
        d->l:"lot"    t->g:"dog"      l->d:"dot"    t->g:"dog"
             |              |              |              |
    backtrack("lot",4)  backtrack("dog",4) backtrack("dot",4) backtrack("dog",4)
    try all L*26,       try all L*26,      try all L*26,      try all L*26,
    "dot" visited,      "cog" found        "lot" visited,     "cog" found
    no new words             |             "dog" found             |
     return INT_MAX     d->c:"cog"              |             d->c:"cog"
                             |             t->g:"dog"              |
                    backtrack("cog",5)          |          backtrack("cog",5)
                         |             backtrack("dog",5)       |
                    word==endWord       try all L*26,       word==endWord
                      return 1         "cog" found           return 1
                                            |
                                       d->c:"cog"
                                            |
                                   backtrack("cog",6)
                                        |
                                   word==endWord
                                     return 1

    Backtracking from bottom up:
      backtrack("cog",5)  = 1
      backtrack("dog",4)  = 1 + 1 = 2
      backtrack("dot",3)  = 1 + 2 = 3   (via dot->dog->cog)
      backtrack("lot",3)  = 1 + 3 = 4   (via lot->dot->dog->cog, lot->dog->cog)
      backtrack("hot",2)  = min(1+3, 1+4) = 4  (hot->dot->dog->cog)
      backtrack("hit",1)  = 1 + 4 = 5
      Final answer = 5  (hit->hot->dot->dog->cog)

    ---------------------------------------------------------------------------------
    BFS (Solution3)
    ---------------------------------------------------------------------------------
    BFS explores words level by level. Each level = one more transformation.
    The FIRST time we reach endWord is guaranteed to be via the shortest path.
    We never revisit a word (mark visited when enqueued, not when popped).
    So we don't waste time exploring longer paths like backtracking does.

    T.C = O(N * L * 26)  where N = wordList size, L = word length
      - Outer while loop pops each word at most once          => O(N)
      - For each word, try L * 26 transformations             => O(L * 26)
      - Each wordSet lookup costs O(L)
      Total: O(N * L * 26 * L) = O(N * L^2 * 26)

    Top-down BFS diagram:

    Level 1:                        "hit"
                                      |
                              (i->o) "hot" found in wordSet
                                      |
    Level 2:                        "hot"
                                   /     \
                        (h->d)"dot"       (h->l)"lot"
                                   \     /
    Level 3:               "dot"       "lot"
                           /    \         \
               (d->l)"lot"  (t->g)"dog"  (t->g)"dog"
               already         |           already
               visited       "dog"         visited
                                |
    Level 4:                  "dog"
                                |
                          (d->c) "cog"
                                |
    Level 5:                  "cog" == endWord => return level 5

    BFS processes each word exactly once. When "cog" is dequeued at level 5,
    we immediately return 5. No need to explore further paths.
    This is why BFS is O(N*L*26) vs backtracking O(N! * L * 26).

*/

// Backtracking : with global variables
// Time Complexity: 
class Solution1 {
private:
    void backtrack(unordered_set<string>& wordSet, string word, string& endWord, unordered_set<string>& visited, int lengthOfChain, int& minimumLengthOfChain) {
        // Base Case : if the end word is found then we update the minimumLenghOfChain
        if (word == endWord) {
            minimumLengthOfChain = min(minimumLengthOfChain, lengthOfChain);
            return;
        }

        visited.insert(word);

        // for every character of this word, try to differ with a single character.
        for (int i = 0; i < word.length(); i++) {
            for (char c = 'a'; c <= 'z'; c++) {
                char originalChar = word[i];

                word[i] = c;

                // if this new word is present in the wordSet and is not visited
                // then make a recursive call with lengthOfChain + 1
                if (wordSet.find(word) != wordSet.end() && visited.find(word) == visited.end()) {
                    backtrack(wordSet, word, endWord, visited, lengthOfChain + 1, minimumLengthOfChain);
                }

                // backtrack
                word[i] = originalChar;
            }
        }
        visited.erase(word);
    }

public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        unordered_set<string> visited;  
        // why do we need visited? wordList {hot, hit,...}
        // hit -> hot.
        // hot -> hit.   We will end up in infinite loop if we don't mark visited.

        // Base case: If the endWord is not present in the wordList
        //            return 0 as there is no transformation possible
        if (wordSet.find(endWord) == wordSet.end())
            return 0;

        int minimumLengthOfChain = INT_MAX;
        int lengthOfChain = 1;
        backtrack(wordSet, beginWord, endWord, visited, lengthOfChain, minimumLengthOfChain);

        // if minimumLengthOfChain is still INT_MAX, it means we haven't found any transformation sequence
        return minimumLengthOfChain == INT_MAX ? 0 : minimumLengthOfChain;
    }
};

// Backtracking : Pure Recursion. Each recursion call returns the number of words in the shortest transformation
// from current word to end word
class Solution2 {
private:
    int backtrack(unordered_set<string>& wordSet, string word, string& endWord, unordered_set<string>& visited) {
        // Base Case : if the end word is found then we return 1
        // stating 1 word in the shortest transformation length
        if (word == endWord)
            return 1;

        // mark the current word as visited
        visited.insert(word);

        // the minimum number of transformation needed to reach end word from this word.
        int minimumTransformation = INT_MAX;

        // try to change every single character from a to z and see if the new word is present in the wordSet
        for (int i = 0; i < word.length(); i++) {
            for (char c = 'a'; c <= 'z'; c++) {
                char originalChar = word[i];

                word[i] = c;

                if (wordSet.find(word) != wordSet.end() && visited.find(word) == visited.end()) {
                    int transformation = backtrack(wordSet, word, endWord, visited);
                    if (transformation != INT_MAX)
                        // update the minimum transformation from this word to reach end word.
                        // 1 + transformation from this word to end word. (+ 1 is adding this word to the chain)
                        minimumTransformation = min(minimumTransformation, 1 + transformation);
                }

                // backtrack
                word[i] = originalChar;
            }
        }
        visited.erase(word);
        return minimumTransformation;
    }

public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        unordered_set<string> visited;

        // Base case: If the endWord is not present in the wordList
        //            return 0 as there is no transformation possible
        if (wordSet.find(endWord) == wordSet.end())
            return 0;

        int minimumTransformation = backtrack(wordSet, beginWord, endWord, visited);

        // if minimumLengthOfChain is still INT_MAX, it means we haven't found any transformation sequence
        return minimumTransformation == INT_MAX ? 0 : minimumTransformation;
    }
};

// BFS
// Time Complexity: O(N * wordLength * 26)
class Solution3 {    
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        // Base Case
        if (wordSet.find(endWord) == wordSet.end())
            return 0;

        queue<string> Q;
        unordered_set<string> visited;
        Q.push(beginWord);
        visited.insert(beginWord);
        int level = 1;
        
        // how many times the Q will pop?
        // Q holds only valid words. so worst case all the words of the wordList. O(N)
        while (!Q.empty()) {
            int size = Q.size();
            while (size--) {
                string word = Q.front();
                Q.pop();

                if (word == endWord)
                    return level;

                // try to change every single character from a to z
                // hit-> ait, bit, cit, dit...zit
                // and check if the new word is present in the wordSet
                // if present, push it into the queue and mark it as visited.
                // if not present, then goto the next character of hit.
                // T.C - O(word.length * 26)
                for (int i = 0; i < word.length(); i++) {
                    char originalChar = word[i];    
                    for (char c = 'a'; c <= 'z'; c++) {
                        word[i] = c;
                        if (wordSet.find(word) != wordSet.end() && visited.find(word) == visited.end()) {
                            visited.insert(word);
                            Q.push(word);
                        }
                    }
                    word[i] = originalChar;
                }
            }
            level++;
        }

        return level;
    }
};

int main()
{
    Solution1 obj;    
    vector<string> wordList = {"hot", "dot", "dog", "lot", "cog"};
    cout << obj.ladderLength("hit", "cog", wordList) << endl;
    return 0;
}
