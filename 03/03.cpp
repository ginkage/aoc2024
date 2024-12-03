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

vector<string> split(const string &s, const string &delimiter) {
    vector<string> res;
    size_t pos_start = 0;
    for (size_t pos_end, delim_len = delimiter.length();
            (pos_end = s.find(delimiter, pos_start)) != string::npos;
            pos_start = pos_end + delim_len)
        res.push_back(s.substr(pos_start, pos_end - pos_start));
    res.push_back(s.substr(pos_start));
    return res;
}

int main() {
    int result = 0;
    bool enable = true;
    const regex linerex(".*mul\\(([\\d]+),([\\d]+)");
    const regex enrex(".*do(n't)*\\(");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        for (auto line : split(s, ")")) {
            smatch linematch;
            if (regex_match(line, linematch, enrex) && linematch.size() == 2)
                enable = linematch[1].str().size() == 0;

            if (regex_match(line, linematch, linerex) && linematch.size() == 3) {
                long a = stol(linematch[1].str());
                long b = stol(linematch[2].str());
                if (enable)
                    result += a * b;
            }
        }
    }

    cout << result << endl;

    return 0;
}

