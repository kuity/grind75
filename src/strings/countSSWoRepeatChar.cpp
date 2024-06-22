#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/count-substrings-without-repeating-character/?envType=weekly-question&envId=2024-06-22
Difficulty: Medium
Topics: string, hashtable, sliding window
*/
class Solution {
public:
    // Idea: We can iterate the string from start
    // Append the number of "special" substrings that the character c at index i contributes
    // If substring does not include c, it's not a new contribution. So only consider ss including c 
    // Maximally, the number of contributions = i
    // However, we need to check if c itself has a preceding occurrence
    // And whether any character in front of c had a preceding occurrence.
    // So we will track this using a variable "substringStart"
    int numberOfSpecialSubstrings(string s) {
        unordered_map<char, int> M;
        int ans = 0;
        int newSubstrings;
        int substringStart = 0;
        for (int i=0; i<int(s.size()); i++) {
            auto c = s[i];
            if (M.find(c) != M.end()) substringStart = max(substringStart, M[c]+1);
            newSubstrings = i - substringStart +1;
            M[c] = i;
            ans += newSubstrings;
        }
        return ans;
    }

    // Here is the same solution with optimization
    int numberOfSpecialSubstringsOpt(string s) {
        int M[26];
        memset(M, -1, sizeof(M));
        int ans = 0;
        int substringStart = 0;
        for (int i=0; i<int(s.size()); i++) {
            substringStart = max(substringStart, M[s[i]-'a']+1);
            M[s[i]-'a'] = i;
            ans += i - substringStart +1;
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    string s = "abcd";
    ans = S->numberOfSpecialSubstrings(s);
    cout << "ans for " << s << " is " << ans << endl;

    s = "abab";
    ans = S->numberOfSpecialSubstrings(s);
    cout << "ans for " << s << " is " << ans << endl;

    s = "afiau";
    ans = S->numberOfSpecialSubstrings(s);
    cout << "ans for " << s << " is " << ans << endl;
}
