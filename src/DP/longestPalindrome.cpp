#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<char, vector<int>> charPos;

public:
    string longestPalindrome(string s) {
        for (auto i=0; i<s.size(); i++) {
            auto c = s[i];
            charPos[c].push_back(i);
        }

        int longest = 1;
        string ans = s.substr(0,1);

        for (auto i=0; i<s.size(); i++) {
            auto c = s[i];
            auto positions = charPos[c];
            for (auto j=positions.size()-1; j>=0; j--) {
                auto nextPos = positions[j];
                if (nextPos <= i) break; // substr must start at index i = gg
                auto ssLen = nextPos - i + 1;
                if (ssLen <= longest) break; // can't be longer than longest = gg
                auto ss = s.substr(i, ssLen);
                auto rss = ss;
                // cout << "ss is " << ss << ", rss is " << rss << endl;
                reverse(rss.begin(), rss.end());
                if (ss == rss) { longest = ssLen; ans = ss; }
            }
        }

        return ans;
    }

    // DP solution with a recursive function
    bool checkStringAtPos(int startPos, int len, vector<vector<int>> &DP, string &s) {
        // cout << "startPos = " << startPos << ", len = " << len << endl;
        if (len<=1) return true;
        if (DP[startPos][len] == 1) return true;
        if (DP[startPos][len] == 0) return false;
        if (s[startPos] != s[startPos+len-1]) {
            DP[startPos][len] = 0;
            return false;
        }
        auto isPal = checkStringAtPos(startPos+1, len-2, DP, s);
        DP[startPos][len] = isPal;
        return isPal;
    }

    string longestPalindromeDP(string s) {
        int longest = 1;
        int index = 0;
        vector<vector<int>> DP(s.size(), vector<int>(s.size()+1, 2));

        for (auto i=0; i<s.size(); i++) {
            for (auto j=longest+1; j<=s.size()-i; j++) { // j is the length of pal
                if (checkStringAtPos(i, j, DP, s)) { 
                    longest = j; 
                    index = i;
                };
            }
        }

        return s.substr(index, longest);
    }

    // Very similar DP approach but we can do it iteratively and straightforwardly
    // A key insight here is how to ensure DP[i+1][j-1] had been previously calculated?
    // For this, we MUST start iterating from the back. i.e. i=size(s)
    string longestPalindromeDPIt(string s) { 
        int longest = 1;
        int index = 0;
        int n = s.size();
        bool DP[n][n];
        memset(DP, 0, sizeof(DP)); // Note this syntax is not really idiomatic in C++
        
        for (auto i=n-1; i>=0; i--) { // i is the starting index; must start from back
            DP[i][i] = true;
            for (auto j=i+1; j<n; j++) { // j is the end index
                if (s[i] != s[j]) continue;
                if (j-i==1) { 
                    DP[i][j] = true; 
                } else {
                    DP[i][j] = DP[i+1][j-1];
                }
                if (!DP[i][j]) continue;
                if (j-i+1 > longest) {
                    longest = j-i+1;
                    index = i;
                }
            }
        }

        return s.substr(index, longest);
    }

    // Possibly TODO: Check Manacher's Algorithm for further optimization
};

int main() {
    // vector<int> list1 = {7, 1, 5, 3 ,6, 4};
    string s1 = "babad";
    string s2 = "cbbd";
    Solution *S = new Solution();
    auto ans = S->longestPalindromeDPIt(s1);
    cout << "answer is " << ans << endl;
};
