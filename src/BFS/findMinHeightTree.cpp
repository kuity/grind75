#include "../../lib/util.h"
#include <unordered_map>
#include <iostream>
#include <queue>

using namespace std;

/*
Link: https://leetcode.com/problems/minimum-height-trees/description/
Difficulty: Medium
Topics: dfs, bfs, graph, topological sort
*/
class Solution {
private:
    unordered_map<int, vector<int>> M;
    vector<vector<int>> D;

public:
    // Find longest path? From root
    // Basically, every node can be the root
    // I need to know the distance from every node to every other node
    // The height will be the maximum of this
    // This works but is too slow
    vector<int> findMinHeightTreesSlow(int n, vector<vector<int>>& edges) {
        vector<vector<int>> distanceMap(n, vector<int>(n, -1));
        for (auto i=0; i<n; i++) distanceMap[i][i] = 0;
        for (auto v: edges) {
            distanceMap[v[0]][v[1]] = 1;
            distanceMap[v[1]][v[0]] = 1;
        }

        int minH = 0;
        int d = 1;
        while(minH == 0) {
            for (auto i=0; i<n; i++) {
                int matchDist = 0; // Check if there are any neighbors d distance away
                for (auto j=0; j<n; j++) {
                    if (distanceMap[i][j] == d) {
                        matchDist++;
                        // Double check the neighbor's neighbors
                        for (auto k=0; k<n; k++) {
                            if (distanceMap[j][k] > 0 && distanceMap[i][k] == -1) {
                                auto newdist = d + distanceMap[j][k];
                                distanceMap[i][k] = newdist;
                                distanceMap[k][i] = newdist;
                            }
                        }
                    }
                }

                if (matchDist == 0) {
                    minH = d-1;
                    break;
                }
            }
            d++;
        }

        vector<int> ans;
        for (auto i=0; i<n; i++) {
            bool isMinH = true;
            for (auto j=0; j<n; j++) {
                auto dist = distanceMap[i][j];
                if (dist == -1 || dist > minH) {
                    isMinH = false;
                    break;
                }
            }
            if (isMinH) ans.push_back(i);
        }
        return ans;
    }

    // Faster solution
    // The idea is we can keep taking leaf nodes and
    // remove them from the graph
    // Eventually, will be left with ONE or TWO nodes
    // These will be the CENTER of the LONGEST PATH that exist in the graph
    // 
    // Logically, there CANNOT EXIST 2 longest paths with a DIFFERENT CENTER
    // If there were, let's just imagine the 2 longest paths
    // They must be connected at some intersect
    // Then we just take the longer subpath in each path respectively
    // This forms a longer path (contradiction)
    //
    // Pro TIP: the adjacency graph MUST NOT be updated, it is TOO SLOW
    // Just rely on the degree graph
    //
    // Pro TIP 2: the iteration must be done in "layers" so we know
    // what was the final layer of removed nodes
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) return {0};
        vector<vector<int>> A(n);
        vector<int> degree(n);
        for (auto v: edges) {
            A[v[0]].push_back(v[1]);
            A[v[1]].push_back(v[0]);
            degree[v[0]]++;
            degree[v[1]]++;
        }

        queue<int> leafnodes;
        for (auto i=0; i<n ;i++) { if (degree[i] == 1) leafnodes.push(i); }

        vector<int> ans;
        while(!leafnodes.empty()) {
            ans = {};
            auto sz = leafnodes.size();
            for (auto i=0; i<sz; i++) {
                auto leafnode = leafnodes.front();
                leafnodes.pop();
                // cout << "i is " << i << ", pushing " << leafnode << endl;
                ans.push_back(leafnode);
                degree[leafnode]--;

                for (auto nb: A[leafnode]) {
                    // update the degree map
                    degree[nb]--;
                    if (degree[nb] == 1) leafnodes.push(nb);
                }
            }
            printVec(ans);
        }

        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    vector<vector<int>> edges = {{3,0},{3,1},{3,2},{3,4},{5,4}};
    auto ans = S->findMinHeightTrees(6, edges);
    cout << "Answer is : "; printVec(ans);

    edges = {{1,0},{1,2},{1,3}};
    ans = S->findMinHeightTrees(4, edges);
    cout << "Answer is : "; printVec(ans);
}
