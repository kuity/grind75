#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int addCharsToSet(string s, unordered_set<int>&H) {
        int l = 0;
        for (char c: s) {
            if (H.count(c)) {
                return l;
            } else {
                H.insert(c);
                l++;
            }
        }
        return l;
    }

    int lengthOfLongestSubstring(string s) {
        int sLen = s.length();
        if (sLen == 0) { 
            return 0; 

        }

        unordered_set<int>charSet;
        int currentLen = addCharsToSet(s, charSet);
        char currentChar = s[0];
        int maxLen = currentLen;

        for (int i=1; i<s.length(); i++) {
            char nextChar = s[i];
            int endCharIndex = i-1+currentLen;

            // Case 1: char after current substring is EoS. we can just return 
            if (endCharIndex >= sLen) {
                break;
            }

            char endChar = s[endCharIndex];
            // Case 2: char after current substring == currentChar
            if (endChar == currentChar) {
                currentLen = currentLen + addCharsToSet(s.substr(endCharIndex+1), charSet);
                maxLen = max(maxLen, currentLen);
            }
            // Case 3: char after current substring != currentChar 
            else {
                charSet.erase(currentChar);
                currentLen--;
            }
            currentChar = nextChar;
        }

        return maxLen;
    }
};

int main() {
    string s = "abcabcbb";
    Solution *S = new Solution();
    int ans = S->lengthOfLongestSubstring(s);
    cout << s << ": " << ans << endl;
    s = "bbbbb";
    ans = S->lengthOfLongestSubstring(s);
    cout << s << ": " << ans << endl;
    s = "pwwkew";
    ans = S->lengthOfLongestSubstring(s);
    cout << s << ": " << ans << endl;
    s = "hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    ans = S->lengthOfLongestSubstring(s);
    cout << s << ": " << ans << endl;
}
