#include <iostream>
#include <vector>
#include <unordered_map>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/contiguous-array/
Difficulty: Medium
Topics: array, hashtable
*/
class Solution {
public:
    // Explanation: we can use a variable sum to track the total sum at index i
    // If total sum was seen before at some index j, then the number of 0s and 1s between i and j must be equal
    // (assume we convert 0 to -1)
    // Thus we use hashtable to track "the first index where sum x was observed"
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> sumIndices;
        sumIndices[0] = -1;
        int cur = 0;
        int maxLen = 0;
        for (int i=0; i<nums.size(); i++) {
            cur += (nums[i] == 1 ? 1 : -1);
            if (sumIndices.find(cur) != sumIndices.end()) {
                int subarrLen = i - sumIndices[cur];
                if (subarrLen > maxLen) maxLen = subarrLen;
            } else {
                sumIndices[cur] = i;
            }
        }
        return maxLen;
    }
};

int main() {
    vector<int> v;
    int ans;
    Solution *S = new Solution();
    v = {0,1};
    ans = S->findMaxLength(v);
    printVec(v);
    cout << "ans is " << ans << endl;

    v = {0,1,0};
    ans = S->findMaxLength(v);
    printVec(v);
    cout << "ans is " << ans << endl;

    v = {0,1,1,0,0,0,1,1,1,0,1};
    ans = S->findMaxLength(v);
    printVec(v);
    cout << "ans is " << ans << endl;
}
