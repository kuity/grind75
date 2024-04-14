#include <boost/filesystem/directory.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <strings.h>
#include <sys/_select.h>
#include <unordered_map>
#include <map>
#include <regex>
#include <string>
#include <cpr/cpr.h>
#include <boost/filesystem.hpp>
#include "../lib/stringutil.h"
#include "cpr/api.h"
#include "cpr/util.h"
#include "nlohmann/json_fwd.hpp"
#include <nlohmann/json.hpp>
#include <gumbo.h>

namespace fs = boost::filesystem;
using namespace std;

string extractDescriptionVal(string s) {
    auto colonPos = s.find(": ");
    if (colonPos != string::npos) return s.substr(colonPos+2);
    return "";
}

static std::string cleantext(GumboNode* node) {
    if (node->type == GUMBO_NODE_TEXT) {
        return std::string(node->v.text.text);
    } else if (node->type == GUMBO_NODE_ELEMENT &&
        node->v.element.tag != GUMBO_TAG_SCRIPT &&
        node->v.element.tag != GUMBO_TAG_STYLE) {
        std::string contents = "";
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            const std::string text = cleantext((GumboNode*) children->data[i]);
            if (i != 0 && !text.empty()) {
                contents.append(" ");
            }
            contents.append(text);
        }
        return contents;
    } else {
        return "";
    }
}

enum UserSelectionType {
    TopicSelection,
    QuestionSelection,
    ActionSelection
};

enum UserAction {
    PrintQnDesc,
    PrintSourceCode,
    RunSourceCode,
    OpenWebPage,
    Restart,
    Quit,
    Count
};

struct LCProblem {
    vector<string> topics;
    string filepath;
    string link;
    string difficulty;
    string name; // let's just use the name of the file

    LCProblem(string filename, string description, string fp) {
        name = filename;
        filepath = fp;
        stringstream ss(description);
        string line;
        getline(ss, line);
        link = extractDescriptionVal(line);
        getline(ss, line);
        difficulty = toLowerCase(extractDescriptionVal(line));
        getline(ss, line);
        string t = extractDescriptionVal(line);
        istringstream tokenStream(t);
        string topic;
        while(getline(tokenStream, topic, ','))
            topics.push_back(toLowerCase(trim(topic)));
    }
};

class Indexer {
    regex pattern;
    fs::path p;
    string ext;
    vector<LCProblem *> *selectedTopic;
    LCProblem *selectedQuestion;
    UserAction selectedAction;

public:
    unordered_map<string, vector<LCProblem*>> M;
    vector<tuple<string, int, int, int>> DiffM;

    Indexer() {
        p = "/Users/lingzhang.jiang/projects/personal/grind75/src";
        ext = ".cpp";
        pattern = R"(Link:.*\nDifficulty:.*\nTopics.*\n)";
        selectedAction = Restart;
    }

    void scanFile(const fs::path& fp) {
        ifstream file(fp.string());
        stringstream buffer;
        buffer << file.rdbuf();
        string content = buffer.str();
        smatch match;
        if (regex_search(content, match, pattern)) {
            // cout << "File: " << fp << endl;
            LCProblem *prob = new LCProblem(fp.stem().string(), match.str(), fp.string());
            // cout << prob->link << endl;
            // cout << prob->difficulty << endl;
            for (auto t: prob->topics) {
                // cout << t << ",";
                M[t].push_back(prob);
            }
        }

        // cout << content << endl;
    }

    void scanDirectory() {
        fs::recursive_directory_iterator end_itr;
        for (fs::recursive_directory_iterator itr(p); itr!=end_itr; itr++) {
            if (fs::is_regular_file(itr->status()) && itr->path().extension() == ext) {
                scanFile(itr->path());
                // cout << dir_entry << endl;
            }
        }
    }

    void aggrCounts() {
        // map<string, tuple<int, int, int>> counts;
        map<string, vector<int>> counts;
        for (auto kv: M) {
            auto topic = kv.first;
            auto probs = kv.second;
            vector<int> V(3, 0);
            for (auto P: probs) {
                if (P->difficulty == "easy") V[0]++;
                else if (P->difficulty == "medium") V[1]++;
                else if (P->difficulty == "hard") V[2]++;
            }
            counts[topic] = V;
        }

        for (auto kv: counts) {
            tuple<string, int, int, int> val;
            get<0>(val) = kv.first;
            get<1>(val) = kv.second[0];
            get<2>(val) = kv.second[1];
            get<3>(val) = kv.second[2];
            DiffM.push_back(val);
        }
    }

    void displayAggrCounts() {
        cout << left     << setw(4)   << "#" << " | "
             << setw(25) << "Topic"   << " | "
             << setw(6)  << "Easy"    << " | " 
             << setw(6)  << "Medium"  << " | " 
             << setw(6)  << "Hard"    << endl;
        for (auto i=0; i<DiffM.size(); i++) {
            auto vals = DiffM[i];
            cout << left     << setw(4) << i << " | "
                 << setw(25) << get<0>(vals) << " | "
                 << setw(6)  << get<1>(vals) << " | " 
                 << setw(6)  << get<2>(vals) << " | " 
                 << setw(6)  << get<3>(vals) << endl;
        }
    }

    void displaySelectedTopic() {
        cout << left << setw(4)  << "#"            << " | " 
                     << setw(30) << "Question"     << " | " 
                     << setw(12) << "Difficulty"   << endl;
        for (auto i=0; i<selectedTopic->size(); i++) {
            auto qn = selectedTopic->at(i);
            cout << left << setw(4)  << i              << " | " 
                         << setw(30) << qn->name       << " | " 
                         << setw(12) << qn->difficulty << endl;
        }
    }
    
    void getUserSelection(UserSelectionType u) {
        int upperBound;
        if (u == TopicSelection) {
            upperBound = DiffM.size();
            cout << "\nSelect topic number: " << endl;
        } else if (u == QuestionSelection) {
            upperBound = selectedTopic->size();
            cout << "\nSelect question number: " << endl;
        }  else if (u == ActionSelection) {
            upperBound = UserAction::Count;
            cout << "\nSelect an action: " << endl;
            cout << "0. Display question description\n"
                 << "1. Display solution source code\n"
                 << "2. Compile and run solution\n"
                 << "3. Open question in browser\n"
                 << "4. Go back to topic selection\n"
                 << "5. Quit" << endl << endl;
        } else {
            return;
        }

        int parsedInput = -1;
        while (parsedInput < 0 || parsedInput >= upperBound) {
            // Prompt for user input
            string input;
            getline(cin, input);
            try {
                parsedInput = stoi(input);
            } catch(exception e) {
                cout << "Unable to parse input, please try again " << endl;
                continue;
            }
            if (parsedInput < 0 || parsedInput >= upperBound) {
                cout << "invalid selection, please try again" << endl;
            }
        }

        if (u == TopicSelection) {
            selectedTopic = &M[get<0>(DiffM[parsedInput])];
        } else if (u == QuestionSelection) {
            selectedQuestion = selectedTopic->at(parsedInput);
        } else if (u == ActionSelection) {
            selectedAction = static_cast<UserAction>(parsedInput);
        } else {
            return;
        }
    }

    void processUserAction() {
        switch(selectedAction) {
            case PrintQnDesc: 
                displaySelectedQuestionDesc(); 
                break;
            case PrintSourceCode: {
                cout << "Reading " << selectedQuestion->filepath << endl;
                ifstream f(selectedQuestion->filepath);
                if (f.is_open()) cout << f.rdbuf();
                break;
            }
            case RunSourceCode: {
                string compileCommand = "g++ -std=c++17 " 
                    + selectedQuestion->filepath 
                    + " lib/*.cpp -o prog.out";
                system(compileCommand.c_str());
                system("./prog.out");
                break;
            }
            case OpenWebPage: 
                system(("open " + selectedQuestion->link).c_str());
                break;
            case Restart: 
                displayAggrCounts();
                getUserSelection(TopicSelection);
                displaySelectedTopic();
                getUserSelection(QuestionSelection);
                break;
            case Quit:
                exit(0);
            default: 
                break;
        }
        cout << endl;
        getUserSelection(ActionSelection);
        processUserAction();
    }

    void displaySelectedQuestionDesc() {
        cout << endl << selectedQuestion->link << endl;
        regex pat(R"(problems/([a-z-]+))");
        smatch matches;
        if (!regex_search(selectedQuestion->link, matches, pat)) {
            cout << "No match found." << endl;
            return;
        } 
        string url = "https://leetcode.com/graphql";
        string query = R"({ question(titleSlug:")" + matches[1].str() + R"(") {content} })";
        cpr::Header headers = { {"Content-Type", "application/json"} };
        // URL-encode the query to ensure it's safe to include in a URL
        string encodedQuery = cpr::util::urlEncode(query);
        string fullUrl = url + "?query=" + encodedQuery;
        cpr::Response response = cpr::Get(cpr::Url{fullUrl});
        cout << "Status code: " << response.status_code << endl; // Should be 200
        nlohmann::json jsonResponse = nlohmann::json::parse(response.text);
        if (jsonResponse["data"]["question"]["content"] == nullptr) {
            cout << "Not able to find question description" << endl;
            return;
        }
        string content = jsonResponse["data"]["question"]["content"];
        GumboOutput *output = gumbo_parse(content.c_str());
        cout << cleantext(output->root) << endl;
    }
};

// If no cmdline params, it should show a list of topics
// It should enter into each directory and parse the header lines
// It should look for this pattern:
// Link: xxx
// Difficulty: xxx
// Topics: xxx
//
// It should aggregate questions under each topics and list them out topic | easy | med | hard
// eg. 1. strings | 1 | 5 | 0
// 
// Then, able to select a topic to show more details
// eg. Strings
// 1. Problem A. Difficulty Med. Topics: a, b, c
// 
// After which, it can do one of a few things:
// 1. Parse the link, fetch and print the problem description with curl
// 2. Print the solution source code 
// 3. Compile and run the source code
// 4. Open the LC page in browser
// 5. Go back to the start (show topics)
//
// TODO:
// Able to fuzzy search questions
// Able to generate a boilerplate template
int main(int argc, char *argv[]) {
    // Using a while loop to iterate through arguments 
    int i = 0; 
    while (i < argc) { 
        cout << "Argument " << i + 1 << ": " << argv[i] 
             << endl; 
        i++; 
    } 

    Indexer *indexer = new Indexer();
    indexer->scanDirectory();
    indexer->aggrCounts();
    indexer->processUserAction();
    return 0;
}
