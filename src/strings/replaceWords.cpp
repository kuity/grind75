#include <iostream>
#include <set>
#include <sstream>

using namespace std;

/*
Link: https://leetcode.com/problems/replace-words
Difficulty: Medium
Topics: array,hashtable,string,trie
*/
vector<string> splitString(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

string joinStrings(const vector<string>& vec, char delimiter) {
    string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i != 0) {
            result += delimiter;
        }
        result += vec[i];
    }
    return result;
}

class Trie {
public:
    vector<Trie*> children;
    Trie() {
        children = vector<Trie *>(27, nullptr);
    }
    
    void insert(string word) {
        if (word.length() == 0) {
            children[26] = (children[26] == nullptr) ? new Trie() : children[26];
        } else {
            int val = word[0] - 'a';
            if (children[val] == nullptr) {
                children[val] = new Trie();
            }
            children[val]->insert(word.substr(1));
        }
    }
    
    bool search(string word) {
        if (word.length() == 0) {
            return children[26] != nullptr;
        } else {
            int val = word[0] - 'a';
            if (children[val] == nullptr) {
                return false;
            } else {
                return children[val]->search(word.substr(1));
            }
        }
    }
   
   int partialSearch(string word, int length) {
       bool hasRoot = children[26] != nullptr;
       // cout << "partialSearch " << word << " length " << length << " hasRoot = " << hasRoot << endl;
       if (word.length() == 0) {
           return hasRoot ? length : -1;
       } else if (hasRoot) {
           return length;
       } else {
           int val = word[0] - 'a';
           if (children[val] == nullptr) {
               return -1;
           } else {
               return children[val]->partialSearch(word.substr(1), length+1);
           }
       }
   }


   bool startsWith(string prefix) {
       if (prefix.length() == 0) {
           return true;
       } else {
           int val = prefix[0] - 'a';
           if (children[val] == nullptr) {
               return false;
           } else {
               return children[val]->startsWith(prefix.substr(1));
           }
       }
   }
};

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        set<string> S = set(dictionary.begin(), dictionary.end());
        auto V = splitString(sentence, ' ');
        for (auto i=0; i<V.size(); i++) {
            auto w = V[i];
            for (auto j=1; j<=w.size(); j++) {
                auto root = w.substr(0, j);
                // cout << "looking for " << root << endl;
                if (S.find(root) != S.end()) {
                    V[i] = root;
                    break;
                }
            }
        }
        return joinStrings(V, ' ');
    }

    string replaceWords2(vector<string>& dictionary, string sentence) {
        Trie *T = new Trie();
        sentence += ' ';
        for (auto w: dictionary) T->insert(w);
        string ans = "";
        string word = "";
        for (auto c: sentence) {
            if (c == ' ') {
                auto l = T->partialSearch(word, 0);
                if (l > 0) ans += word.substr(0, l); 
                else ans += word;
                ans += ' ';
                word = "";
            } else {
                word += c;
            }
        }
        return ans.substr(0, ans.size()-1);
    }
};

int main() {
    Solution *S = new Solution();
    vector<string> D = {"cat","bat","rat"};
    string ans = S->replaceWords(D, "the cattle was rattled by the battery");
    cout << "ans is " << ans << endl;
    string ans2 = S->replaceWords2(D, "the cattle was rattled by the battery");
    cout << "ans2 is " << ans2 << endl;

}
