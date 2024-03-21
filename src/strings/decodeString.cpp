#include <cctype>
#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/decode-string/
Difficulty: Medium
Topics: string, stack, recursion
*/
class Solution {
public:
    string helper(string s, int &index) {
        string decoded;
        string multiplier;
        while (index < s.size()) {
            auto c = s[index];
            if (isdigit(c)) {
                multiplier.push_back(c);
            } else if (c == '[') {
                index++;
                auto nextStr = helper(s, index);
                for (auto i=0; i<stoi(multiplier); i++) decoded += nextStr;
                multiplier = "";
            } else if (c == ']') {
                return decoded;
            } else {
                decoded.push_back(c);
            }
            index++;
        }
        return decoded;
    }

    string decodeString(string s) {
        int index = 0;
        return helper(s, index);
    }
};

int main() {
    Solution *S = new Solution();
    string s;
    string decoded;

    s = "3[a2[c]]";
    decoded = S->decodeString(s);
    cout << "encoded string is " << s << endl;
    cout << "decoded string is " << decoded << endl;

    s = "3[a]2[bc]";
    decoded = S->decodeString(s);
    cout << "encoded string is " << s << endl;
    cout << "decoded string is " << decoded << endl;

    s = "2[abc]3[cd]ef";
    decoded = S->decodeString(s);
    cout << "encoded string is " << s << endl;
    cout << "decoded string is " << decoded << endl;

}

