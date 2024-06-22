#include <cstdlib>
#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/score-of-a-string
Difficulty: Easy
Topics: string
*/
class Solution {
public:
    int scoreOfString(string s) {
        int ans = 0;
        for (int i=0; i<s.length()-1; i++) {
            auto c = s[i];
            auto nextC = s[i+1];
            ans += abs(c-nextC);
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    int ans = S->scoreOfString("hello");
    cout << "ans is " << ans;
}
