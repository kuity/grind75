#include <functional>
#include <iostream>
#include <queue>
#include "../../lib/util.h"
#include <stack>

using namespace std;

/*
Link: https://leetcode.com/problems/daily-temperatures/
Difficulty: Medium
Topics: Array, Stack, Monotonic Stack
*/
class Solution {
public:
    // This is actually a very classic and elegant solution utilizing stack 
    // Can think of this as we want to track elements that CAN POTENTIALLY be the nearest greater element for another element
    // We can iterate from the back and push each element onto the stack
    // When we check the current element, and the topstack is smaller or equal, we can discard the topstack
    // because it cannot become the NEAREST greater element for subsequent elements on the left
    // If the topstack is greater, we have found the nearest greater element and can just subtract
    // current index from the found index
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> ans(temperatures.size(), 0);
        stack<pair<int, int>> S;
        for (int i=temperatures.size()-1; i>=0; i--) {
            auto deezTemp = temperatures[i];
            while (!S.empty() && S.top().first <= deezTemp) S.pop();
            if (!S.empty()) ans[i] = S.top().second-i;
            S.push({deezTemp, i});
        }
        return ans;
    }

    // This is an inferior solution utilizing a minheap 
    // The way it works is we iterate the list and keep the index and value in a minheap
    // On processing each element
    // if it's smaller than the top of the heap, we are done because 
    // this element can't be greater than any previous elements
    // Otherwise, we keep popping off the heap until its empty or the top is greater
    vector<int> dailyTemperaturesHeap(vector<int>& temperatures) {
        priority_queue<pair<int, int>, 
            vector<pair<int, int>>, 
            function<bool(pair<int, int>, pair<int, int>)>
        > Q (
            [](const pair<int, int>& a, const pair<int, int>& b) {
                return a.first > b.first;
            }
        );

        int sz = (int)temperatures.size();
        vector<int> ans(sz, 0);
        for (auto i=0; i<sz; i++) {
            auto thisTemp = temperatures[i];
            cout << "checking " << thisTemp << endl;
            while(!Q.empty() && thisTemp > Q.top().first) {
                auto QTop = Q.top();
                ans[QTop.second] = i - QTop.second;
                Q.pop();
            }

            Q.push({thisTemp, i});
        }

        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> temps = {73,74,75,71,69,72,76,73};
    auto ans = S->dailyTemperatures(temps);
    printVec(ans);

    temps = {30, 40, 50, 60};
    ans = S->dailyTemperatures(temps);
    printVec(ans);

}
