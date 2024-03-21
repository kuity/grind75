#include <algorithm>
#include <iostream>
#include <vector>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/find-k-closest-elements/description/
Difficulty: Medium
Topics: array, binary search, two pointers, sliding window, sorting
*/
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        auto index = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        cout << "index is " << index << endl;
        vector<int> ans;
        int lowerInd = index-1;
        int upperInd = index;

        while (ans.size() < k) {
            if (lowerInd < 0) {
                ans.push_back(arr[upperInd]);
                upperInd++;
                continue;
            }
            if (upperInd >= arr.size()) {
                ans.push_back(arr[lowerInd]);
                lowerInd--;
                continue;
            }

            auto l = arr[lowerInd];
            auto u = arr[upperInd];
            if (x - l <= u - x) {
                ans.push_back(l);
                lowerInd--;
            } else {
                ans.push_back(u);
                upperInd++;
            }
        }

        sort(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    vector<int> v = {1,2,3,4,5};
    Solution *S = new Solution();
    vector<int> ans;
    ans = S->findClosestElements(v, 4, 3);
    printVec(ans);
    ans = S->findClosestElements(v, 4, -1);
    printVec(ans);
    ans = S->findClosestElements(v, 4, 6);
    printVec(ans);
}
