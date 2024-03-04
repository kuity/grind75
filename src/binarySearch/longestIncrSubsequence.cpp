#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

/*
Link: https://leetcode.com/problems/longest-increasing-subsequence/description/
Difficulty: Medium
Topics: array, binary search, dp
*/
class Solution {
public:
    // O(nlogn) Solution based on binary search 
    // https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
    // Basically we keep building the longest subsequence while iterating through the input array
    // And looking for "replaceable" elements in the subsequence so far, by binary search
    int lengthOfLIS(vector<int>& nums) {
        vector<int> longest = {nums[0]};
        for (auto i=1; i<nums.size(); i++) {
            auto num = nums[i];
            if (num > *(longest.end()-1)) longest.push_back(num);
            else {
                auto it = lower_bound(longest.begin(), longest.end(), num);
                *it = num;
            }
        }
        return longest.size();
    }

    // This is an O(n^2) solution 
    // where we keep track of the longest subsequence length in a map 
    // and keep inserting into the map 
    // Each insertion, need to check all smaller keys in the map
    // and update with the longest subsequence length + 1
    int lengthOfLISslow(vector<int>& nums) {
        map<int, int> M;
        int longest = 0;
        for (auto num: nums) {
            auto it = M.begin();
            auto greatest = 1;
            while (it->first < num && it != M.end()) {
                if (it->second >= greatest) greatest = it->second+1;
                it++;
            }
            M[num] = greatest;
            if (greatest > longest) longest = greatest;
        }
        
        return longest;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> v = {10,9,2,5,3,7,101,18};
    auto ans = S->lengthOfLIS(v);
    cout << ans << endl;

    v = {0,1,0,3,2,3};
    ans = S->lengthOfLIS(v);
    cout << ans << endl;
    
    v = {7,7,7,7,7,7,7};
    ans = S->lengthOfLIS(v);
    cout << ans << endl;

}
