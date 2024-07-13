#include <iostream>
#include <set>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph
Difficulty: Medium
Topics: dfs, bfs, graph, topological sort
*/
class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        int indegree[n];
        vector<vector<int>> children(n);
        memset(indegree, 0, sizeof(indegree));
        for (auto edge: edges) {
            indegree[edge[1]]++;
            children[edge[0]].push_back(edge[1]);
        }

        vector<int> sources;
        for (auto i=0; i<n; i++) if (indegree[i] == 0) sources.push_back(i);

        vector<set<int>> ans(n);
        while (sources.size() > 0) {
            vector<int> tmp;
            for (auto s: sources) {
                for (auto c: children[s]) {
                    ans[c].insert(s);
                    ans[c].insert(ans[s].begin(), ans[s].end());
                    if (--indegree[c] == 0) tmp.push_back(c);
                }
            }
            sources = tmp;
        }

        vector<vector<int>> Vans;
        for (auto i=0; i<n; i++) {
            vector<int> nxt(ans[i].begin(), ans[i].end());
            Vans.push_back(nxt);
        }
        return Vans;
    }
};

int main() {
    Solution *S = new Solution();
    vector<vector<int>> ans;
    vector<vector<int>> E;
    int n;

    E = {{0,3},{0,4},{1,3},{2,4},{2,7},{3,5},{3,6},{3,7},{4,6}};
    n = 8;
    ans = S->getAncestors(n, E);
    cout << "n = " << n << ", Edgelist: ";
    printVecVec(E);
    cout << "ans: ";
    printVecVec(ans);
}
