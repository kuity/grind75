#include "../../lib/util.h"
#include <iostream>
#include <stack>

using namespace std;

/*
Link: https://leetcode.com/problems/asteroid-collision/
Difficulty: Medium
Topics: Array, Stack
*/
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> ans;
        vector<int> tracker;
        for (auto a: asteroids) {
            if (a > 0) tracker.push_back(a);
            else {
                bool destroyed = false;
                while (!tracker.empty()) {
                    int top = tracker[tracker.size()-1];
                    // cout << "top is " << top << endl;
                    if (-a > top) tracker.pop_back();
                    else if (-a == top) {
                        tracker.pop_back(); 
                        destroyed = true;
                        break;
                    } else {
                        destroyed = true;
                        break;
                    }
                }
                // only way the negative val asteroid is not destroyed
                // is if it desroyed all positive asteroid in the stack
                if (!destroyed) ans.push_back(a);
            }
        }

        for (auto val: tracker) ans.push_back(val);
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> v;
    vector<int> ans;

    v = {5,10,-5};
    ans = S->asteroidCollision(v);
    printVec(ans);

    v = {8, -8};
    ans = S->asteroidCollision(v);
    printVec(ans);

    v = {10,2,-5};
    ans = S->asteroidCollision(v);
    printVec(ans);
}
