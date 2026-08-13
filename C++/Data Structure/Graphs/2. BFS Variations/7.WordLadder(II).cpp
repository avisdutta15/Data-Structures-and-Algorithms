#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    https://www.youtube.com/watch?v=mIZJIuMpI2M

    Problem Statement:
    -----------------
    Given two words beginWord and endWord, and a wordList, find ALL shortest
    transformation sequences from beginWord to endWord such that:
      - Only one letter can be changed at a time
      - Each transformed word must exist in wordList
    Return all such shortest transformation sequences.

    Examples:
    --------
    Input : beginWord="hit", endWord="cog"
            wordList=["hot","dot","dog","lot","log","cog"]
    Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]

    Approach:
    ---------
    Two phases:
      Phase 1 - BFS: Build a DAG (directed acyclic graph) of only the shortest paths.
      Phase 2 - DFS: Traverse the DAG to collect all paths from beginWord to endWord.

    Why not pure BFS or pure DFS?
      - Pure BFS gives shortest path length but not all paths.
      - Pure DFS/backtracking explores ALL paths including longer ones (slow).
      - BFS+DFS: BFS first prunes the graph to shortest-path edges only,
        then DFS collects all paths on that pruned graph efficiently.

    ---------------------------------------------------------------------------------
    Phase 1: BFS to build the DAG
    ---------------------------------------------------------------------------------
    Standard BFS level-by-level from beginWord.
    For each word dequeued, try all L*26 single-char transformations.
    For each valid neighbour found in wordSet:
      - If NOT yet visited (no level assigned):
          assign level[neighbour] = level[word] + 1
          add edge word -> neighbour in graph
          enqueue neighbour
      - If ALREADY visited AND level[neighbour] == level[word] + 1:
          add edge word -> neighbour in graph  (same-level cross edge, still shortest)
          do NOT enqueue again (already in queue or processed)

    The second condition is the key difference from Word Ladder I.
    In Ladder I we skip already-visited nodes entirely.
    In Ladder II we still add the edge if it is a same-level forward edge,
    because it represents another shortest path to that node.

    Stop BFS only after the ENTIRE level containing endWord is processed.
    targetWordFound is set when endWord is dequeued, and we immediately
    break out of the inner loop (skip finding neighbours of endWord and
    all remaining words at that level) since endWord has no useful children
    — any edges added from endWord's level would point to level+1 which is
    beyond the shortest path and never traversed by DFS.
    The outer while checks targetWordFound only between levels.
    This is critical — it ensures ALL words at the same level as endWord
    get to add their edges to endWord before BFS stops.

    e.g. both "dog" and "log" are at level 4. When "dog" is processed,
    "cog" is found and enqueued. Later when "cog" is dequeued,
    targetWordFound=true and we continue (skip cog's neighbours).
    But "log" is still in the inner while loop and gets processed too,
    adding log->cog edge.
    Only after the full level 4 is done does the outer while exit.

    BFS execution on example:
    wordSet = {hot, dot, dog, lot, log, cog}

    Level 1:                      "hit"
                                    |
                          try all L*26 transforms
                          only "hot" found in wordSet
                                    |
                           graph["hit"] = ["hot"]
                           level["hot"] = 2
                                    |
    Level 2:                      "hot"
                                    |
                          try all L*26 transforms
                          "dot" and "lot" found in wordSet
                         /                          \
               graph["hot"] = ["dot", "lot"]
               level["dot"] = 3, level["lot"] = 3
                         /                          \
    Level 3:          "dot"                        "lot"
                        |                             |
              try all L*26                    try all L*26
              "dog" found (new)               "log" found (new)
              "lot" found but                 "dot" found but
               level[lot]=3 == 3+1? NO         level[dot]=3 == 3+1? NO
               skip (not a child)              skip (not a child)
                        |                             |
             graph["dot"] = ["dog"]        graph["lot"] = ["log"]
             level["dog"] = 4              level["log"] = 4
                        |                             |
    Level 4:          "dog"                        "log"
                        |                             |
              try all L*26                    try all L*26
              "cog" found (new)               "cog" found BUT
                        |                     level[cog]=5 == level[log]+1=5? YES
             graph["dog"] = ["cog"]           add edge log->cog (cross edge!)
             level["cog"] = 5               graph["log"] = ["cog"]
             enqueue "cog"                  (still processed because "dog" and "log"
                                             are both in level 4, inner while finishes
                                             the full level before outer while exits)
                        |                             |
    Level 5:          "cog" dequeued
                      word == endWord =>
                      targetWordFound = true
                      break  (no useful edges from endWord or any other level-5 word)
                      outer while checks targetWordFound == true => stop

    Resulting DAG (only shortest-path edges):

                          "hit"
                            |
                          "hot"
                         /     \
                      "dot"   "lot"
                        |       |
                      "dog"   "log"
                         \     /
                          "cog"

    level map:  hit=1, hot=2, dot=3, lot=3, dog=4, log=4, cog=5

    ---------------------------------------------------------------------------------
    Phase 2: DFS to collect all paths
    ---------------------------------------------------------------------------------
    Simple DFS on the DAG from beginWord to endWord.
    Since the graph is a DAG (all edges go strictly from level L to level L+1),
    there are no cycles, no visited set needed.
    Every root-to-leaf path in the DAG is a shortest transformation sequence.

    DFS execution on the DAG:

                          "hit"  path=["hit"]
                            |
                          "hot"  path=["hit","hot"]
                         /     \
                      "dot"   "lot"
                        |         \
    path=["hit","hot","dot"]    path=["hit","hot","lot"]
                        |               |
                      "dog"           "log"
                        |               |
    path=["hit","hot","dot","dog"]  path=["hit","hot","lot","log"]
                        |               |
                      "cog"           "cog"
                        |               |
    node==endWord               node==endWord
    allPaths.push_back(         allPaths.push_back(
    ["hit","hot","dot","dog","cog"])  ["hit","hot","lot","log","cog"])

    Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]

    Time Complexity: O(M^2 * N) where M = word length, N = wordList size

    Phase 1 - BFS:
      Each word is dequeued at most once                          => O(N) dequeues
      For each word, we try M positions * 26 chars               => O(M * 26) = O(M) per word
      Each wordSet lookup compares strings of length M           => O(M) per lookup
      So per word: O(M * 26 * M) = O(M^2)
      Total BFS: O(N * M^2)

      In our example: N=6 words, M=3 chars
        "hot": 3 positions * 26 lookups * 3 char compare = 234 ops
        "dot": same, "lot": same ... all 6 words
        Total BFS ~ 6 * 3 * 26 * 3 = 1404 ops = O(N * M^2)

    Phase 2 - DFS:
      DFS traverses every edge in the DAG exactly once.
      In the worst case the DAG has O(N) nodes and O(N) edges    => O(N)
      Each path has length M (shortest path length).
      Copying path into allPaths costs O(M) per path.
      Number of shortest paths is at most O(N)                   => O(N * M)
      Total DFS: O(N * M)

      In our example:
        2 paths, each of length 5 => 2 * 5 = 10 copy ops
        DAG has 7 nodes, 6 edges  => 6 edge traversals
        Total DFS ~ O(N * M)

    Overall: O(N * M^2) + O(N * M) = O(N * M^2)
    Simplified as O(M^2 * N)


    -----------------------------------------------------------------------
    OPTIMIZATION - x Parent->Child DAG
                   y Child->Parent DAG
    -----------------------------------------------------------------------

    You brought up a brilliant point: "The DAG has only valid words from source to end."
    This is actually a very common misconception about how the BFS builds the graph. 
    
    The DAG does NOT only contain paths to the endWord. 
    It contains the shortest paths from beginWord to EVERY reachable word in the dictionary, 
    up until the level the target is found.
    
    Let's look at a concrete example to see how dead ends are accidentally captured by the BFS.
    
    The "Dead End" Example
        beginWord: "hit"
        endWord: "cog"
        wordList: ["hot", "dot", "dog", "lot", "log", "cog", "hat", "cat", "can"]
    
    Let's trace the BFS step-by-step:
        Level 1: hit
        Level 2: BFS finds hot and hat.
            Graph so far: hit -> [hot, hat]
        Level 3: BFS processes hot (finds dot, lot) and hat (finds cat).
            Graph so far:
                hit -> [hot, hat]
                hot -> [dot, lot]
                hat -> [cat]
        Level 4: BFS processes dot (finds dog), lot (finds log), and cat (finds can).
            Graph so far:
                hit -> [hot, hat]
                hot -> [dot, lot]
                hat -> [cat]
                dot -> [dog]
                lot -> [log]
                cat -> [can]
        Level 5: BFS processes dog (finds cog), log (finds cog), and can (finds nothing).
                hit -> [hot, hat]
                hot -> [dot, lot]
                hat -> [cat]
                dot -> [dog]
                lot -> [log]
                cat -> [can]
                dog -> [cog]
                log -> [cog]
                can -> []
        targetWordFound is true! BFS stops.
    The Forward DFS Trap
        Look at the graph your BFS just built. It contains this path:
            hit -> hat -> cat -> can
        Because you are running a Forward DFS starting from "hit", your DFS will 
        look at hit's children. It will go down the hat branch. 
        It will traverse all the way to can, check if can == cog, realize it failed, and have to backtrack.
        
        In a massive dictionary with thousands of words, this creates an enormous tree 
        of dead ends. Your forward DFS will explore every single one of those failed 
        branches before it finishes.
*/

// Solution: Parent->Child DAG + Forward DFS
// Suffers from dead-end traversal in DFS (see optimization above)
class Solution {
private:
    void BFS(unordered_set<string>& wordSet
        , unordered_map<string, vector<string>>& graph
        , unordered_map<string, int>& level
        , string beginWord
        , string endWord)
    {
        queue<string> Q;

        int currentLevel = 1;
        level[beginWord] = currentLevel;
        Q.push(beginWord);
        graph[beginWord] = {};
        bool targetWordFound = false;

        while (!Q.empty() && targetWordFound == false) {
            int levelSize = Q.size();
            while (levelSize--) {
                auto word = Q.front();
                Q.pop();

                if (word == endWord) {
                    targetWordFound = true;
                    break;   // endWord has no useful children. Any other word at this
                             // level would only add edges to level+1 which is beyond
                             // the shortest path. So stop processing this level entirely.
                }

                string origWord = word;
                for (int i = 0; i < word.length(); i++) {
                    char origChar = word[i];

                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == origChar)    // if character is same then ignore
                            continue;

                        word[i] = c;
                        if (wordSet.find(word) != wordSet.end()) {  //neighbour node found
                            if (level.find(word) == level.end()) {  //if not visited yet
                                level[word] = level[origWord] + 1;
                                graph[origWord].push_back(word);
                                Q.push(word);
                            }
                            // if already visited and neighbour node is a child then add it to adjList
                            // dog -> 
                            //        cog
                            // log -> 
                            // here if cog is already visited via dog and level[cog] = level[log] + 1 
                            // then add cog to children of log
                            else if (level[word] == level[origWord] + 1) {
                                graph[origWord].push_back(word);
                            }
                        }
                    }
                    word[i] = origChar;
                }
            }
            currentLevel++;
        }
    }

    void DFS(unordered_map<string, vector<string>>& graph, string node, string dest
        , vector<string> path, vector<vector<string>>& allPaths)
    {
        path.push_back(node);
        if (node == dest) {
            allPaths.push_back(path);
            return;
        }
        for (auto& neighbour : graph[node]) {
            DFS(graph, neighbour, dest, path, allPaths);
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordList.empty() || !wordSet.count(endWord))
            return {};

        // build the graph using BFS
        unordered_map<string, vector<string>> graph;
        unordered_map<string, int> level;
        BFS(wordSet, graph, level, beginWord, endWord);

        // DFS to get all paths
        vector<vector<string>> allPaths;
        vector<string> path;
        DFS(graph, beginWord, endWord, path, allPaths);
        return allPaths;
    }
};

// Solution2: Child->Parent DAG + Reverse DFS (optimization)
// BFS builds graph[child] = [parents] instead of graph[parent] = [children]
// DFS starts from endWord and walks back to beginWord.
// Every node DFS visits is guaranteed to be on a valid path to endWord
// because we start FROM endWord — no dead-end branches possible.
//
// Dead end example: beginWord="hit", endWord="cog"
//   wordList=["hot","dot","dog","lot","log","cog","hat","cat","can"]
//
// Parent->Child DAG (Solution):          Child->Parent DAG (Solution2):
//   hit->[hot,hat]                          hot->[hit]
//   hot->[dot,lot]                          hat->[hit]
//   hat->[cat]          DFS from hit        dot->[hot]      DFS from cog
//   dot->[dog]          explores            lot->[hot]      ONLY explores
//   lot->[log]          hat->cat->can       cat->[hat]      cog->dog->dot->hot->hit
//   cat->[can]          dead end!           can->[cat]      cog->log->lot->hot->hit
//   dog->[cog]                              dog->[dot]      can/cat/hat never touched
//   log->[cog]                              log->[lot]
//   can->[]                                 cog->[dog,log]
//
// Reverse DFS from "cog":
//   cog -> parents: [dog, log]
//     dog -> parents: [dot]
//       dot -> parents: [hot]
//         hot -> parents: [hit]
//           hit == beginWord => path=[cog,dog,dot,hot,hit] => reverse => [hit,hot,dot,dog,cog] checkmark
//     log -> parents: [lot]
//       lot -> parents: [hot]
//         hot -> parents: [hit]
//           hit == beginWord => path=[cog,log,lot,hot,hit] => reverse => [hit,hot,lot,log,cog] checkmark
//   hat/cat/can branches never touched since they have no path back to endWord
class Solution2 {
private:
    void BFS(unordered_set<string>& wordSet
        , unordered_map<string, vector<string>>& graph  // graph[child] = [parents]
        , unordered_map<string, int>& level
        , string beginWord
        , string endWord)
    {
        queue<string> Q;
        level[beginWord] = 1;
        Q.push(beginWord);
        bool targetWordFound = false;

        while (!Q.empty() && !targetWordFound) {
            int levelSize = Q.size();
            while (levelSize--) {
                auto word = Q.front();
                Q.pop();

                if (word == endWord) {
                    targetWordFound = true;
                    break;
                }

                string origWord = word;
                for (int i = 0; i < word.length(); i++) {
                    char origChar = word[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == origChar) continue;
                        word[i] = c;
                        if (wordSet.find(word) != wordSet.end()) {
                            if (level.find(word) == level.end()) {
                                level[word] = level[origWord] + 1;
                                graph[word].push_back(origWord);  // child -> parent
                                Q.push(word);
                            }
                            else if (level[word] == level[origWord] + 1) {
                                graph[word].push_back(origWord);  // cross edge: child -> parent
                            }
                        }
                    }
                    word[i] = origChar;
                }
            }
        }
    }

    // DFS from endWord back to beginWord, then reverse the path
    void DFS(unordered_map<string, vector<string>>& graph, string node, string dest
        , vector<string> path, vector<vector<string>>& allPaths)
    {
        path.push_back(node);
        if (node == dest) {
            reverse(path.begin(), path.end());  // reverse to get beginWord->endWord order
            allPaths.push_back(path);
            return;
        }
        for (auto& parent : graph[node]) {
            DFS(graph, parent, dest, path, allPaths);
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordList.empty() || !wordSet.count(endWord))
            return {};

        unordered_map<string, vector<string>> graph;  // graph[child] = [parents]
        unordered_map<string, int> level;
        BFS(wordSet, graph, level, beginWord, endWord);

        vector<vector<string>> allPaths;
        vector<string> path;
        DFS(graph, endWord, beginWord, path, allPaths);  // DFS from endWord to beginWord
        return allPaths;
    }
};
int main()
{
    Solution obj;    
    vector<string> wordList = { "hot","dot","dog","lot","log","cog" };
    auto ladders = obj.findLadders("hit", "cog", wordList);
    for (auto ladder : ladders) {
        for (auto word : ladder)
            cout << word << "";
        cout << endl;
    }
    return 0;
}
