#include <iostream>
#include <set>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<string, set<string>> emailSetMap;
    unordered_map<string, int> emailAccountMap;
    unordered_map<int, string> idNameMap;
    int uniqueId = 0;

public:
    void updEmailAccountMap(vector<string> emails, int id) {
	for (auto i=1; i<emails.size(); i++) {
	    emailAccountMap[emails[i]] = id;
	}
	idNameMap[id] = emails[0];
    }

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
	for (auto v: accounts) {
	    auto name = v[0];
	    cout << "finding " << name << endl;
	    // Never see this name before
	    if (emailSetMap.find(name) == emailSetMap.end()) {
		set<string> nameSet(v.begin()+1, v.end());
		emailSetMap[name] = nameSet;
		updEmailAccountMap(v, uniqueId);
		uniqueId++;
		continue;
	    }

	    // Check if the email list has any repeats
	    auto nameSet = emailSetMap[name];
	    bool hasCommon = false;
	    int commonId;
	    for (auto i=1; i<v.size(); i++) {
		auto nextMail = v[i];
		if (nameSet.find(nextMail) != nameSet.end()) {
		    hasCommon = true;
		    commonId = emailAccountMap[nextMail];
		} 
		emailSetMap[name].insert(nextMail);
	    }

	    if (hasCommon) {
		updEmailAccountMap(v, commonId);
	    } else {
		updEmailAccountMap(v, uniqueId);
		uniqueId++;
	    }
	}

	// Generate the final list
	vector<vector<string>> finalList(uniqueId);
	for (auto kv: emailAccountMap) {
	    finalList[kv.second].push_back(kv.first);
	}

	for (auto kv: idNameMap) {
	    auto index = kv.first;
	    sort(finalList[index].begin(), finalList[index].end());
	    finalList[index].insert(finalList[index].begin(), kv.second);
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
