#include <iostream>
#include <functional>
#include <queue>
#include "../lib/util.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
	priority_queue<pair<int, int>,
	    vector<pair<int, int>>,
	    function<bool(pair<int, int>, pair<int, int>)>
	> tracker (
	    [](const pair<int, int>& a, const pair<int, int>& b) {
		return a.first < b.first;
	    }
	);

	int numFilled = 0;
	for (int i=0; i<points.size(); i++) {
	    int p_1 = points[i][0];
	    int p_2 = points[i][1];
	    int s = p_1 * p_1 + p_2 * p_2;
	    if (numFilled < k) {
		tracker.emplace(s, i);
		numFilled++;
	    } else {
		if (s < tracker.top().first) {
		    tracker.pop();
		    tracker.emplace(s, i);
		}
	    }
	}

	vector<vector<int>> ans;
	while(!tracker.empty()) {
	    const auto& p = tracker.top();
	    ans.push_back(points[p.second]);
	    tracker.pop();
	}
	return ans;
    }
};

int main() {
    Solution *S = new Solution();
    vector<vector<int>> x = {{1,3},{-2,2}};
    vector<vector<int>> y = S->kClosest(x, 1);
    printVecVec(y);

    x = {{3,3},{5,-1},{-2,4}};
    y = S->kClosest(x, 2);
    printVecVec(y);
}
