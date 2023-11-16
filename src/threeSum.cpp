#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include "../lib/util.h"

using namespace std;

class Solution {
public:
    // Prebuilding a "positional" reference
    vector<vector<int>> threeSum(vector<int>& nums) {
	set<vector<int>> ans;
	unordered_map<int, int> counts;
	// just store the largest index
	unordered_map<int, int> posRef;
	for (int i=0; i<nums.size(); i++) {
	    posRef[-nums[i]] = i;
	}

	// We'll go through each possible pair
	counts[nums[0]] = 1;
	for (int i=1; i<nums.size(); i++) {
	    if (counts[nums[i]] > 1) {
		continue;
	    }
	    for (int j=0; j<i; j++) {
		// cout << "i is " << i << ", j is " << j << endl;
		int pairSum = nums[i] + nums[j];
		if (posRef.find(pairSum) != posRef.end()) {
		    if (posRef[pairSum] > i) {
			// cout << "found " << pos << ": " << -pairSum << endl;
			vector<int> newVec = {nums[i], nums[j], -pairSum};
			sort(newVec.begin(), newVec.end());
			ans.insert(newVec);
		    }
		}
	    }
	    counts[nums[i]]++;
	}

	vector<vector<int>> ansVec(ans.begin(), ans.end());
        return ansVec;
    }

    // First method. Is too slow
    vector<vector<int>> threeSumOld(vector<int>& nums) {
	unordered_map<int, int>	 numCounts;
	unordered_map<int, vector<vector<int>>> num2pairs;
	vector<vector<int>> ans;

	for (int n: nums) {
	    // get the possible pairs so far, that sum to -n 
	    if (num2pairs.find(-n) != num2pairs.end()) {
		for (auto p: num2pairs[-n]) {
		    vector<int> newTrio = p;
		    int freq = count(p.begin(), p.end(), n) + 1;
		    if (freq > numCounts[n]) {
			p.push_back(n);
			ans.push_back(p);
		    }
		}
	    }

	    // update num2pairs;
	    if (numCounts[n]==1) {
		num2pairs[2*n].push_back({n, n});
	    } else if (numCounts[n]==0) {
		for (const auto& p : numCounts) {
		    if (p.second > 0) {
			int x = p.first;
			int newSum = x + n;
			num2pairs[newSum].push_back({x, n});
		    }
		}
	    }

	    // Only update counts at the very end
	    numCounts[n]++;
	}

        return ans;
    }


};

int main() {
    Solution *S = new Solution();
    vector<int> v = {-1, 0, 1, 2, -1, -4};
    const auto &ans = S->threeSum(v);
    cout << "case 1" << endl;
    printVecVec(ans);

    v = {0,1,1};
    const auto &ans2 = S->threeSum(v);
    cout << "case 2" << endl;
    printVecVec(ans2);

    v = {0,0,0};
    const auto &ans3 = S->threeSum(v);
    cout << "case 3" << endl;
    printVecVec(ans3);

    cout << "case 4" << endl;
c    v = {-2,0,1,1,2};
    printVec(v);
    const auto &ans4 = S->threeSum(v);
    printVecVec(ans4);

}
