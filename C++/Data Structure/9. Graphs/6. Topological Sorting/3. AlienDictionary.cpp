#include <iostream> 
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement:
    ------------------
    Alien Dictionary (LeetCode 269 / GFG)

    Given a sorted list of words from an alien language, find the order
    of characters in that language.

    The words are sorted lexicographically according to the rules of
    the alien language. Derive the character ordering from the given
    sorted word list.

    If no valid ordering exists (contradictory data), return "".
    If multiple valid orderings exist, return any one.

    Examples:
    ---------

    Example 1:
        Input:  words = ["wrt", "wrf", "er", "ett", "rftt"]
        Output: "wertf"
        Explanation:
            "wrt" vs "wrf" → t < f
            "wrf" vs "er"  → w < e
            "er"  vs "ett" → r < t
            "ett" vs "rftt"→ e < r
            Edges: t→f, w→e, r→t, e→r
            Topo order: w → e → r → t → f → "wertf"

    Example 2:
        Input:  words = ["z", "x"]
        Output: "zx"
        Explanation:
            "z" vs "x" → z < x. Only ordering: z before x.

    Example 3:
        Input:  words = ["z", "x", "z"]
        Output: ""
        Explanation:
            "z" vs "x" → z < x
            "x" vs "z" → x < z
            Contradiction (cycle): z < x < z. Return "".

    Example 4:
        Input:  words = ["abc", "ab"]
        Output: ""
        Explanation:
            "abc" comes before "ab" but "abc" is longer and "ab"
            is a prefix of "abc". In any valid dictionary, shorter
            prefixes come first. This is invalid input.

    Constraints:
    ------------
    - 1 <= words.length <= 100
    - 1 <= words[i].length <= 100
    - words[i] consists of only lowercase English letters.

    Approach: Topological Sort (Kahn's Algorithm)
    ----------------------------------------------

    Intuition:
    ----------
    The sorted word list encodes ordering relationships between
    characters. We need to extract those relationships and find
    a global ordering that satisfies all of them.

    This is exactly topological sorting on a directed graph.

    Step 1: How to extract edges from the word list?

        Compare every pair of adjacent words (words[i], words[i+1]).
        Find the FIRST position where they differ. That gives us
        one ordering rule:

            words[i][j] comes BEFORE words[i+1][j]

        Only the FIRST differing character gives valid information.
        Characters after that are ordered relative to a different
        prefix and tell us nothing about the alien alphabet.

        Example: "abc" vs "adc"
            j=0: a == a → skip
            j=1: b != d → b comes before d → edge b → d
            j=2: don't look here — the words already diverged at j=1

    Note on Graph Creation:
    -----------------------
    How we build the graph here is different from typical graph problems.

    In Course Schedule, the edges are given to us directly:
        prerequisites = [[1,0], [2,0]] → edges 0→1, 0→2. Done.

    Here, no edges are given. We DERIVE them from the sorted word list.
    The word list is like a dictionary — the fact that "ccd" appears
    before "cba" tells us something about character ordering.

    Think of it like this: how do you look up words in an English
    dictionary? You compare character by character. "cat" comes before
    "dog" because 'c' < 'd'. "cat" comes before "cup" because at
    position 1, 'a' < 'u'. You only look at the FIRST difference.

    Same logic here, but the alphabet is unknown. Each adjacent word
    pair gives us one "clue" — one edge in the graph:

        words[i] vs words[i+1]
        → find first j where words[i][j] != words[i+1][j]
        → that means words[i][j] < words[i+1][j] in this alien alphabet
        → add edge: words[i][j] → words[i+1][j]

    Why only adjacent pairs? Because the list is sorted. If word A
    comes before word B and word B comes before word C, comparing
    A vs B and B vs C captures all the information. Comparing A vs C
    would be redundant (transitive).

    Why only the FIRST differing character? Because once characters
    differ at position j, the ordering is decided there. Characters
    at position j+1, j+2, etc. are compared only when the first j
    characters are identical — which they're not in this case.

    So the graph has:
        - Nodes: every unique character across all words
        - Edges: one per adjacent word pair (at most n-1 edges)

    Once the graph is built, it's a standard topological sort — same
    as Course Schedule.

    Step 2: Handle the invalid prefix case.

        If word1 is longer than word2 AND word2 is a prefix of word1,
        the input is invalid. In any dictionary, "ab" must come before
        "abc". If we see "abc" before "ab", return "".

    Step 3: Topological sort (Kahn's BFS).

        Build a graph from the edges. Compute indegrees. BFS from
        all indegree-0 nodes. If all characters are visited, the
        BFS order is a valid alien alphabet. If not, a cycle exists
        (contradictory rules) — return "".

    Dry Run (words = ["ccd", "cba", "dab", "a", "ada", "aad", "bad", "baa"]):
    --------------------------------------------------------------------------

    Edge extraction (compare adjacent pairs):
        "ccd" vs "cba" → c==c, c!=b → c < b → edge c→b
        "cba" vs "dab" → c!=d       → c < d → edge c→d
        "dab" vs "a"   → d!=a       → d < a → edge d→a
        "a"   vs "ada" → a==a, "a" is shorter prefix → valid, no edge
        "ada" vs "aad" → a==a, d!=a → d < a → edge d→a (duplicate, skip)
        "aad" vs "bad" → a!=b       → a < b → edge a→b
        "bad" vs "baa" → b==b, a==a, d!=a → d < a (duplicate, skip)

    Graph:                Indegree:
        c → {b, d}          c: 0
        d → {a}              d: 1  (from c→d)
        a → {b}              a: 1  (from d→a)
                             b: 2  (from c→b, a→b)

    Kahn's BFS:
        Queue = [c]  (only indegree-0 node)

        Pop c → result = "c"
            c→b: indegree[b] = 2→1
            c→d: indegree[d] = 1→0, push d.   Queue = [d]

        Pop d → result = "cd"
            d→a: indegree[a] = 1→0, push a.   Queue = [a]

        Pop a → result = "cda"
            a→b: indegree[b] = 1→0, push b.   Queue = [b]

        Pop b → result = "cdab"
            No neighbors.                      Queue = []

    visited.size() (4) == indegree.size() (4) → valid!
    Answer: "cdab" ✓

    Bug to watch out for:
    ---------------------
    When comparing two words and finding c1 != c2, you must BREAK
    even if the edge already exists (duplicate). Without breaking,
    the loop continues comparing later characters which gives
    WRONG edges. Always break on the first mismatch.

    Complexity Analysis:
    --------------------
    Time  : O(C + V + E)
            C = total characters across all words (for initialization)
            V = number of unique characters
            E = number of edges (at most n-1, one per adjacent pair)
    Space : O(V + E) — graph + indegree map + queue.

*/

class Solution {
public:
    string findOrder(vector<string>& words) {
        int n = words.size();

        // STEP 1: Register all characters in the graph and indegree map.
        // This ensures characters that have no ordering constraints
        // (never appear in a first-mismatch) still show up with indegree 0.
        unordered_map<char, unordered_set<char>> graph;
        unordered_map<char, int> indegree;

        for (const string& word : words) {
            for (const char& c : word) {
                graph[c];          // create entry if it doesn't exist
                indegree[c] = 0;   // initialize indegree to 0
            }
        }

        // STEP 2: Compare adjacent words to extract ordering edges.
        for (int i = 0; i <= n - 2; i++) {
            string word1 = words[i];
            string word2 = words[i + 1];

            int commonCharsLen = min(word1.length(), word2.length());

            // Invalid case: word1 is longer but word2 is a prefix of word1.
            // e.g., "abc" before "ab" is impossible in any valid dictionary.
            if (word1.size() > word2.size()
                && word1.substr(0, commonCharsLen) == word2.substr(0, commonCharsLen))
                return "";

            // Find the FIRST position where the two words differ.
            // That character pair gives us one ordering rule.
            for (int j = 0; j < commonCharsLen; j++) {
                char c1 = word1[j], c2 = word2[j];
                if (c1 != c2) {
                    // c1 comes before c2 in the alien alphabet → edge c1 → c2
                    if (graph[c1].count(c2) == 0) {
                        graph[c1].insert(c2);
                        indegree[c2]++;
                    }
                    // IMPORTANT: always break on first mismatch.
                    // Later characters don't give valid ordering info.
                    break;
                }
            }
        }

        // STEP 3: Kahn's BFS — topological sort.
        // Start with all characters that have indegree 0 (no prerequisites).
        queue<char> Q;
        for (auto& c : indegree) {
            if (c.second == 0) {
                Q.push(c.first);
            }
        }

        string result = "";
        while (!Q.empty()) {
            char u = Q.front();
            Q.pop();

            // Append this character to the alien alphabet order
            result += u;

            // For every character v that must come after u:
            for (char v : graph[u]) {
                indegree[v]--;  // u is placed, v has one less dependency

                // If v has no more dependencies, it's ready to be placed
                if (indegree[v] == 0) {
                    Q.push(v);
                }
            }
        }

        // STEP 4: If we placed all characters, the ordering is valid.
        // If not, a cycle exists (contradictory rules) — return "".
        if (result.size() != indegree.size())
            return "";

        return result;
    }
};

int main() {
    Solution obj;
    vector<string> words = { "ccd", "cba", "dab", "a", "ada", "aad", "bad", "baa" };
    cout << obj.findOrder(words) << endl;
}
