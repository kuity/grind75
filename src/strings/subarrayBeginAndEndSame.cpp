#include <iostream>
#include <unordered_map>

using namespace std;

/*
Link: https://leetcode.com/problems/substrings-that-begin-and-end-with-the-same-letter
Difficulty: Medium
Topics: hashtable,math,string,counting,prefix sum
*/
class Solution {
public:
    // Track number of times we have seen each character
    // Everytime we see a character c, we should add x, where x is the number of times we have already seen c
    // As that's the number of legit substrings begin and end with c
    long long numberOfSubstrings(string s) {
        int M[26];
        memset(M, 0, sizeof(M));
        long long ans = s.size();
        for (auto c: s) {
            ans += M[c-'a'];
            M[c-'a']++;
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    string s = "abcba";
    auto ans = S->numberOfSubstrings(s);
    cout << "s is " << s << " ans is " << ans << endl;

    s = "abacad";
    ans = S->numberOfSubstrings(s);
    cout << "s is " << s << " ans is " << ans << endl;

    s = "a";
    ans = S->numberOfSubstrings(s);
    cout << "s is " << s << " ans is " << ans << endl;

}
