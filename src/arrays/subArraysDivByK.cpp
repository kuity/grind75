#include <iostream>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/subarray-sums-divisible-by-k
Difficulty: Medium
Topics: array, hashtable, prefix sum
*/
class Solution {
public:
    // This is actually very similar to continuous-subarray-sum problem
    // We will track the running sum
    // Every time the same running sum appears, add the cumsum to the answer
    // At the end, we need to add number of times running sum = 0 (mod k)
    // as these are unaccounted for
    int subarraysDivByK(vector<int>& nums, int k) {
        unordered_map<int, int> M;
        int s = 0;
        int nSubArrays = 0;
        for (auto i=0; i<nums.size(); i++) {
            s = (s + nums[i]) % k;
            if (s < 0) s+=k;
            cout << "i = " << i << " s = " << s << endl;
            if (M.find(s) != M.end()) {
                cout << "adding " << M[s] << " for i=" << i << "(" << nums[i] << ")" << endl;
                nSubArrays += M[s];
                M[s]++;
            } else M[s] = 1;
        }
        if (M.find(0) != M.end()) nSubArrays += M[0];
        return nSubArrays;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> v = {4,5,0,-2,-3,1};
    int k = 5;
    int ans = S->subarraysDivByK(v, k);
    printVec(v);
    cout << "for k = : " << k << " ans is " << ans << endl;
}
