#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>
using namespace std;

/*
	Problem Statement:
	-----------------
	The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.

	For example, "ACGAATTCCG" is a DNA sequence.
	When studying DNA, it is useful to identify repeated sequences within the DNA.

	Given a string s that represents a DNA sequence, return all the 10-letter-long sequences 
	(substrings) that occur more than once in a DNA molecule. You may return the answer in any order.

	Examples:
	---------
	Example 1:
	Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
	Output: ["AAAAACCCCC","CCCCCAAAAA"]

	Example 2:
	Input: s = "AAAAAAAAAAAAA"
	Output: ["AAAAAAAAAA"]

	Approach:
	---------
	Approach 1: Naive Hash Map (String Keys)
		The most intuitive solution is to simply extract every possible substring of length 10, 
		store it in a generic Hash Map (std::unordered_map), and count occurrences.

		Logic:
		Loop from index 0 to N-10.
		Extract substring(i, 10).
		Increment count in the map.
		If count becomes 2, add to results.
	
		Time Complexity: O((N-L). L) approx O(10N). String hashing and copying take O(L)
		(where L=10).
		Space Complexity: O((N-L). L). We store potentially N strings of length 10 in memory.

	Approach 2: Rolling Hash (Rabin-Karp)
	We can optimize the time complexity by avoiding string 
	copying and re-hashing. Instead of processing 10 characters every step, we use a Rolling Hash 
	to update the hash value in O(1).
	Optimization:Treat the string as a Base-4 number (A=0, C=1, G=2, T=3).
	Roll: Remove the leading digit (most significant) and add the trailing digit (least significant).

	Time Complexity: O(N). Hashing is O(1) per step.
	Space Complexity: O(N). The map stores integer keys instead of strings, saving significant memory.

	Approach 3: Bit Manipulation (2-Bit Encoding) - [TODO]
	This is the standard industry optimization for DNA problems. Since we only have 4 characters, 
	we don't need a full byte (8 bits) or an integer base. We can map them to 2 bits:
		A -> 00
		C -> 01
		G -> 10
		T -> 11
	A 10-letter sequence requires 10 x 2 = 20 bits. 
	This fits perfectly inside a standard 32-bit int.
	
	Logic:Instead of mathematical multiplication/subtraction, we use Shift (<<) and Mask (&) operators.
	1. Shift Left: 
		val << 2 moves the window.
	2. Add New: 
		val | char_code adds the new character.
	3. Mask: 
		val & 0xFFFFF keeps only the last 20 bits (clears the bit that "fell off" the left side).

	Time: O(N).
	Space: O(N) for the map.
*/

class Solution {
private:
	int getNum(char c) {
		switch (c) {
		case 'A': return 0;
		case 'C': return 1;
		case 'G': return 2;
		case 'T': return 3;
		default: return 0;
		}
	}
public:
	vector<string> findRepeatedDnaSequencesNaive(string s) {
		vector<string> repeatedDNASequences;
		if (s.length() == 0 || s.length() < 10)
			return repeatedDNASequences;
		unordered_map<string, int> substringFreq;

		for (int i = 0; i < s.length() - 10 + 1; i++) {
			string substring = s.substr(i, 10);
			substringFreq[substring]++;
			if (substringFreq[substring] == 2)
				repeatedDNASequences.push_back(substring);
		}
		return repeatedDNASequences;
	}

	vector<string> findRepeatedDnaSequencesBitMasking(string s) {
		if (s.length() < 10) return {};

		vector<string> repeatedDNASequences;
		unordered_map<int, int> seen;

		// Specific map for bit manipulation: A=0(00), C=1(01), G=2(10), T=3(11)
		// Note: The ASCII logic below is a quick hack to map A,C,G,T to 0,1,2,3
		// A(65)&7=1, C(67)&7=3, G(71)&7=7, T(84)&7=4 (Collision prone in general, but specific map is safer)
		unordered_map<char, int> toInt = { {'A', 0}, {'C', 1}, {'G', 2}, {'T', 3} };

		int currentVal = 0;

		// Process first 9 chars (prep loop)
		for (int i = 0; i < 9; i++) {
			currentVal = (currentVal << 2) | toInt[s[i]];
		}

		for (int i = 9; i < s.length(); i++) {
			// 1. Shift left by 2 bits to make room
			// 2. OR with new character bits
			// 3. AND with 0xFFFFF (20 ones) to keep only last 20 bits
			currentVal = ((currentVal << 2) | toInt[s[i]]) & 0xFFFFF;

			seen[currentVal]++;
			if (seen[currentVal] == 2) {
				repeatedDNASequences.push_back(s.substr(i - 9, 10));
			}
		}
		return repeatedDNASequences;
	}

	vector<string> findRepeatedDnaSequencesRollingHash(string s) {
		vector<string> repeatedDNASequences;
		if (s.length() == 0)
			return repeatedDNASequences;

		int sLen = s.length();
		long long int sHash = 0;
		int dnaHash = 0;
		long long int power = 1;
		long long int MOD = 10e9 + 7;
		long long int BASE = 5;
		unordered_map<long long int, int> hashFreq;

		//pre-calculate the power. i.e. x^m-1. Here m = 10
		for (int i = 1; i <= 9; i++) {
			power = (BASE * power)%MOD;
		}

		//calculate the hash for the first window
		for (int i = 0; i < 10; i++) {
			sHash = ((sHash * BASE)%MOD + getNum(s[i]))%MOD;
		}

		//store the first hash in the map
		hashFreq[sHash] = 1;

		for (int i = 10; i < sLen; i++) {
			sHash = (sHash - (getNum(s[i - 10]) * power)%MOD)%MOD;
			sHash = (sHash * BASE) % MOD;
			sHash = (sHash + getNum(s[i])) % MOD;

			hashFreq[sHash]++;

			if (hashFreq[sHash] == 2) {
				repeatedDNASequences.push_back(s.substr(i-9, 10));
			}
		}

		return repeatedDNASequences;
	}
};

int main() {
	Solution obj;

	string s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
	vector<string> repeatedDNASequences = obj.findRepeatedDnaSequencesNaive(s);
	for (auto s : repeatedDNASequences) {
		cout << s << " ";
	}
	cout << endl;

	s = "AAAAAAAAAAAAA";
	repeatedDNASequences = obj.findRepeatedDnaSequencesNaive(s);
	for (auto s : repeatedDNASequences) {
		cout << s << " ";
	}
	cout << endl;

	return 0;
}