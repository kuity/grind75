#include <iostream>
#include <numeric>

using namespace std;

/*
Link: https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends
Difficulty: Medium
Topics: array, union find, sorting
*/
class Solution {
public:
    // Using union find algorithm
    // 1. Always need a parent vector. and initialize v[i] = i
    // 2. find function recursively finds parent
    // 3. Path compression can improve find() step runtime
    // 4. Union step can apply iteratively to each "edge"
    // 5. by setting parent of pnt 1 to be the parent of the parent of pnt 2
    // 6. if the parents were different, a union happens, so reduce 
    // number of distinct components by 1
    int earliestAcq(vector<vector<int>>& logs, int n) {
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int> &b) {
            return a[0] < b[0];
        });
        vector<int> p(n);
        iota(begin(p), end(p), 0);
        int joins = 0;

        function<int (int)> find = [&](int v) {
            if (p[v] == v) return v;
            else {
                auto parent = find(p[v]);
                p[v] = parent;
                return parent;
            }
        };

        for (auto& log: logs) {
            int v = find(log[1]), w = find(log[2]);
            p[v] = w;
            n -= v != w;
            if (n == 1) return log[0];
            // cout << "n is " << n << endl;
        }
        return -1;
    }
};

int main() {
    vector<vector<int>> logs;
    Solution *S = new Solution();
    int n;
    int ans;

    logs = {{20190101,0,1},{20190104,3,4},{20190107,2,3},{20190211,1,5},{20190224,2,4},{20190301,0,3},{20190312,1,2},{20190322,4,5}};
    n = 6;
    ans = S->earliestAcq(logs, n);
    cout << "ans is " << ans << endl;

    logs = {{0,2,0},{1,0,1},{3,0,3},{4,1,2},{7,3,1}};
    n = 4;
    ans = S->earliestAcq(logs, n);
    cout << "ans is " << ans << endl;
}
