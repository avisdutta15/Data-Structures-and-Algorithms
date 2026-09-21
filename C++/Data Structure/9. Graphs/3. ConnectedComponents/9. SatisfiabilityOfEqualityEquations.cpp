#include <algorithm>
#include <iostream>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

/*
	https://www.youtube.com/watch?v=0Z8lt7U_kiE

	Problem Statement:
	------------------
	You are given an array of strings equations that represent relationships between 
	variables where each string equations[i] is of length 4 and takes one of two different 
	forms: 
		"xi==yi" or "xi!=yi".
	Here, xi and yi are lowercase letters (not necessarily different) that represent 
	one-letter variable names.

	Return true if it is possible to assign integers to variable names so as 
	to satisfy all the given equations, or false otherwise.
 
    Example:
	--------
	Example 1:

	Input: equations = ["a==b","b!=a"]
	Output: false
	Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
	There is no way to assign the variables to satisfy both equations.
	
	Example 2:

	Input: equations = ["b==a","a==b"]
	Output: true
	Explanation: We could assign a = 1 and b = 1 to satisfy both equations.

	Approach: 
    ---------
	Equality (==) is transitive: if a==b and b==c, then a==c. 
	This is exactly what DSU models — union all equal variables into the same component. 
	Then for every inequality (!=), check if both variables ended up in the same component. 
	If they did, the constraints contradict each other.
	
	Equations: ["a==b", "b==c", "a!=c"]
		Step 1 (equalities):   Union(a,b), Union(b,c)
			→ a, b, c are all in the same component
		
		Step 2 (inequalities): a != c?
			→ find(a) == find(c) → CONTRADICTION! Return false.

	Why two passes? Equalities must be processed first to build the full connected components. 
	If we interleaved, we might check an inequality before seeing a later equality that connects them.
	
	Time: O(N · α(26)) = O(N) 
	Since α(26) is effectively a constant, N equations, 26 possible characters. 
	Space: O(1) — DSU of fixed size 26.
*/

class DSU {
public:
	vector<int> parent;
	vector<int> rank;

	DSU(int N) {
		parent = vector<int>(N);
		rank = vector<int>(N, 0);
		for (int i = 0; i < N; i++) 
			parent[i] = i;
	}

	int find(int x) {
		if (parent[x] == x)
			return x;
		return parent[x] = find(parent[x]);
	}

	void Union(int x, int y) {
		int x_parent = find(x);
		int y_parent = find(y);
		if (x_parent == y_parent) return;

		if (rank[x_parent] > rank[y_parent]) {
			parent[y_parent] = x_parent;
		}
		else if (rank[y_parent] > rank[x_parent]) {
			parent[x_parent] = y_parent;
		}
		else {
			parent[y_parent] = x_parent;
			rank[x_parent]++;
		}
	}
};

class Solution {
public:
	bool equationsPossible(vector<string>& equations) {
		// 'a==b' -> a and b should be in same component
		// 'a!=b' -> a and b should not be in same component
		// Process all equality equations first
		DSU disjointSet(26);

		for(int i=0; i<equations.size(); i++ )
		{
			string equation = equations[i];
			if(equation[1] == '=') {	// a==b (check the 1st character)
				disjointSet.Union(equation[0]-'a', equation[3]-'a');
			}
		}

		// Now process inequality equations
		for (int i = 0; i < equations.size(); i++) {
			string equation = equations[i];
			if (equation[1] == '!') {
				char first = equation[0];
				char second = equation[3];

				if(disjointSet.find(first-'a') == disjointSet.find(second-'a'))
					return false; // Inequality constraint violated
			}
		}

		return true;
	}
};

int main() {

	return 0;
}