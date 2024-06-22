#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/patching-array
Difficulty: Hard
Topics: array, greedy
*/
class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        int ans = 0;
        long nextSum = 1;
        int i = 0;
        while (nextSum <= n) {
            if (i < nums.size() && nums[i] <= nextSum) {
                nextSum += nums[i];
                i++;
            } else {
                nextSum += nextSum;
                ans++;
            }
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    vector<int> v = {1,3};
    ans = S->minPatches(v, 6);
    cout << "ans is " << ans << endl;

    v = {1,5,10};
    ans = S->minPatches(v, 20);
    cout << "ans is " << ans << endl;

    v = {1,2,2};
    ans = S->minPatches(v, 5);
    cout << "ans is " << ans << endl;
}
