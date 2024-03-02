#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

/*
Link: https://leetcode.com/problems/group-anagrams/
Difficulty: Medium
Topics: Array, Hashtable, String, Sorting
*/
class Solution {
    unordered_map<string, int> M;

public:
    string vectorToStringWithPadding(const vector<int>& vec, int paddingWidth) {
	ostringstream oss;
	
	for (const auto& num : vec) {
	    oss << setw(paddingWidth) << setfill('0') << num;
	}
	
	return oss.str();
    }

    string getStringKey(string anagram) {
	vector<int> count(26, 0);
	for (auto c: anagram) {
	    auto ind = c-'a';
	    count[ind]++;
	}
	return vectorToStringWithPadding(count, 3);
    }

    // kinda complicated solution converting each string into a key
    vector<vector<string>> groupAnagramsConversion(vector<string>& strs) {
	vector<vector<string>> ans;
	for (auto s: strs) {
	    auto k = getStringKey(s);
	    if (M.find(k) != M.end()) {
		ans[M[k]].push_back(s);
	    } else {
		M[k] = int(ans.size());
		ans.push_back({s});
	    }
	}
	return ans;
    }

    // very simple solution using default sort lol
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
	vector<vector<string>> ans;
	for (auto s: strs) {
	    auto k = s;
	    sort(k.begin(), k.end());
	    if (M.find(k) != M.end()) ans[M[k]].push_back(s); 
	    else {
		M[k] = int(ans.size());
		ans.push_back({s});
	    }
	}
	return ans;
    }
};

int main() {
    vector<string> strs = {"eat","tea","tan","ate","nat","bat"};
    Solution *S = new Solution();
    auto ans = S->groupAnagrams(strs);
    for (auto v: ans) { for (auto s: v) cout << s << ","; cout << endl;}
}
