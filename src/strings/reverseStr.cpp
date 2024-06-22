#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/reverse-string
Difficulty: Easy
Topics: two pointers, string
*/
class Solution {
public:
    void reverseString(vector<char>& s) {
        for (int i=0; i<s.size()/2; i++) {
            auto tmp = s[i];
            int index = (s.size()-1) - i;
            s[i] = s[index];
            s[index] = tmp;
        }
    }
};

int main() {
    Solution *S = new Solution();
    vector<char> s = {'h', 'e', 'l', 'l', 'o'};
    S->reverseString(s);
    for (auto c: s) cout << c;
    cout << endl;
}
