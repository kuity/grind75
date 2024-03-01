#include <algorithm>
#include <iostream>
using namespace std;

/*
Link: https://leetcode.com/problems/maximum-product-subarray
Difficulty: Medium
Topics: Array, DP
*/
class Solution {
public:
    // The intuition behind this DP approach is to keep 3 values at each index i
    // it doesn't matter much whether iterate from the back or the front
    // Assume we iterate from back
    // at each i, DP[i][0] = contiguous positive product for nums[i:]
    // DP[i][1] = contiguous negative product for nums[i:]
    // DP[i][2] = max product for nums[i:]
    //
    // Only interesting point is if nums[i] = 0, we need to reset DP[i][0] and DP[i][1]
    int maxProductSlow(vector<int>& nums) {
        auto sz = nums.size();
        vector<vector<int>> DP(sz, vector<int>(3, 0));
        auto last = nums[sz-1];
        if (last > 0) DP[sz-1] = {last, 0, last};
        else if (last < 0) DP[sz-1] = {0, last, last};

        for (int i=sz-2; i>=0; i--) {
            // cout << "i is " << i << endl;
            auto num = nums[i];
            auto DPvals = DP[i+1];
            if (num == 0) DP[i] = {0, 0, DPvals[2]};
            else if (num > 0) {
                DP[i][0] = max(num, num*DPvals[0]);
                DP[i][1] = num*DPvals[1];
                DP[i][2] = max(DP[i][0], DPvals[2]);
            }
            else {
                DP[i][0] = num*DPvals[1];
                DP[i][1] = min(num, num*DPvals[0]);
                DP[i][2] = max(DP[i][0], DPvals[2]);
            }
        }

        return DP[0][2];
    }

    // This is like an optimization of maxProductSlow
    // We can discard the DP vector and just use a pair to keep track 
    // of the contiguous positive and negative product
    // 
    // Now, the only issue is if there is just one number in nums
    // Let's say {-15}. In this case, just return immediately
    int maxProduct(vector<int>& nums) {
        auto sz = nums.size();
        int ans = nums[0];
        if (sz == 1) return ans;
        pair<int, int> tracker = {0, 0};
        for (int i=0; i<sz; i++) {
            auto num = nums[i];
            if (num == 0) tracker = {0, 0};
            else if (num < 0) tracker = {tracker.second*num, min(num, tracker.first*num)};
            else if (num > 0) tracker = {max(num, tracker.first*num), tracker.second*num};
            ans = max(ans, tracker.first);
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> l = {2,3,-2,4};
    auto ans = S->maxProduct(l);
    cout << "answer is " << ans << endl;

    l = {-2,0,-1};
    ans = S->maxProduct(l);
    cout << "answer is " << ans << endl;

    l = {0, -3, -5, -2, 0};
    ans = S->maxProduct(l);
    cout << "answer is " << ans << endl;

    l = {-2, 3, -4};
    ans = S->maxProduct(l);
    cout << "answer is " << ans << endl;

    l = {0, 0, 0};
    ans = S->maxProduct(l);
    cout << "answer is " << ans << endl;

    l = {-15};
    ans = S->maxProduct(l);
    cout << "answer is " << ans << endl;

};
