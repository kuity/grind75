#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/height-checker
Difficulty: Easy
Topics: array, sorting, counting sort
*/
class Solution {
public:
    int heightChecker(vector<int>& heights) {
        auto sorted = heights;
        sort(heights.begin(), heights.end());
        int ans = 0;
        for (auto i=0; i<heights.size(); i++) {
            if (heights[i] != sorted[i]) ans++;
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    vector<int> v = {1,1,4,2,1,3};
    ans = S->heightChecker(v);
    cout << "ans is " << ans << endl;

    v = {5,1,2,3,4};
    ans = S->heightChecker(v);
    cout << "ans is " << ans << endl;
}
