#include <iostream>
#include <unordered_map>

using namespace std;


class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
	unordered_map<char, int> characters;
	for (char a: magazine) {
	    if (characters.find(a) != characters.end()) {
		characters[a]++;
	    } else {
		characters[a] = 1;
	    }
	}

	for (char b: ransomNote) {
	    if (characters.find(b) == characters.end()) {
		return false;
	    } else {
		characters[b] -= 1;
		if (characters[b] == 0) {
		    characters.erase(b);
		}
	    }
	}

	return true;
    }
};

int main() {
    string s = "a";
    string t = "b";
    Solution *S = new Solution();
    cout << S->canConstruct(s, t) << endl;

    s = "aa";
    t = "ab";
    cout << S->canConstruct(s, t) << endl;

    s = "aa";
    t = "aab";
    cout << S->canConstruct(s, t) << endl;
}
