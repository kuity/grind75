#include <iostream>
#include <set>
#include <string>
#include <unordered_map>

using namespace std;

/*
Link: https://leetcode.com/problems/accounts-merge/description/
Difficulty: Medium
Topics: array, hashtable, union find, dfs, bfs, string, sorting
*/
class Solution {
private:
    unordered_map<string, string> owner;
    unordered_map<string, string> parent;
    unordered_map<string, set<string>> unions;

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
	function<string(string)> find = [&](string x) -> string {
	    if (parent[x] == x) return x;
	    else {
		auto p = find(parent[x]);
		parent[x] = p; // Path compression optim to union find (its just caching)
		return p;

	    }
	};

	// Initially, set all parent as self
	for (auto v: accounts) {
	    auto name = v[0];
	    for (auto i=1; i<v.size(); i++) {
		parent[v[i]] = v[i];
		owner[v[i]] = name;
	    }
	}

	// Set each parent's parent as the leader's parent
	// why? if the group leader's parent is itself and each group member parent is itself (basic case),
	// want the group member's parent to be the group leader
	// if member's parent is not ifself (it was set previously), then we want to link 2 groups
	// then simply set member's parent's parent to the group leader
	// this will link the 1st to the 2nd group
	for (auto v: accounts) {
	    auto leader = find(v[1]);
	    for (auto i=2; i<v.size(); i++) {
		parent[find(v[i])] = leader;
	    }
	}

	// here, we simply establish the full group for each parent
	for (auto v: accounts) {
	    for (auto i=1; i<v.size(); i++) {
		unions[find(v[i])].insert(v[i]);
	    }
	}

	vector<vector<string>> finalList;
	for (const auto &kv: unions) {
	    auto name = owner[kv.first];
	    vector<string> emails(kv.second.begin(), kv.second.end());
	    emails.insert(emails.begin(), name);
	    finalList.push_back(emails);
	}

	return finalList;
    }
};

int main() {
    vector<vector<string>> accounts = {{"John","johnsmith@mail.com","john_newyork@mail.com"},
	{"John","johnsmith@mail.com","john00@mail.com"},
	{"Mary","mary@mail.com"},
	{"John","johnnybravo@mail.com"}};

    accounts = {{"David","David0@m.co","David1@m.co"},
	{"David","David3@m.co","David4@m.co"},
	{"David","David4@m.co","David5@m.co"},
	{"David","David2@m.co","David3@m.co"},
	{"David","David1@m.co","David2@m.co"}};

    Solution *S = new Solution();
    auto ans = S->accountsMerge(accounts);
    for (auto v: ans) {
	for (auto s: v) {
	    cout << s << ",";
	}
	cout << endl;
    }
}
