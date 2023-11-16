#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include "../lib/util.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // Find the largest element
        int sz = 0;
        for (auto v: intervals) {
            if (v[1] > sz) {
                sz = v[1];
            }
        }

        vector<int> markers(sz+1, -1);
        // Fill in markers
        // if some index has both a start and end interval, they cancel each other out
        for (auto v: intervals) {
            if (markers[v[0]] < v[1]) {
                markers[v[0]] = v[1];
            }
        }

        vector<vector<int>> ans;
        int st = -1;
        int ed = -1;

        // Iterate and keep track of each interval
        for (auto m=0; m<markers.size(); m++) {
            // cout << "st is " << st << ",ed is " << ed << endl;
            int val = markers[m];
            // Start tracking if needed
            if (val >= 0 && st < 0) {
                st = m;
                ed = val;
            }

            // move on if not tracking any interval
            if (st < 0) {
                continue;
            }

            // update if there is a greater ed
            if (val > ed) {
                ed = val;
            }

            // push to ans if needed
            if (ed == m) {
                vector<int> nI = {st, ed};
                // cout << "pushing ";
                // printVec(nI);
                ans.push_back(nI);
                st = -1;
                ed = -1;
            }
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> nums = {{1,3}, {2,6}, {8,10}, {15,18}};
    Solution *S = new Solution();
    auto ans = S->merge(nums);
    printVecVec(nums);
    printVecVec(ans);

    nums = {{1,4}, {4,5}};
    ans = S->merge(nums);
    printVecVec(nums);
    printVecVec(ans);

    nums = {{1,4}, {1,5}};
    ans = S->merge(nums);
    printVecVec(nums);
    printVecVec(ans);
}
