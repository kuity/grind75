#include <algorithm>
#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/random-pick-with-weight/
Difficulty: Medium
Topics: randomized, array, math, binary search, prefix sum
*/
class Solution {
    vector<int> bounds;
    int upperBound;
public:
    // accumulate and keep the upper bounds of each weight in a vector
    // apparently O(1) is possible https://en.wikipedia.org/wiki/Alias_method
    Solution(vector<int>& w) {
        int tracker = 0;
        for (auto weight: w) {
            tracker += weight;
            bounds.push_back(tracker);
        }
        upperBound = tracker;
        srand(time(NULL));
    }
    
    int pickIndex() {
        int randNum = rand() % upperBound;
        int ind = upper_bound(bounds.begin(), bounds.end(), randNum) - bounds.begin();
        return ind;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */

int main() {
    vector<int> weights = {1,3};
    Solution *S = new Solution(weights);
    int ans;
    ans = S->pickIndex();
    cout << "rolled " << ans << endl;

    ans = S->pickIndex();
    cout << "rolled " << ans << endl;

    ans = S->pickIndex();
    cout << "rolled " << ans << endl;

    ans = S->pickIndex();
    cout << "rolled " << ans << endl;

    ans = S->pickIndex();
    cout << "rolled " << ans << endl;

    ans = S->pickIndex();
    cout << "rolled " << ans << endl;

    ans = S->pickIndex();
    cout << "rolled " << ans << endl;

    ans = S->pickIndex();
    cout << "rolled " << ans << endl;
}
