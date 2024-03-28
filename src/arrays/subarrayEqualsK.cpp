#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Link: https://leetcode.com/problems/subarray-sum-equals-k/description/
Difficulty: Medium
Topics: array, hashtable, prefix sum
*/
class Solution {
public:
    // At each index, we wanna track all the subarray sums so far
    // can track this using hashmap
    // eg. M[5] = 2 => there are 2 subarray sums which equal 5
    //
    // basically, need to add nums[i] to each key
    // instead of actually adding to the key
    // we can keep updating an "offset" value, i.e.
    // M[5] = 2 => there are 2 subarray sums equal to (5 + offset)
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> tracker;
        int ans = 0;
        int offset = 0;

        for (auto n: nums) {
            tracker[-offset]++;
            offset += n;
            ans += tracker[k-offset];
        }
        return ans;
    }
};

int main() {
    vector<int> v;
    Solution *S = new Solution();
    int ans;

    v = {1,1,1};
    ans = S->subarraySum(v, 2);
    cout << "ans is " << ans << endl;

    v = {1,2,3};
    ans = S->subarraySum(v, 3);
    cout << "ans is " << ans << endl;

    v = {1,-1,0};
    ans = S->subarraySum(v, 0);
    cout << "ans is " << ans << endl;
}
