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
	https://www.youtube.com/watch?v=ottPfSr3xls

	Problem Statement:
	------------------
	In a town, there are n people labeled from 1 to n. 
	There is a rumor that one of these people is secretly the town judge.
	
	If the town judge exists, then:
		1. The town judge trusts nobody.
		2. Everybody (except for the town judge) trusts the town judge.
		3. There is exactly one person that satisfies properties 1 and 2.
	You are given an array trust where trust[i] = [ai, bi] representing that 
	the person labeled ai trusts the person labeled bi. 
	
	If a trust relationship does not exist in trust array, then such a trust 
	relationship does not exist.
	
	Return the label of the town judge if the town judge exists and can be identified, 
	or return -1 otherwise.
    
	Example:
	--------
	
	Approach: 
    ---------
	if :
		indegree  [i] == n-1
		outdegree [i] == 0
	then i is the town judge.
*/

class Solution {
public:
	int findJudge(int n, vector<vector<int>> &trust) {

		if (trust.size() == 0 && n == 1)
			return 1;
		
		// trust_score array is used to keep track of the number of people who trust a particular 
		// person and the number of people that a particular person trusts.
		// If the value of trust_score[i] is n-1, it means that person i is trusted by everyone else, 
		// and if the value of trust_score[i] is 0, it means that person i trusts no one.
		// If the value of trust_score[i] is neither n-1 nor 0, it means that person i is either 
		// trusted by some people or trusts some people, but not both.
		vector<int> trust_score(n + 1, 0);  // n + 1 for 1 based indexing
		for (auto person : trust) {
			int u = person[0];
			int v = person[1];

			// trust_score[u]--; decrements the trust trust_score of the first person in the pair. 
			// This is done because if the first person trusts the second person, it means that 
			// the first person does not trust themselves.
			trust_score[u]--;
			// trust_score[v]++; increments the trust trust_score of the second person in the pair. 
			// This is done because if the first person trusts the second person, it means 
			// that the second person is trusted by the first person.
			trust_score[v]++;
		}

		for (int person = 0; person < trust_score.size(); person++) {
			// check if there is a person who is trusted by everyone except themselves (n-1 people) 
			// and if such person exists it returns the index of that person.
			// why not trust_score[person] == 0 because 
			// it is possible that a person does not trust anyone.
			// But the townjudge will be trusted by n-1 people for sure.
			if (trust_score[person] == n - 1)
				return person;
		}
		return -1;
	}
};

int main() {

	return 0;
}