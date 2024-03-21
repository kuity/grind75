#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
link: https://leetcode.com/problems/graph-valid-tree/
difficulty: medium
topics: dfs, graph, bfs, union find
*/
class Solution {
public:
    void DFS(int node, vector<bool> &visited, unordered_map<int, vector<int>> &M) {
        for (auto child: M[node]) {
            if (visited[child]) continue;
            visited[child] = true;
            DFS(child, visited, M);
        }
    }

    // A pretty optimized DFS solution
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n-1) return false; // too many edges = gg
        unordered_map<int, vector<int>> M;
        // build adjacency graph
        for (auto e: edges) {
            M[e[0]].push_back(e[1]);
            M[e[1]].push_back(e[0]);
        }
        vector<bool> visited(n, false);
        visited[0] = true;
        DFS(0, visited, M);
        for (auto x: visited) if (!x) return false;
        return true;
    }

    // TODO: Union find solution?
};

int main() {
    Solution *S = new Solution();
    bool ans;
    vector<vector<int>> edges = {{0,1},{0,2},{0,3},{1,4}};
    ans = S->validTree(5, edges);
    cout << "ans is " << ans << endl;

    edges = {{0,1},{1,2},{2,3},{1,3},{1,4}};
    ans = S->validTree(5, edges);
    cout << "ans is " << ans << endl;

    edges = {{0,1},{2,3}};
    ans = S->validTree(4, edges);
    cout << "ans is " << ans << endl;

}
