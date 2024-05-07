#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/decode-ways/description/
Difficulty: Medium
Topics: string, DP
*/
class Solution {
    unordered_map<string, int> M;

public:
    Solution() {
        for (int i=1; i<=26; i++) {
            // S.insert(to_string(i));
            M[""] = 1;
        }
    }

    // 1,2,...,26
    // Each time can read either 1 or 2 
    int numDecodings(string s) {
        // cout << "Checking " << s << endl;
        if (M.find(s) != M.end()) return M[s];
        // cout << "s1 is " << s1 << " s2 is " << s2 << endl;

        int ans = 0;
        if (stoi(s.substr(0, 1)) >= 1) ans += numDecodings(s.substr(1));
        if (s.size() > 1 && s[0] != '0' && stoi(s.substr(0, 2)) <= 26) ans += numDecodings(s.substr(2));
        M[s] = ans;
        return ans;
    }

    // This also can use DP (todo: practice)
};

int main() {
    Solution *S = new Solution();
    string s;
    int ans;

    s = "11106";
    ans = S->numDecodings(s);
    cout << "encoded string is " << s << endl;
    cout << "ways to decode = " << ans << endl;
}

