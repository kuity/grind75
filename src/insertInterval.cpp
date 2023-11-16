#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
	int newIntervalSt = newInterval[0];
	int newIntervalEd = newInterval[1];
	bool pushRest = false;
	bool checkHead = true;
	bool hasAdded = false;

	vector<vector<int>> result;
	vector<int> newVec;

	// Plan: find the first interval that is larger than new interval
	for (auto v: intervals) {
	    int intervalSt = v[0];
	    int intervalEd = v[1];

	    if (pushRest) {
		result.push_back(v);
	    } else if (checkHead) {
		if (intervalEd < newIntervalSt) {
		    result.push_back(v);
		} else if (intervalSt > newIntervalEd) {
		    result.push_back(newInterval);
		    result.push_back(v);
		    hasAdded = true;
		    pushRest = true;
		} else {
		    newVec.push_back(min(intervalSt, newIntervalSt));
		    newIntervalEd = max(intervalEd, newIntervalEd);
		    checkHead = false;
		}
	    } else {
		if (intervalEd <= newIntervalEd) {
		    continue;
		} else if (intervalSt <= newIntervalEd) {
		    newVec.push_back(max(intervalEd, newIntervalEd));
		    result.push_back(newVec);
		    hasAdded = true;
		    pushRest = true;
		} else {
		    newVec.push_back(newIntervalEd);
		    result.push_back(newVec);
		    result.push_back(v);
		    hasAdded = true;
		    pushRest = true;
		}
	    }

	    // for (auto v: result) {
	    //     cout << "iteration interval: " << intervalSt << "," << intervalEd << endl;
	    //     cout << v[0] << "," << v[1] << endl;
	    // }
	}

	if (newVec.size() == 1) {
	    newVec.push_back(newIntervalEd);
	    result.push_back(newVec);
	    hasAdded = true;
	}

	if (!hasAdded) {
	    result.push_back({newIntervalSt, newIntervalEd});
	}

	return result;
    }
};

int main() {
    Solution *S = new Solution();
    //vector<vector<int>> v1 = {{1,3},{6,9}};
    //vector<int> n1 = {2,5};
    //vector<vector<int>> v1 = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    //vector<int> n1 = {4,8};
    vector<vector<int>> v1 = {{1,5}};
    vector<int> n1 = {0,0};
    vector<vector<int>> a1 = S->insert(v1, n1);
    for (auto v: a1) {
	cout << v[0] << "," << v[1] << endl;
    }
}
