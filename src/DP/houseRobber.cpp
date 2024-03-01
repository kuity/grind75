#include <algorithm>
#include <iostream>
using namespace std;

/*
Link: https://leetcode.com/problems/house-robber/description/
Difficulty: Medium
Topics: Array, DP
*/
class Solution {
public:
    // This is just a classic DP problem
    int rob(vector<int>& nums) {
        int ans = 0;
        int sz = nums.size();
        vector<int> DP(sz, 0);
        for (auto i=sz-1; i>=0; i--) {
            if (i==sz-1) DP[i] = nums[i];
            else if (i==sz-2) DP[i] = max(nums[i], nums[i+1]);
            else DP[i] = max(DP[i+1], nums[i]+DP[i+2]);
        }

        return DP[0];
    }
};

int main() {
    vector<int> l = {2,7,9,3,1};
    Solution *S = new Solution();
    auto ans = S->rob(l);
    cout << "answer is " << ans << endl;
};
