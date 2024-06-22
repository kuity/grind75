#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/append-characters-to-string-to-make-subsequence
Difficulty: Medium
Topics: two pointers, string, greedy
*/
class Solution {
public:
    int appendCharacters(string s, string t) {
        int sIndex = 0;
        int tIndex = 0;
        while (sIndex < s.size() && tIndex < t.size()) {
            if (s[sIndex] == t[tIndex]) {
                sIndex++;
                tIndex++;
            } else {
                sIndex++;
            }
        }

        return t.size() - tIndex;
    }
};

int main() {
    Solution *S = new Solution();
    string s = "coaching";
    string t = "coding";
    int ans = S->appendCharacters(s, t);
    cout << "ans for s=" << s << ", t=" << t << " is " << ans << endl;

    s = "abcde";
    t = "a";
    ans = S->appendCharacters(s, t);
    cout << "ans for s=" << s << ", t=" << t << " is " << ans << endl;
}
