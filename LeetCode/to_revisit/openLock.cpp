#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <random>

/*
   Open the Lock

   You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.

   The lock initially starts at '0000', a string representing the state of the 4 wheels.

   You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.

   Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock, or -1 if it is impossible.



   Example 1:
Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
Output: 6
Explanation:
A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
because the wheels of the lock become stuck after the display becomes the dead end "0102".

Example 2:
Input: deadends = ["8888"], target = "0009"
Output: 1
Explanation: We can turn the last wheel in reverse to move from "0000" -> "0009"

Example 3:
Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
Output: -1
Explanation: We cannot reach the target without getting stuck.

Constraints:
1 <= deadends.length <= 500
deadends[i].length == 4
target.length == 4
target will not be in the list deadends.
target and deadends[i] consist of digits only.

Solution:
	This is my first solution, which apparently, isn't the best approach. But hey, it works!
	
	We do a breadth search starting at 0000 and keep track of the number of steps along the way 
	to reach the target. We do the search using a queue and we keep track of visited nodes using
	an unordered set. What we push to the queue isn't just the lock combination but also the step
	count that lead us to that particular combination (see code).

	Once we reach the target, we check if it was the bare minimum number of steps that led us there.
	If it is, we exit and return the step count, which is the bare min step count. Otherwise, we
	check if the number of steps that lead us to the target is smaller than the previous time's
	min step count. If yes, it becomes the latest min step count that leads to the target.

	Optimizations: 
	1. If during the search, we reach the target in the bare minimum step count, we stop and
	return the step count.
	2. If during the search we happen to have stepped more than the current min step count,
	we stop the search along that path.
	3. Use unordered set to keep track of visited combinations and also the deadend combinations.
	This makes search faster as there are as many searches as there are nodes.
 */

class Solution 
{
    using combo = std::string;
    using comboList = std::vector<combo>;
    using comboSet = std::unordered_set<combo>;
    using step_t = unsigned int;
    using size_t = unsigned int;
    using comboSeq = std::pair<combo, step_t>;
    using comboQue = std::queue<comboSeq>;

    comboSet m_deadends, m_visited;
    step_t bareMinStepCt;
    comboQue m_q;
    bool m_found;

    public:
    /*
       comboList getVec(unsigned int size)
       {
       static std::random_device dev;
       static std::mt19937 rng(dev());
       std::uniform_int_distribution<std::mt19937::result_type> dist6(48,57);
       std::vector<std::string> v(size + 1);

       for(auto i{ 0u }; i < size + 1; ++i)
       {
       v[i].resize(m_width);
       for(auto j{ 0u }; j < m_width; ++j)
       {
       v[i][j] = dist6(rng);
       }
       }
       return v;
       }

       void printTarget(const combo& combo)
       {
       std::cout << "Target: " << combo << '\n';
       }

       void printDeadends(const comboList& deadends)
       {
       if(deadends.size() > 50)
       return;
       std::cout << "Deadends: ";
       for(const auto& ele: deadends)
       std::cout << ele << ' ';
       std::cout << '\n';
       }

       std::pair<combo, comboList> getProblemData(unsigned int size)
       {
       comboList deadends;
       combo  target;
       auto v{ getVec(size) };
       target = v[0];
       for(auto i{ 1u }; i < size + 1; ++i)
       deadends.push_back(v[i]);

       return { target, deadends };
       }

       void printProblem(const std::pair<combo, comboList>& d)
       {
       printTarget(d.first);
       printDeadends(d.second);
       }

       combo getSeed()
       {
       combo seed;
       seed.resize(m_width);
       for(auto i{ 0u }; i < m_width; ++i)
       seed[i] = '0';
       return seed;
       }
     */

    void populateDeadends(const comboList& deadends)
    {
	for(const auto& ele: deadends)
	    m_deadends.insert(ele);
    }

    char increment(char c)
    {
	return (c == '9')? '0': (c + 1);
    }

    char decrement(char c)
    {
	return (c == '0')? '9': (c - 1);
    }

    int minSteps(char c)
    {
	return (c > '5')? (10 - c + '0'): (c - '0');
    }

    step_t getBareMinSteps(const combo& s)
    {
	step_t bareMinSteps{ };
	for(auto i{ 0u }; i < 4; ++i)
	{
	    bareMinSteps += minSteps(s[i]);
	}
	return bareMinSteps;
    }


    combo turnWheel(combo s, int index, bool up)
    {
	if(up)
	{
	    s[index] = increment(s[index]);
	    return s;
	}

	s[index] = decrement(s[index]);
	return s;
    }

    bool isVisited(const combo& cbo)
    {
	return (m_visited.find(cbo) != m_visited.end());
    }

    bool isDeadend(const combo& cbo)
    {
	return (m_deadends.find(cbo) != m_deadends.end());
    }

    void push(const comboSeq& cs)
    {
	if(!isVisited(cs.first))
	{
	    m_q.push(cs);
	    m_visited.insert(cs.first);
	}
    }

    step_t searchWide(const combo& target)
    {
	m_q.push({ "0000", 0 });
	m_visited.insert("0000");
	step_t minStepCount{ };
	--minStepCount;
	m_found = false;

	while(!m_q.empty())
	{
	    auto ele{ m_q.front() };
	    auto curCombo{ ele.first };
	    auto curStep{ ele.second };

	    if(curStep >= minStepCount)
	    {
		m_q.pop();
		continue;
	    }

	    if(curCombo == target)
	    {
		m_found = true;
		if(curStep == bareMinStepCt)
		{
		    return curStep;
		}

		if(curStep < minStepCount)
		{
		    minStepCount = curStep;
		    m_q.pop();
		    continue;
		}
	    }

	    if(isDeadend(curCombo))
	    {
		m_q.pop();
		continue;
	    }

	    for(auto i{ 0u }; i < 4; ++i)
	    {
		push({ turnWheel(curCombo, i, true), curStep + 1 });
		push({ turnWheel(curCombo, i, false), curStep + 1 });
	    }

	    m_q.pop();
	}
	return minStepCount;
    }


    int openLock(comboList& deadends, combo target) 
    {
	populateDeadends(deadends);
	bareMinStepCt = getBareMinSteps(target);
	size_t stepCount{ searchWide(target) };
	return m_found? stepCount: -1;
    }
};

int main()
{
    /*
       Solution s;
       auto data{ s.getProblemData(5000) };
       s.printProblem(data);
       char ch;
       std::cin >> ch;
       s.openLock(data.second, data.first);
     */
}

