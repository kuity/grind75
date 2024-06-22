#include <iostream>
#include "../../lib/util.h"
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
Link: https://leetcode.com/problems/continuous-subarray-sum
Difficulty: Medium
Topics: array,hashtable,math,prefix sum
*/
class Solution {
public:
    // Elegant solution that tracks the running sum mod k
    // If the running sum mod k was seen before, then a legit subsequence exists
    bool checkSubarraySum(vector<int>& nums, int k) {
        if (nums.size() < 2) return false;
        int s = nums[0] % k;
        unordered_map<int, int> M;
        M[s] = 0;
        M[0] = -1;
        for (auto i=1; i<nums.size(); i++) {
            s = (s + nums[i]) % k;
            if (M.find(s) != M.end()) {
                if (i-M[s] > 1) return true;
            } else M[s] = i;
        }
        return false;
    }

    // Pretty complicated solution that tracks the "offset"
    // or the sum so far
    // At each offset, the target (essentially k - offset) is calculated
    // And will find if the target has been seen so far
    // basically we are looking for, at each index i 
    // whether there exists a subsequence ending with nums[i] that has sum multiple of k
    bool checkSubarraySum2(vector<int>& nums, int k) {
        int offset = 0;
        unordered_set<int> S;
        for (auto i=0; i<nums.size(); i++) {
            auto newMod = nums[i] % k;
            auto target = (k - newMod - offset) % k;
            if (target < 0) target += k;
            if (S.find(target) != S.end()) return true;
            offset = (offset + newMod) % k;
            auto newEntry = (newMod - offset) % k;
            if (newEntry < 0) newEntry += k;
            S.insert(newEntry);
        }
        return false;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> v = {23,2,4,6,7};
    auto ans = S->checkSubarraySum(v, 6);
    printVec(v);
    cout << "k is " << 6 << " ans is " << ans << endl;

    v = {23,2,6,4,7};
    printVec(v);
    ans = S->checkSubarraySum(v, 13);
    cout << "k is " << 13 << " ans is " << ans << endl;

    v = {23,2,4,6,6};
    printVec(v);
    ans = S->checkSubarraySum(v, 7);
    cout << "k is " << 7 << " ans is " << ans << endl;

    v = {1,2,12};
    printVec(v);
    ans = S->checkSubarraySum(v, 6);
    cout << "k is " << 6 << " ans is " << ans << endl;
}
