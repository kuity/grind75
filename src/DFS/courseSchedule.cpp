#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <stack>
#include "../../lib/util.h"

using namespace std;

/*
link: https://leetcode.com/problems/course-schedule/description/
difficulty: medium
topics: dfs, bfs, graph, topological sort
*/
class Solution {
private:
    unordered_map<int, stack<int>> edges;

/*
 * Given prerequisites, we can identify sources and sinks
 * Keep repeating below until all edges are visited
 
 * If there are no "sources", return true because no requirements left to satisfy
 * Else, if there are no "sinks", return false because there's no way to satisfy any requirement (there is at least 1 cycle)
 *
 * Start from any random sink and do a DFS, keeping a visited set
 * If the DFS "revisits", return false because there is at least 1 cycle. consider self-cycles
 * Otherwise, restart the loop 
*/
public:
    bool hasCycleDFS(int n, set<int> &visited) {
        if (visited.find(n) != visited.end()) {
            return true;
        }
        visited.insert(n);
        while(!edges[n].empty()) {
            int nxt = edges[n].top();
            edges[n].pop();
            if (hasCycleDFS(nxt, visited)) {
                return true;
            }
        }
        edges.erase(n);
        visited.erase(n);
        return false;
    }


    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        stack<int> sinks;
        vector<int> tracker (numCourses, 1);
        for (auto v: prerequisites) {
            edges[v[1]].push(v[0]);
            tracker[v[0]] = 0;
        }

        for (int x=0; x<numCourses; x++) {
            if (tracker[x]==1) {
                sinks.push(x);
            }
        }

        while (edges.size() > 0) {
            if (sinks.size() == 0) {
                return false;
            }

            set<int> ns;
            if (hasCycleDFS(sinks.top(), ns)) {
                return false;
            }
            sinks.pop();
        }
        return true;
    }
};

int main() {
    vector<vector<int>> v = {{1,0}};
    Solution *S = new Solution();
    int ans;
    ans = S->canFinish(2, v);
    printVecVec(v);
    cout << "ans is " << ans << endl;
    v = {{1,0},{0,1}};
    ans = S->canFinish(2, v);
    printVecVec(v);
    cout << "ans is " << ans << endl;
    v = {{1,0},{0,2},{2,1}};
    ans = S->canFinish(3, v);
    printVecVec(v);
    cout << "ans is " << ans << endl;
}
