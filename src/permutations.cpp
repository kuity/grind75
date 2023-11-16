#include <iostream>
#include <vector>
#include "../lib/util.h"

using namespace std;

class Solution {
public:
    // This is intuitive solution without swapping
    // At each step, pluck each elem from rem and plop into cur, recurse
    vector<vector<int>> findPerm(vector<int> &rem, vector<int> &cur, int target) {
        vector<vector<int>> ans;
        // cout << "findPerm was called for: ";
        // printVec(rem);
        for (auto i=0; i<rem.size(); i++) {
            auto n = rem[i];
            rem.erase(rem.begin() + i);
            cur.push_back(n);
            auto subAns = findPerm(rem, cur, target);
            ans.insert(ans.end(), subAns.begin(), subAns.end());
            rem.insert(rem.begin() + i, n);
            cur.pop_back();
        }
        
        if (cur.size() == target) {
            ans.push_back(cur);
        }

        return ans;
    }

    // This is efficient solution with swaps
    // To understand, at each position, element x1 can be swapped with itself or any x2...xN
    void findPermWithSwaps(vector<vector<int>> &ans, vector<int> &nums, int cur, int target) {
        if (cur == target-1) {
            ans.push_back(nums);
            return;
        }

        for (auto i = cur; i < target; i++) {
            auto tmp = nums[i];
            nums[i] = nums[cur];
            nums[cur] = tmp;
            findPermWithSwaps(ans, nums, cur+1, target);
            nums[cur] = nums[i];
            nums[i] = tmp;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        // vector<int> cur;
        // return findPerm(nums, cur, nums.size());
        vector<vector<int>> ans;
        findPermWithSwaps(ans, nums, 0, nums.size());
        return ans;
    }
};

int main() {
    vector<int> nums = {1,2,3,4};
    Solution *S = new Solution();
    auto ans = S->permute(nums);
    printVecVec(ans);
}
