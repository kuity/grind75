#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/generate-parentheses/description/
Difficulty: Medium
Topics: string, DP, backtracking
*/
class Solution {
public:
    void helper(vector<string> &v, int completed, int open, int n, string p) {
        if (completed == n) {
            v.push_back(p);
            return;
        }
        if (completed + open < n) helper(v, completed, open+1, n, p+"(");
        if (open > 0) helper(v, completed+1, open-1, n, p+")");
    }
    
    vector<string> generateParenthesis(int n) {
        vector<string> v;
        helper(v, 0, 0, n, "");
        return v;
    }
};

int main() {
    int n;
    Solution *S = new Solution();
    n = 3;
    vector<string> ans;
    ans = S->generateParenthesis(n);
    for (auto s: ans) cout << s << ","; cout << endl;
}
