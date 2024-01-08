#include <iostream>
#include <vector>
#include <queue>

/*
   Keys and Rooms

   There are n rooms labeled from 0 to n - 1 and all the rooms 
   are locked except for room 0. Your goal is to visit all the 
   rooms. However, you cannot enter a locked room without having 
   its key.

   When you visit a room, you may find a set of distinct keys 
   in it. Each key has a number on it, denoting which room it 
   unlocks, and you can take all of them with you to unlock the 
   other rooms.

   Given an array rooms where rooms[i] is the set of keys that 
   you can obtain if you visited room i, return true if you can 
   visit all the rooms, or false otherwise.



   Example 1

   Input - rooms = [[1],[2],[3],[]]
   Output true
   Explanation
   We visit room 0 and pick up key 1.
   We then visit room 1 and pick up key 2.
   We then visit room 2 and pick up key 3.
   We then visit room 3.
   Since we were able to visit every room, we return true.

   Example 2

   Input - rooms = [[1,3],[3,0,1],[2],[0]]
   Output false
   Explanation 
   We can not enter room number 2 since the only key that unlocks it is in that room.


   Constraints

   n == rooms.length
   2 <= n <= 1000
   0 <= rooms[i].length <= 1000
   1 <= sum(rooms[i].length) <= 3000
   0 <= rooms[i][j] < n
   All the values of rooms[i] are unique.

   Solution - O(n).
   Code self-explanatory.

 */

class Solution {
    public:
	bool canVisitAllRooms(std::vector<std::vector<int>>& rooms) {

	    //list of visited rooms. Currently none visited.
	    std::vector<int> visited_rooms(rooms.size(), 0);

	    //queue of keys obtained.
	    std::queue<int> keys;

	    //we have key for room 0.
	    keys.push(0);

	    //start visiting rooms.
	    while(!keys.empty()) {

		//current key at hand.
		auto curr_key = keys.front();

		//if we've already visited the room with the current key...
		if(visited_rooms[curr_key]) {

		    //then throw the key away.
		    keys.pop();
		    continue;
		}

		//otherwise

		//mark the room with current key as visited.
		visited_rooms[curr_key] = 1;

		//put all the keys in that room into the queue.
		for(int i = 0; i < rooms[curr_key].size(); ++i) {
		    keys.push(rooms[curr_key][i]);
		}

		//throw the current key.
		keys.pop();
	    }

	    //check if we've visted all rooms.
	    for(const auto ele: visited_rooms) {
		if(!ele)
		    return false;
	    }

	    return true;
	}
};

int main() {
    std::vector<std::vector<int>> set = {
	{1},
	{2},
	{3},
	{}
    };

    Solution s;
    auto val = s.canVisitAllRooms(set);

    if(val)
	std::cout << "true\n";
    else
	std::cout << "false\n";
}

