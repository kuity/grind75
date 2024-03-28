#include <iostream>
#include <numeric>

using namespace std;

/*
Link: https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph
Difficulty: Medium
Topics: dfs, bfs, union find, graph
*/
class Solution {
public:
    // Using union find algorithm
    // 1. Always need a parent vector. and initialize v[i] = i
    // 2. find function recursively finds parent
    // 3. Path compression can improve find() step runtime
    // 
    // 4. Union step can apply iteratively to each "edge"
    // 5. by setting parent of pnt 1 to be the parent of the parent of pnt 2
    //
    // 6. if the parents were different, a union happens, so reduce 
    // number of distinct components by 1
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int> p(n);
        iota(begin(p), end(p), 0);
        function<int (int)> find = [&](int v) {
            if (p[v] == v) return v;
            else {
                auto parent = find(p[v]);
                p[v] = parent;
                return parent;
            }
        };

        for (auto& edge : edges) {
            int v = find(edge[0]), w = find(edge[1]);
            p[v] = w;
            n -= v != w;
        }
        return n;
    }
};

int main() {
    vector<vector<int>> edges = {{0,1},{1,2},{2,3},{3,4}};
    Solution *S = new Solution();
    int ans;
    ans = S->countComponents(5, edges);
    cout << "ans is " << ans << endl;

    edges = {{0,1}, {1,2}, {3,4}};
    ans = S->countComponents(5, edges);
    cout << "ans is " << ans << endl;
}
