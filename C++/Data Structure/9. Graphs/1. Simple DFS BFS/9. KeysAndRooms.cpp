#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <queue>
#include <unordered_map>
#include <stack>
using namespace std;

/*
	Problem Statement:
	-----------------
	There are n rooms labeled from 0 to n - 1 and all the rooms are locked except for room 0. Your goal is to visit all the rooms. 
    However, you cannot enter a locked room without having its key.
    When you visit a room, you may find a set of distinct keys in it. Each key has a number on it, 
    denoting which room it unlocks, and you can take all of them with you to unlock the other rooms.

    Given an array rooms where rooms[i] is the set of keys that you can obtain if you visited room i, 
    return true if you can visit all the rooms, or false otherwise.

    Examples:
    --------
    Example 1:

    Input: rooms = [[1],[2],[3],[]]
    Output: true
    Explanation:
    We visit room 0 and pick up key 1.
    We then visit room 1 and pick up key 2.
    We then visit room 2 and pick up key 3.
    We then visit room 3.
    Since we were able to visit every room, we return true.

    Example 2:

    Input: rooms = [[1,3],[3,0,1],[2],[0]]
    Output: false
    Explanation: We can not enter room number 2 since the only key that unlocks it is in that room.

	Approach:
	---------
    This is an adjacency list with roomId -> [keyforroom0, keyforroom1....]
	Start the exploration with room 0. 
    Do a DFS/BFS and check if we can visit all the rooms.
*/

class Solution {
public:

    void DFS(int room, vector<vector<int>>& rooms, unordered_set<int>& visited) {

        //visit the room
        visited.insert(room);

        //one by one pick all the keys to other rooms and visit them
        vector<int> keys = rooms[room];
        for (int key : keys) {
            if (visited.find(key) == visited.end())
                DFS(key, rooms, visited);
        }
    }

    bool canVisitAllRooms(vector<vector<int>>& rooms) {

        int numberOfRooms = rooms.size();

        unordered_set<int> visited;

        //Start DFS from room 0
        DFS(0, rooms, visited);

        if (visited.size() != numberOfRooms)
            return false;

        return true;

    }
}; 
int main()
{
	Solution obj;

    vector<vector<int>> rooms = {{1}, {2}, {3}, {}};
    cout << obj.canVisitAllRooms(rooms) << endl;

    rooms = { {1, 3}, {3, 0, 1}, {2}, {0} };
    cout << obj.canVisitAllRooms(rooms) << endl;

    return 0;
}