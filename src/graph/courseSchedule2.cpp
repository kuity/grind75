#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <stack>
#include "../../lib/util.h"

using namespace std;

/*
link: https://leetcode.com/problems/course-schedule-ii/
difficulty: medium
topics: dfs, bfs, graph, topological sort
*/
class Solution {
public:
    // This is just topological sort apparently
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_map<int, vector<int>> M;
        vector<int> inDegree(numCourses, 0);
        for (auto p: prerequisites) {
            M[p[1]].push_back(p[0]);
            inDegree[p[0]]++;
        }

        stack<int> S;
        vector<int> ans;
        for (auto i=0; i<numCourses; i++) if (inDegree[i]==0) S.push(i);
        while(!S.empty()) {
            auto node = S.top();
            ans.push_back(node);
            S.pop();
            for (auto nb: M[node]) {
                inDegree[nb]--;
                if (inDegree[nb] == 0) S.push(nb);
            }
        }
        return int(ans.size()) == numCourses ? ans : vector<int>();
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> ans;
    vector<vector<int>> v = {{1,0},{2,0},{3,1},{3,2}};
    ans = S->findOrder(4, v);
    printVec(ans);

    v = {{1,0}};
    ans = S->findOrder(2, v);
    printVec(ans);
}
