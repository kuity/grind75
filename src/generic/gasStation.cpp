#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/gas-station/description/
Difficulty: Medium
Topics: Array, Greedy
*/
class Solution {
public:
    // The greedy approach is easy but it takes one logical leap to see why it works
    // If we start from gas station 0 and track the cumulative net value
    // at each incremental index
    // Supposing cum net val fails (<0) at some index i,
    // it means the net val at i is negatively large enough to offset cum net val so far
    // but cum net val had been monotonically increasing
    // Therefore even if we start from any index j, where 0<j<i, it's gonna fail at i.
    // So we can proceed to start at i+1 immediately
    //
    // Next we can abuse the fact that there's either no solution or a unique solution
    // If there's no solution, the total net val must be < 0
    // Otherwise, there's a unique solution, therefore 1 pass is enough
    // why? 
    // Imagine we finish 1 pass and answer is i 
    // That means, all indices j, where j<i must be bad
    // and all indices k, where k>=i, are "ok"
    // Now, there's no point doubling back and checking 0<j<i again
    // because if it's bad for i, it MUST also be bad for k>i (monotonically increasing sum)
    // and if it's ok for i, then index i is a solution and therefore the UNIQUE solution
    // so we can simply skip 
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int ans = 0;
        int cumNetVal = 0;
        int total = 0;
        for (auto i=0; i<gas.size(); i++) {
            auto net = gas[i]-cost[i];
            cumNetVal += net;
            total += net;
            if (cumNetVal < 0) {cumNetVal = 0; ans = i+1;}
        }
        return total>=0 ? ans : -1;
    }

    // The problem with a brute force solution is that the time complexity is O(n^2)
    // Issue is that the input data can be crafted such that it really runs in n^2, which is an issue
    int canCompleteCircuitBruteF(vector<int>& gas, vector<int>& cost) {
	vector<int> net;
	int sz = gas.size();
	for (auto i=0; i<sz; i++) net.push_back(gas[i]-cost[i]);

	for(auto i=0; i<sz; i++) {
	    bool found = true;
	    int sum = 0;
	    for(auto j=0; j<sz; j++) {
		int index = (i+j) % sz;
		sum += net[index];
		if (sum < 0) { found = false; break; }
	    }
	    if (found) return i;
	}
	return -1;
    }
};

int main() {
    vector<int> gas = {1,2,3,4,5};
    vector<int> cost = {3,4,5,1,2};
    Solution *S = new Solution();
    auto ans = S->canCompleteCircuit(gas, cost);
    cout << "ans is " << ans << endl;
}
