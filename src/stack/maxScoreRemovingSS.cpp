#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/maximum-score-from-removing-substrings
Difficulty: Medium
Topics: string, stack, greedy
*/
class Solution {
public:
    int maximumGain(string s, int x, int y) {
        int gain = 0;
        char first = x > y ? 'a' : 'b';
        char second = x > y ? 'b' : 'a';
        vector<int> incr = {x, y};
        vector<char> chars = {first, second};
        sort(incr.begin(), incr.end(), greater<int>());
        vector<char> v;
        for (auto m=0; m<2; m++) {
            for (int i=0; i<s.size(); i++) {
                if (v.empty()) v.push_back(s[i]);
                else {
                    if (v.back() == chars[m] && s[i] == chars[(m+1)%2]) {
                        v.pop_back();
                        gain += incr[m];
                    } else {
                        v.push_back(s[i]);
                    }
                }
            }
            string newS(v.begin(), v.end());
            s = newS;
            v = {};
            // cout << "string is now " << s << endl;
        }
        return gain;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    cout << "ans is " << ans;
}
