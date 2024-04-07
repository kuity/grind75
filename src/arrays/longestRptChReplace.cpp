#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
Link: https://leetcode.com/problems/longest-repeating-character-replacement/
Difficulty: Medium
Topics: hashtable, string, sliding window
*/
class Solution {
public:
    int getMaxVal(unordered_map<char, int> &M) {
        return max_element(M.begin(), M.end(),
            [] (const pair<int, int>& p1, const pair<int, int>& p2) {
                return p1.second < p2.second; })->second;
    }

    int characterReplacement(string s, int k) {
        int distinctChars = 0;
        int start = 0;
        int end = 0;
        int longest = 0;
        unordered_map<char, int> M;
        while (end < s.size()) {
            auto nextChar = s[end];
            M[nextChar]++;
            end++;
            auto maxVal = getMaxVal(M);
            while (end-start-maxVal > k) {
                auto prevChar = s[start];
                M[prevChar]--;
                start++;
                maxVal = getMaxVal(M);
            }
            if (end-start > longest) longest = end-start;
        }

        return longest;
    }

    // A more efficient implementation
    // Also one optimization:
    // If window reaches some length N,
    // we don't need to shrink the window just to fit K
    // we can just slide the window
    int characterReplacementEfficient(string s, int k) {
        // Base case...
        if (s.size() == 0) return 0;
        // Make an array...
        vector <int> arr(26);
        // Initialize largestCount & beg pointer...
        int beg = 0, largestCount = 0;
        // Traverse all characters through the loop...
        for (int end = 0; end < s.size(); end++) {
            // Get the largest count of a single, unique character in the current window...
            largestCount = max(largestCount, ++arr[s[end] - 'A']);
            // We are allowed to have at most k replacements in the window...
            // So, if max character frequency + distance between beg and end is greater than k...
            // That means we have met a largest possible sequence, we can move the window to right...
            if (end - beg + 1 - largestCount > k)       // The main equation is: end - beg + 1 - largestCount...
                arr[s[beg++] - 'A']--;
        }
        // Return the sequence we have passes, which is s.length() - beg...
        return s.length() - beg;
    }
};

int main() {
    Solution *S = new Solution();
    string s;
    int ans;

    s = "ABAB";
    ans = S->characterReplacement(s, 2);
    cout << "ans is " << ans << endl;

    ans = S->characterReplacementEfficient(s, 2);
    cout << "ans is " << ans << endl;

    s = "AABABBA";
    ans = S->characterReplacement(s, 1);
    cout << "ans is " << ans << endl;

    ans = S->characterReplacementEfficient(s, 1);
    cout << "ans is " << ans << endl;

    s = "ABCABCAAAA";
    ans = S->characterReplacement(s, 2);
    cout << "ans is " << ans << endl;

    ans = S->characterReplacementEfficient(s, 2);
    cout << "ans is " << ans << endl;

    s = "ABCABCAAAACC";
    ans = S->characterReplacement(s, 2);
    cout << "ans is " << ans << endl;

    ans = S->characterReplacementEfficient(s, 2);
    cout << "ans is " << ans << endl;
}
