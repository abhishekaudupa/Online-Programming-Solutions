#include <iostream>
#include <unordered_map>

/*
   Pow(x, n)

   Implement pow(x, n), which calculates x raised to the power n (i.e., xn).

   Example 1:

   Input- x = 2.00000, n = 10
   Output- 1024.00000

   Example 2:

   Input- x = 2.10000, n = 3
   Output- 9.26100

   Example 3:

   Input- x = 2.00000, n = -2
   Output- 0.25000
   Explanation- 2-2 = 1/22 = 1/4 = 0.25

   Constraints-

   -100.0 < x < 100.0
   -231 <= n <= 231-1
   n is an integer.
   Either x is not zero or n > 0.
   -104 <= xn <= 104

   Solution - O(n), memoized. Code self-explanatory.
 */

class Solution {

    std::unordered_map<int, double> store;

    public:
    double myPow(double x, int n) {
	if(store.find(n) != store.end()) {
	    return store.at(n);
	}

	if(x == 1) {
	    return 1;
	}

	if(n == 0) {
	    store.insert(std::make_pair(0, 1));
	    return 1;
	}

	if(n > 0) {
	    if(n % 2 == 0) {
		auto ans = myPow(x, n / 2) * myPow(x, n / 2);
		store.insert(std::make_pair(n, ans));
		return ans;
	    }

	    auto ans = x * myPow(x, n / 2) * myPow(x, n / 2);
	    store.insert(std::make_pair(n, ans));
	    return ans;
	}

	/*
	   enclosing n / 2 inside parenthesis and then negating is a subtle
	   but very important point to note. Otherwise, there will be an
	   integer overflow/underflow condition when you negate n that is
	   at the extremes of integer datatype bounds.
	 */
	if(n % 2 == 0) {
	    auto ans = 1 / (myPow(x, -(n / 2)) * myPow(x, -(n / 2)));
	    return ans;
	}

	auto ans = 1 / (x * myPow(x, -(n / 2)) * myPow(x, -(n / 2)));
	return ans;
    }
};

int main() {
    std::cout << "Enter x: ";
    double x;
    std::cin >> x;
    std::cout << "Enter n: ";
    int n;
    std::cin >> n;

    Solution s;
    std::cout << s.myPow(x, n) << '\n';
}

