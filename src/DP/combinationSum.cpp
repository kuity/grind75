#include <iostream>
#include <set>
#include "../lib/util.h"

using namespace std;

// Represent DP[i] as a set of vector<int>
// each vector<int> is a frequency chart of candidates
// 
// From LC, there is a more efficient DP that represents DP[i] as a vector of vector<int>
// Each DP[i] is immediately the soln, no need to represent frequency chart
// This avoid duplicates by setting outing loop to go through candidates
// Then middle loop go through candidate -> target
// And finally, inner loop go through DPs
// This will avoid double counting combinations
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	vector<set<vector<int>>> DP(target+1);
	auto nCandidates = candidates.size();

	for (auto i=0; i<nCandidates; i++) {
	    auto defaultKey = candidates[i];
	    if (defaultKey <= target) {
		vector<int> v(nCandidates, 0);
		v[i] = 1;
		DP[candidates[i]].insert(v);
	    }
	}

	for (auto i=0; i<DP.size(); i++) {
	    auto val = DP[i];
	    for (auto combi: val) {
		for (auto j=0; j<nCandidates; j++) {
		    auto nextCandidate = candidates[j];
		    auto nextKey = i+nextCandidate;
		    if (nextKey < DP.size()) {
			auto nextCombi = combi;
			nextCombi[j]++;
			DP[nextKey].insert(nextCombi);
		    }
		}
	    }
	}

	vector<vector<int>> ans;
	for (auto v: DP[target]) {
	    vector<int> vAns;
	    for (auto x = 0; x < nCandidates; x++) {
		for (auto m = 0; m < v[x]; m++) {
		    vAns.push_back(candidates[x]);
		}
	    }
	    ans.push_back(vAns);
	}
	return ans;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> C = {2, 3, 6, 7};
    int target = 7;
    vector<vector<int>> ans = S->combinationSum(C, target);
    cout << "candidates are: " << endl;
    printVec(C);
    cout << "target is: " << target << endl;
    cout << "ans is: ";
    printVecVec(ans);


    C = {2, 3, 5};
    target = 8;
    ans = S->combinationSum(C, target);
    cout << "candidates are: " << endl;
    printVec(C);
    cout << "target is: " << target << endl;
    cout << "ans is: ";
    printVecVec(ans);


    C = {2};
    target = 1;
    ans = S->combinationSum(C, target);
    cout << "candidates are: " << endl;
    printVec(C);
    cout << "target is: " << target << endl;
    cout << "ans is: ";
    printVecVec(ans);
}
