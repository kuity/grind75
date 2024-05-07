#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/reverse-integer/description/
Difficulty: Medium
Topics: math
*/
class Solution {
public:
    int reverse(int x) {
        string xstr = to_string(x);
        if (x >= 0) std::reverse(xstr.begin(), xstr.end());
        else std::reverse(xstr.begin()+1, xstr.end());
        try {
            return stoi(xstr);
        } catch (std::out_of_range& e) {
            return 0;
        }
    }

    // Solution that checks overflow (if it overflowed, the condition not check out)
    int reverseOF(int x) {
        int ans = 0;
        while (x) {
            int temp = ans * 10 + x % 10;
            if (temp / 10 != ans)
                return 0;
            ans = temp;
            x /= 10;
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    ans = S->reverse(123);
    cout << "reverse(123) is " << ans << endl;
    ans = S->reverse(-123);
    cout << "reverse(-123) is " << ans << endl;
    ans = S->reverse(120);
    cout << "reverse(120) is " << ans << endl;
    ans = S->reverse(-120);
    cout << "reverse(-120) is " << ans << endl;
}
