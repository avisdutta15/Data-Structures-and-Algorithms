#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given text string with length n and a pattern with length m, the task is to prints all occurrences of pattern in text.
	Note: You may assume that n > m.

	Examples: 
	---------

	Input:  text = "THIS IS A TEST TEXT", pattern = "TEST"
	Output: Pattern found at index 10


	Input:  text =  "AABAACAADAABAABA", pattern = "AABA"
	Output: Pattern found at index 0, Pattern found at index 9, Pattern found at index 12

	Approach:
	---------
	Rabin Karp using Rolling Hash
*/

class Solution {
public:
	vector<int> search(string s, string p) {
		vector<int> occurrences;

		int sLen = s.length();
		int pLen = p.length();

		//i denotes the starting point of the substring in s.
		//slide p[] over s[]
		for (int i = 0; i < sLen - pLen; i++) {
			int j = i;

			//for current index i, check for pattern match
			//iterate over the pattern j and the substring (i..pLen)
			for (j = i; j < pLen; j++) {
				if (s[i + j] != p[j])
					break;
			}

			//if the pattern and substring matched then j will be at pLen
			if (j == pLen)
				occurrences.push_back(i);
		}
		return occurrences;
	}

	//returns the list of starting indices of s where p matches with the substring of s
	//Rabin Karp using pow() for polynomial calculation, 2 as base  
	vector<int> searchRabinKarpNaive(string s, string p) {
		vector<int> occurrences;

		int sLen = s.length();
		int pLen = p.length();

		int pHash = 0;
		int sHash = 0;

		//calculate the hash of p and the first window in s
		for (int i = 0; i < pLen; i++) {
			pHash = pHash + (p[i] * pow(2, pLen - i - 1));
			sHash = sHash + (s[i] * pow(2, pLen - i - 1));
		}

		for (int i = pLen; i < sLen; i++) {
			//check if the previous window matches or not
			if (pHash == sHash && s.substr(i - pLen, pLen) == p)
				occurrences.push_back(i - pLen);

			//subtract the first character from the hash
			sHash = sHash - (s[i - pLen] * pow(2, pLen - 1));

			//adjust the powers of each element
			sHash = sHash * 2;

			//add the new element at the end
			sHash = sHash + s[i];
		}

		//for the last window
		if (pHash == sHash && s.substr(sLen - pLen, pLen) == p)
			occurrences.push_back(sLen - pLen);

		return occurrences;
	}

	//Rabin Karp using pow() for polynomial calculation, 2 as base.
	//Optimization - Precalculate the last first power i.e. x^m-1
	vector<int> searchOptimized1(string s, string p) {
		vector<int> occurrences;

		int sLen = s.length();
		int pLen = p.length();

		int pHash = 0;
		int sHash = 0;

		//When we subtract the first character of the window from the sHash,
		//we compute pow(2, pLen-1). This is costly! O(log(pLen-1)) called sLen-pLen times
		//totalling to O((sLen-pLen) * (log(pLen-1)). We can reduce this to O(sLen-pLen)
		//by precomputing it.
		int power = 1;
		for (int i = 1; i <= pLen - 1; i++) {
			power = (power * 2);
		}


		for (int i = 0; i < pLen; i++) {
			pHash = pHash + (p[i] * pow(2, pLen - i - 1));
			sHash = sHash + (s[i] * pow(2, pLen - i - 1));
		}

		for (int i = pLen; i < sLen; i++) {
			//check if the previous window matches or not
			if (pHash == sHash && s.substr(i - pLen, pLen) == p)
				occurrences.push_back(i - pLen);

			//subtract the first character from the hash
			sHash = sHash - (s[i - pLen] * power);

			//adjust the powers of each element
			sHash = sHash * 2;

			//add the new element at the end
			sHash = sHash + s[i];
		}

		//for the last window
		if (pHash == sHash && s.substr(sLen - pLen, pLen) == p)
			occurrences.push_back(sLen - pLen);

		return occurrences;
	}

	//Rabin Karp using 2 as base.
	//Optimization - Precalculate the last first power i.e. x^m-1
	//			   - Instead of pow() use Horner's method for polynomial evaluation
	vector<int> searchOptimized2(string s, string p) {
		vector<int> occurrences;

		int sLen = s.length();
		int pLen = p.length();

		int pHash = 0;
		int sHash = 0;

		//When we subtract the first character of the window from the sHash,
		//we compute pow(2, pLen-1). This is costly! O(log(pLen-1)) called sLen-pLen times
		//totalling to O((sLen-pLen) * (log(pLen-1)). We can reduce this to O(sLen-pLen)
		//by precomputing it.
		int power = 1;
		for (int i = 1; i <= pLen - 1; i++) {
			power = (power * 2);
		}

		//Instead of evaluating the polynomial in the following way, 
		//lets use Hornor's method. 
		//10.x^3 + 20.x^2 + 2.x + 5
		//x.(10.x^2 + 20.x + 2) + 5
		//x.(x.(10x + 20) + 2 ) + 5
		//x.(x.(x.(10) + 20) + 2 ) + 5
		/*
		for (int i = 0; i < pLen; i++) {
			pHash = pHash + (p[i] * pow(2, pLen - i - 1));
			sHash = sHash + (s[i] * pow(2, pLen - i - 1));
		}
		*/
		pHash = 0, sHash = 0;

		for (int i = 0; i < pLen; i++) {
			pHash = (pHash * 2) + p[i];
			sHash = (sHash * 2) + s[i];
		}

		for (int i = pLen; i < sLen; i++) {
			//check if the previous window matches or not
			if (pHash == sHash && s.substr(i - pLen, pLen) == p)
				occurrences.push_back(i - pLen);

			//subtract the first character from the hash
			sHash = sHash - (s[i - pLen] * power);

			//adjust the powers of each element
			sHash = sHash * 2;

			//add the new element at the end
			sHash = sHash + s[i];
		}

		//for the last window
		if (pHash == sHash && s.substr(sLen - pLen, pLen) == p)
			occurrences.push_back(sLen - pLen);

		return occurrences;
	}

	//Rabin Karp using 2 as base.
	//Optimization - Precalculate the last first power i.e. x^m-1
	//			   - Instead of pow() use Horner's method for polynomial evaluation
	//			   - Use % operation using a large number 10^31 to reduce collision
	vector<int> searchOptimized3(string s, string p) {
		vector<int> occurrences;

		int sLen = s.length();
		int pLen = p.length();

		int pHash = 0;
		int sHash = 0;
		long long int MOD = 10e9 + 7;

		int power = 1;
		for (int i = 1; i <= pLen - 1; i++) {
			power = (power * 2) % MOD;
		}

		for (int i = 0; i < pLen; i++) {
			pHash = ((pHash * 2) + p[i]) % MOD;
			sHash = ((sHash * 2) + s[i]) % MOD;
		}

		for (int i = pLen; i < sLen; i++) {
			//check if the previous window matches or not
			if (pHash == sHash && s.substr(i - pLen, pLen) == p)
				occurrences.push_back(i - pLen);

			//subtract the first character from the hash
			sHash = (sHash - (s[i - pLen] * power) % MOD) % MOD;
			if (sHash < 0) {
				sHash = sHash + MOD;
			}

			//adjust the powers of each element
			sHash = (sHash * 2) % MOD;

			//add the new element at the end
			sHash = (sHash + s[i]) % MOD;
		}

		//for the last window
		if (pHash == sHash && s.substr(sLen - pLen, pLen) == p)
			occurrences.push_back(sLen - pLen);

		return occurrences;
	}

	//Rabin Karp.
	//Optimization - Precalculate the last first power i.e. x^m-1
	//			   - Instead of pow() use Horner's method for polynomial evaluation
	//			   - Use % operation using a large number 10^31 to reduce collision
	//			   - Use a prime number e.g. 31 as BASE instead of 2 to reduce collision.
	//				 BASE = 2 (poor choice)
	//				 hash("ab") = 'a' * 2 + 'b' = 97 * 2 + 98 = 292
	//				 hash("ba") = 'b' * 2 + 'a' = 98 * 2 + 97 = 293
	//				 Only 1 difference - high collision risk
	//				 BASE = 31 (good choice)  
	//				 hash("ab") = 'a' * 31 + 'b' = 97 * 31 + 98 = 3105
	//				 hash("ba") = 'b' * 31 + 'a' = 98 * 31 + 97 = 3135
	//				 30 difference - better separation
	vector<int> searchOptimized4(string s, string p) {
		vector<int> occurrences;

		int sLen = s.length();
		int pLen = p.length();

		if (pLen > sLen) return occurrences;

		const long long BASE = 31;
		const long long MOD = 1e9 + 7;

		// Precompute BASE^(pLen-1) % MOD
		long long power = 1;
		for (int i = 0; i < pLen - 1; i++) {
			power = (power * BASE) % MOD;
		}

		// Calculate hash for pattern and first window of text
		long long pHash = 0, sHash = 0;
		for (int i = 0; i < pLen; i++) {
			pHash = ((pHash * BASE) + p[i]) % MOD;
			sHash = ((sHash * BASE) + s[i]) % MOD;
		}

		// Rolling hash for remaining windows
		for (int i = pLen; i < sLen; i++) {
			// Check last window
			if (pHash == sHash && s.substr(i - pLen, pLen) == p) {
				occurrences.push_back(i - pLen);
			}

			// Remove leftmost character
			sHash = (sHash - (s[i - pLen] * power) % MOD) % MOD;
			if (sHash < 0) {
				sHash = sHash + MOD;
			}

			//adjust the powers of each element
			sHash = (sHash * BASE) % MOD;

			// Add new character on the right
			sHash = (sHash + s[i]) % MOD;
		}

		//for the last window
		if (pHash == sHash && s.substr(sLen - pLen, pLen) == p)
			occurrences.push_back(sLen - pLen);

		return occurrences;
	}
};

int main() {
	Solution obj;

	// Test searchOptimized4
	cout << "Testing searchOptimized4:" << endl;
	auto occurrences4 = obj.searchOptimized4("aabaacaadaabaaba", "aaba");
	for (int i : occurrences4) {
		cout << i << " ";
	}
	cout << endl;

	return 0;
}