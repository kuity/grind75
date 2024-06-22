#include <iostream>
#include <string>

using namespace std;

/*
Link: https://leetcode.com/problems/find-common-characters
Difficulty: Easy
Topics: array, hashtable, string
*/
class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        int tracker[26][words.size()];
        memset(tracker, 0, sizeof(tracker));
        vector<string> ans;
        for (auto i=0; i<words.size(); i++) {
            auto word = words[i];
            for (auto c: word) {
                int n = c - 'a';
                tracker[n][i]++;
            }
        }

        for (auto i=0; i<26; i++) {
            int m = 100;
            for (auto j=0; j<words.size(); j++) {
                if (tracker[i][j] < m) {
                    m = tracker[i][j];
                    if (m == 0) break;
                }
            }
            char c = i + 'a';
            string s = string(1, c);
            for (auto x=0; x<m; x++) {
                ans.push_back(s);
            }
            
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    vector<string> words = {"bella","label","roller"};
    auto ans = S->commonChars(words);
    for (auto s: ans) cout << s;
    cout << endl;
}
