#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
Link: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
Difficulty: Medium
Topics: hashtable, string, backtracking
*/
class Solution {
private:
    unordered_map<int, vector<char>> map = {
	{2, {'a', 'b', 'c'}},
	{3, {'d', 'e', 'f'}},
	{4, {'g', 'h', 'i'}},
	{5, {'j', 'k', 'l'}},
	{6, {'m', 'n', 'o'}},
	{7, {'p', 'q', 'r', 's'}},
	{8, {'t', 'u', 'v'}},
	{9, {'w', 'x', 'y', 'z'}}
    };
    
public:
    vector<string> helper(string digits, int i, vector<string> &v) {
	if (i>=digits.size()) return v;
	auto nextDigit = stoi(digits.substr(i, 1));
	if (nextDigit == 1) helper(digits, i+1, v);
	auto chars = map[nextDigit];
	auto numS = v.size();
	vector<string> newV;
	for (auto s: v) {
	    for (auto c: chars) {
		auto newS = s+c;
		newV.push_back(newS);
	    }
	}
	v = newV;
	return helper(digits, i+1, v);
    }

    vector<string> letterCombinations(string digits) {
	vector<string> init = {""};
	auto ans = helper(digits, 0, init);
	if (ans.size() == 1) {
	    return {};
	}
	return ans;
    }
};

int main() {
    string digits = "23";
    Solution *S = new Solution();
    auto ans = S->letterCombinations(digits);
    cout << "size of ans is " << ans.size() << endl;
    for (auto s: ans) cout << s << ",";
    cout << endl;
}
