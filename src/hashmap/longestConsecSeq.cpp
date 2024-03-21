#include <string>
#include <unordered_map>
#include <set>
#include <iostream>
#include <vector>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/longest-consecutive-sequence/description/
Difficulty: Medium
Topics: Array, Hashtable, Union Find
*/
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, vector<int>> ranges;
        set<int> done;
        int longest = 0;
        for (auto n: nums) {
            // if already seen the number, skip
            if (done.find(n) != done.end()) continue;
            done.insert(n);
            int newStart = n;
            int newEnd = n;
            if (ranges.find(n-1) != ranges.end()) newStart = ranges[n-1][0];
            if (ranges.find(n+1) != ranges.end()) newEnd = ranges[n+1][1];
            ranges[newStart] = {newStart, newEnd};
            ranges[newEnd] = {newStart, newEnd};
            // cout << "num is " << n << ", newStart is " << newStart << ", newEnd is " << newEnd << endl;
            if (newEnd-newStart+1 > longest) longest = newEnd-newStart+1;
        }
        return longest;
    }
    
    // Taken from leetcode.
    // This is just an optimization of the above
    // Basically, we no need to store the beginning and end of the range
    // Actually, at each index, we just need to store the longest range seen (which is starting or ending) at that index
    int longestConsecutiveOptimized(vector<int>& nums) {
        unordered_map<int, int> m;
        int r = 0;
        for (int i : nums)
            if (!m[i]) {
                m[i] = m[i - 1] + m[i + 1] + 1;
                m[i - m[i - 1]] = m[i];
                m[i + m[i + 1]] = m[i];
                r = max(r, m[i]);
            }
        return r;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> v = {100,4,200,1,3,2};
    printVec(v);
    auto ans = S->longestConsecutive(v);
    cout << "ans is " << ans << endl;

    v = {0,3,7,2,5,8,4,6,0,1};
    printVec(v);
    ans = S->longestConsecutive(v);
    cout << "ans is " << ans << endl;

    v = {9,-8,9,8,-7,9,-4,6,5,5,6,7,-9,-5,-4,6,-8,-1,8,0,1,5,4};
    printVec(v);
    ans = S->longestConsecutive(v);
    cout << "ans is " << ans << endl;
}
