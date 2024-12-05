#include <algorithm> 
#include <iostream>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

vector<int> split(const string &s, const string &delimiter) {
    vector<int> res;
    size_t pos_start = 0;
    for (size_t pos_end, delim_len = delimiter.length();
            (pos_end = s.find(delimiter, pos_start)) != string::npos;
            pos_start = pos_end + delim_len)
        res.push_back(stoi(s.substr(pos_start, pos_end - pos_start)));
    res.push_back(stoi(s.substr(pos_start)));
    return res;
}

int main() {
    int result = 0;

    unordered_map<int, unordered_set<int>> prev;

    const regex linerex("(.*)\\|(.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!s.size()) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            int a = stoi(linematch[1].str());
            int b = stoi(linematch[2].str());
            prev[a].insert(b);
        }
    }

    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        auto vec = split(s, ",");
        bool good = true;
        for (int i = 0; i < vec.size(); i++) {
            for (int j = i + 1; j < vec.size(); j++) {
                auto &rj = prev[vec[j]];
                if (rj.find(vec[i]) != rj.end()) {
                    good = false;
                    swap(vec[i], vec[j]);
                }
            }
        }

        if (!good)
            result += vec[vec.size() / 2];
    }

    cout << result << endl;

    return 0;
}

