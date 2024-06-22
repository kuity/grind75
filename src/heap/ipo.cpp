#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

/*
Link: https://leetcode.com/problems/ipo
Difficulty: Hard
Topics: array,greedy,sorting,heap
*/
class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        priority_queue<int, vector<int>, less<int>> Q;
        vector<pair<int, int>> combined;
        auto n = profits.size();
        for (auto i=0; i<n; i++) combined.push_back({capital[i], profits[i]});
        sort(combined.begin(), combined.end());

        int i = 0;
        int index = 0;
        while (i < k) {
            while (combined[index].first <= w && index < n) {
                Q.push(combined[index].second);
                index++;
            }
            if (Q.empty()) return w;
            w+=Q.top();
            Q.pop();
            i++;
        }
        return w;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    vector<int> P;
    vector<int> C;
    P = {1,2,3};
    C = {0,1,1};
    ans = S->findMaximizedCapital(2, 0, P, C);
    cout << "ans is " << ans << endl;

    P = {1,2,3};
    C = {0,1,2};
    ans = S->findMaximizedCapital(3, 0, P, C);
    cout << "ans is " << ans << endl;

    P = {1,2,3};
    C = {1,1,2};
    ans = S->findMaximizedCapital(1, 0, P, C);
    cout << "ans is " << ans << endl;
}
