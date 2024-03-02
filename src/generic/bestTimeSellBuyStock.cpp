#include <vector>
#include <iostream>
#include <climits>

using namespace std;

/*
Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
Difficulty: Easy
Topics: array, dp
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
	int min = INT_MAX;
	int maxProfit = 0;
	for (int i=0; i<prices.size(); i++) {
	    int cur = prices[i];
	    if (cur < min) {
		min = cur;
	    }
	    if (cur - min > maxProfit) {
		maxProfit = cur - min;
	    }
	}
	return maxProfit;
    }
};

int main() {
    // vector<int> list1 = {7, 1, 5, 3 ,6, 4};
    vector<int> list1 = {7, 6, 4, 3 ,1};
    Solution *S = new Solution();
    int mp = S->maxProfit(list1);
    cout << mp << endl;
};
