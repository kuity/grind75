#include <iostream>
#include <vector>

using namespace std;

/*
Link: https://leetcode.com/problems/subsets/description/
Difficulty: Medium
Topics: array, backtracking, bit manipulation
*/
class Solution {
private:
public:
    vector<vector<int>> subsets(vector<int>& nums) {
	vector<vector<int>> ans = {{}};
	for (auto n: nums) {
	    auto l = ans.size();
	    for (auto i=0; i<l; i++) {
		auto newV = ans[i];
		newV.push_back(n);
		ans.push_back(newV);
	    }
	}
	return ans;
    }
};

int main() {
    vector<int> v = {1,2,3};
    Solution *S = new Solution();
    auto ans = S->subsets(v);
    for (auto v: ans) {
	for (auto x: v) cout << x << ",";
	cout << endl;
    }
}
