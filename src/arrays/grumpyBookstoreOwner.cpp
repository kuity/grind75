#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/grumpy-bookstore-owner/
Difficulty: Medium
Topics: array, sliding window
*/
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int flippable = 0;
        int ans = 0;
        for (auto i=0; i<minutes; i++) {
            if (grumpy[i] == 1) flippable += customers[i];
            else ans += customers[i];
        }

        int window = flippable;
        for (auto i=minutes; i<customers.size(); i++) {
            window = window - customers[i-minutes] * grumpy[i-minutes]
                + customers[i] * grumpy[i];
            flippable = max(window, flippable);
            if (grumpy[i] == 0) ans += customers[i];
        }
        // cout << "ans is " << ans << endl;
        // cout << "flippable is " << flippable << endl;
        return ans + flippable;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    vector<int> c;
    vector<int> g;
    int m;
    c = {1,0,1,2,1,1,7,5};
    g = {0,1,0,1,0,1,0,1};
    m = 3;
    ans = S->maxSatisfied(c, g, m);
    cout << "ans is " << ans << endl;
}
