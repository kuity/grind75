#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves
Difficulty: Medium
Topics: array, greedy, sorting
*/
class Solution {
public:
    // actually like a sliding window problem
    int minDifference(vector<int>& nums) {
        if (nums.size() <= 4) return 0;
        sort(nums.begin(), nums.end());
        int minDiff = *nums.rbegin() - *nums.begin();
        int i = 0, j = nums.size() - 4;
        for (auto k=0; k<4; k++) {
            minDiff = min(minDiff, nums[j] - nums[i]);
            // cout << "minDiff is " << minDiff << endl;
            // cout << "checked " << nums[j] << "," << nums[i] << endl;
            j++;
            i++;
        }
        return minDiff;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    cout << "ans is " << ans;
}
