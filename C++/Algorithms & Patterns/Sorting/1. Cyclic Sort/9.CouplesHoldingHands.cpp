#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	There are n couples sitting in 2n seats arranged in a row and want to hold hands.

	The people and seats are represented by an integer array row where row[i] is the ID of the person sitting in 
	the ith seat. The couples are numbered in order, the first couple being (0, 1), the second couple being (2, 3), 
	and so on with the last couple being (2n - 2, 2n - 1).

	Return the minimum number of swaps so that every couple is sitting side by side. A swap consists of 
	choosing any two people, then they stand up and switch seats.

	Examples:
	---------
	Input: row = [0,2,1,3]
	Output: 1
	Explanation: We only need to swap the second (row[1]) and third (row[2]) person.

	Input: row = [3,2,0,1]
	Output: 0
	Explanation: All couples are already seated side by side.

	Approach: 
	----------
	1. Brute Force:
		If we observe closely, 
			if person == even_element
				partner = person + 1	i.e. odd_element
			if A[i] == odd_element
				partner = person - 1	i.e. even_element

		We loop through the array.
			Check if partner == expected_partner (get from above logic)
			if not then:
				iterate the array from i+2 and find the expected_partner
					swap the A[i+1] and A[expected_partner_index] 
					i.e. swap the imposter and the expected_partner
					swap_count++;
					break;

		Time Complexity: O(N^2)
		Space Complexity : O(1)

	2. Optimization:
		When we realize that the neighbour is not the expected_partner then
		loop through the rest of the array to find the position of the expected_partner.

		Instead of this, we have a cache/map of <person, index> then we can do O(1)
		lookup to find the index of the expected_partner.

		Once found we can swap them and update the position_map.

		Time Complexity: O(N)
		Space Complexity: O(N)

	TRICK TO FIND THE expected_partner
	The Binary Pattern
	Let's look at the first few numbers in binary (using 3 bits for simplicity):

	Couple 1:
		0 = 000
		1 = 001

	Couple 2:
		2 = 010
		3 = 011

	Couple 3:
		4 = 100
		5 = 101

	The "Aha!" Observation: Notice that for every single valid couple, their binary representations 
	are 100% identical except for the very last bit (the Least Significant Bit, or LSB).
		The even person always ends in a 0.
		The odd person always ends in a 1.

	What XOR 1 (^ 1) Actually Does
	The bitwise XOR operator (^) compares two bits. 
		If the bits are different, it returns 1. 
		If they are the same, it returns 0.
	
	When you XOR any number by 1 (001 in binary), you are leaving all the higher bits completely 
	alone (because XORing by 0 changes nothing), but you are forcing the last bit to flip.
	
		If the last bit is 0 (an even number): 0 ^ 1 = 1. It flips to 1, giving you the odd partner.
		Example: 4 ^ 1 -> 100 ^ 001 = 101 (which is 5).
		If the last bit is 1 (an odd number): 1 ^ 1 = 0. It flips to 0, giving you the even partner.
		Example: 3 ^ 1 -> 011 ^ 001 = 010 (which is 2).
*/

class Solution {
private:
	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}
	int getExpectedPartner(int person) {
		int partner = 0;
		if (person % 2 == 0)
			partner = person + 1;
		else
			partner = person - 1;
		return partner;
	}

public:
	int minSwapsCouples(vector<int> row) {
		int swaps = 0;

		// Iterate through the row in pairs
		for (int i = 0; i < row.size(); i = i + 2) {
			int person_1 = row[i];
			int expected_partner = getExpectedPartner(person_1);

			//if the person seated next is not the expected_partner
			if (row[i + 1] != expected_partner) {

				// Brute force: Search the rest of the array for the partner
				for (int j = i + 2; j < row.size(); j++) {

					// Found them! Swap the imposter with the real partner
					if (row[j] == expected_partner) {
						swap(row[j], row[i + 1]);
						swaps++;
						break;	// Stop searching once we've made the swap
					}
				}
			}
		}

		return swaps;
	}
};

class Solution2 {
private:
	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}
public:
	int minSwapsCouples(vector<int> row) {
		int swaps = 0;

		// Iterate through the row in pairs
		for (int i = 0; i < row.size(); i = i + 2) {
			int person_1 = row[i];
			int expected_partner = person_1 ^ 1;					//TRICK

			//if the person seated next is not the expected_partner
			if (row[i + 1] != expected_partner) {

				// Brute force: Search the rest of the array for the partner
				for (int j = i + 2; j < row.size(); j++) {

					// Found them! Swap the imposter with the real partner
					if (row[j] == expected_partner) {
						swap(row[j], row[i + 1]);
						swaps++;
						break;	// Stop searching once we've made the swap
					}
				}
			}
		}

		return swaps;
	}
};

class Solution3 {
private:
	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}
public:
	int minSwapsCouples(vector<int> &row) {
		int swaps = 0;

		unordered_map<int, int> seatCache;
		for (int i = 0; i < row.size(); i++) {
			seatCache[row[i]] = i;
		}

		// Iterate through the row in pairs
		for (int i = 0; i < row.size(); i = i + 2) {
			int person_1 = row[i];
			int expected_partner = person_1 ^ 1;

			//if the person seated next is not the expected_partner
			if (row[i + 1] != expected_partner) {

				//get the seat index of the expected_partner
				int expected_partner_seat_index = seatCache[expected_partner];

				//update the seatcache
				seatCache[row[i + 1]] = expected_partner_seat_index;
				seatCache[row[expected_partner_seat_index]] = i + 1;

				//swap the contents
				swap(row[i+1], row[expected_partner_seat_index]);
				swaps++;				
			}
		}

		return swaps;
	}
};


int main()
{
	Solution obj;
	vector<int> A = { 0,2,1,3 };
	cout << obj.minSwapsCouples(A) << endl;

	Solution2 obj2;
	cout << obj2.minSwapsCouples(A) << endl;

	Solution3 obj3;
	cout << obj3.minSwapsCouples(A) << endl;


	return 0;
}