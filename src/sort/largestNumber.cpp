#include <iostream>
#include <vector>
#include <sstream>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/largest-number/
Difficulty: Medium
Topics: array, string, greedy, sorting
*/
struct greater_than_custom
{
    inline bool operator() (const int& a, const int& b)
    {
        // cout << "compare " << a << " and " << b << endl;
        auto astr = to_string(a);
        auto bstr = to_string(b);
        return astr + bstr > bstr + astr;
    }
};

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater_than_custom());
        ostringstream s;
        int i = 0;
        while (i < nums.size() && nums[i] == 0) i++;
        for (; i<nums.size(); i++) s << to_string(nums[i]);
        auto ans = s.str();
        return ans.size() == 0 ? "0" : ans;
    }
};

int main() {
    vector<int> nums = {3,30,34,5,9};
    Solution *S = new Solution();
    string ans;
    ans = S->largestNumber(nums);
    printVec(nums);
    cout << ans << endl;
}
