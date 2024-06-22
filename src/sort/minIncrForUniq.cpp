#include <iostream>
#include <unordered_set>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/minimum-increment-to-make-array-unique
Difficulty: Medium
Topics: array,greedy,sorting,counting
*/
class Solution {
public:
    int minIncrementForUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int last = nums[0]+1;
        int ans = 0;
        for (auto i=1; i<nums.size(); i++) {
            int num = nums[i];
            if (num >= last) last = num+1;
            else {
                ans += (last-num);
                last++;
            }
        }
       
        return ans;
    }

    int minIncrementForUnique2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int last = nums[0];
        int substitute = last+1;
        int ans = 0;

        unordered_set<int> M;
        for(auto n: nums) M.insert(n);

        for(auto i=1; i<nums.size(); i++) {
            auto num = nums[i];
            if (num == last) {
                while(M.find(substitute) != M.end()) substitute++;
                ans += (substitute-num);
                substitute++;
            } else {
                last = num;
                substitute = max(substitute, last+1);
            }
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> nums = {3,2,1,2,1,7};
    printVec(nums);
    int ans = S->minIncrementForUnique(nums);
    cout << "ans is " << ans << endl;

    nums = {1,2,2};
    printVec(nums);
    ans = S->minIncrementForUnique(nums);
    cout << "ans is " << ans << endl;

}
