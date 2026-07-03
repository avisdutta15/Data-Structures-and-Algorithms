
/*
    https://www.youtube.com/watch?v=SmTow5Ht4iU
    https://www.youtube.com/watch?v=tcOcmNHFTTM

    Problem Statement:
    ------------------

    Examples:
    ---------

    Constraints:
    -----------

    Approach:
    ---------
    Approach 1. Make a circular walk.
    The simplest approach is to consider each index as a starting point and check 
    if a car can complete the circular tour starting from that index. 
    If we find a valid starting point, we will return it.

	Logic walkthrough with gas=[1,2,3,4,5], cost=[3,4,5,1,2]:

	startStation=0: gas(1) < cost(3) → skip
	startStation=1: gas(2) < cost(4) → skip
	startStation=2: gas(3) < cost(5) → skip
	startStation=3: gas(4) >= cost(1) ✓
		currentGas = 4 - 1 + gas[4] = 3 + 5 = 8, nextStation=4
		At 4: currentGas(8) >= cost[4](2) ✓ → currentGas = 8 - 2 + gas[0] = 7, nextStation=0
		At 0: currentGas(7) >= cost[0](3) ✓ → currentGas = 7 - 3 + gas[1] = 6, nextStation=1
		At 1: currentGas(6) >= cost[1](4) ✓ → currentGas = 6 - 4 + gas[2] = 5, nextStation=2
		At 2: currentGas(5) >= cost[2](5) ✓ → currentGas = 5 - 5 + gas[3] = 4, nextStation=3
		nextStation == startStation(3) → return 3 ✓

    Approach 2. 
*/

// Time Complexity: O(n^2), Space Complexity: O(1)
class Solution1 {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int n = gas.size();

		for (int startStation = 0; startStation < n; startStation++) {

			// Pruning: if gas at this station is less than cost to leave it,
			// we can't even reach the next station, so skip immediately
			if (gas[startStation] < cost[startStation])
				continue;

			// Try starting the circuit from startStation.
			// We begin by moving from startStation to the next station.
			// currentGas = gas picked up at startStation
			//            - cost to travel from startStation to nextStation
			// currentGas denotes the gas we will have when we reach next station
			int nextStation = (startStation + 1) % n;
			int currentGas = gas[startStation] - cost[startStation];

			// Keep moving forward until we either complete the circuit
			// (nextStation wraps back to startStation) or run out of gas
			while (nextStation != startStation) {
                // add the gas present in the new gas station
				currentGas = currentGas + gas[nextStation];
				// Can we leave nextStation? If not, this startStation doesn't work
				if (currentGas < cost[nextStation])
					break;

				// Travel from nextStation to the station after it:
				// deduct travel cost, advance.
				int travelCost = cost[nextStation];
				nextStation = (nextStation + 1) % n;
				currentGas = currentGas - travelCost;
			}

			// If nextStation wrapped all the way back to startStation,
			// we completed the full circuit — startStation is our answer
			if (nextStation == startStation)
				return startStation;
		}

		// No valid starting station found
		return -1;
	}
};

// Time Complexity: O(n), Space Complexity: O(1)
class Solution2 {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int n = gas.size();

		int totalGas = accumulate(gas.begin(), gas.end(), 0);
		int totalCost = accumulate(cost.begin(), cost.end(), 0);

		// If total gas is less than total cost, it's impossible to complete the circuit
		if (totalGas < totalCost)
			return -1;

		// Else atleast one start station exists		
		int currentGas = 0;
		int startIndex = 0;

		for (int i = 0; i < n; i++) {
			// accumulate net gas at station i (gas gained minus cost to leave)
			currentGas = currentGas + gas[i] - cost[i];

			// If currentGas goes negative, we can't reach i+1 from startIndex.
			// No station between startIndex and i can be a valid start either,
			// because they all had even less gas accumulated before hitting this deficit.
			// So reset and try starting fresh from i+1.
			if (currentGas < 0) {
				currentGas = 0;
				startIndex = i + 1;
			}
		}

		return startIndex;
	}
};

int main() {
	Solution1 obj;
	vector<int> gas = { 1, 2, 3, 4, 5 };
	vector<int> cost = { 3, 4, 5, 1, 2 };
	cout << obj.canCompleteCircuit(gas, cost) << endl;
	return 0;
}