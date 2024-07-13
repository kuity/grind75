#include <iostream>
#include <set>

using namespace std;

/*
Link: https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit
Difficulty: Medium
Topics: array,queue,sliding window,heap,ordered set,monotonic queue 
*/
class Solution {
public:
    // Use a sliding window approach keeping the maximum and minimum value using a data structure like a multiset from STL in C++.
    int longestSubarray(vector<int>& nums, int limit) {
        int hi = 0;
        int lo = 0;
        multiset<int, less<int>> R;
        int longest = 1;
        while (hi < nums.size()) {
            R.insert(nums[hi]);
            while (abs(*R.rbegin() - *R.begin()) > limit) {
                R.erase(R.find(nums[lo]));
                lo++;
            }
            longest = max(longest, int(R.size()));
            hi++;
        }
        return longest;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    vector<int> v;
    v = {8,2,4,7};
    ans = S->longestSubarray(v, 4);
    cout << "ans is " << ans << endl;
}
