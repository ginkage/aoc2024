#include <algorithm> 
#include <iostream>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <cmath>

using namespace std;

vector<uint64_t> split(const string &s, const string &delimiter) {
    vector<uint64_t> res;
    size_t pos_start = 0;
    for (size_t pos_end, delim_len = delimiter.length();
            (pos_end = s.find(delimiter, pos_start)) != string::npos;
            pos_start = pos_end + delim_len)
        res.push_back(stoul(s.substr(pos_start, pos_end - pos_start)));
    res.push_back(stoul(s.substr(pos_start)));
    return res;
}

static function<uint64_t(uint64_t, uint64_t)> ops[] = {
    [](uint64_t a, uint64_t b) { return a + b; },
    [](uint64_t a, uint64_t b) { return a * b; },
    [](uint64_t a, uint64_t b) { return a * pow(10, floor(log10(b)) + 1) + b; },
};

bool does_match(uint64_t res, uint64_t part, vector<uint64_t> &v, int i) {
    if (part > res)
        return false;
    if (i == v.size())
        return part == res;
    for (auto op : ops)
        if (does_match(res, op(part, v[i]), v, i + 1))
            return true;
    return false;
}

int main() {
    uint64_t result = 0;

    const regex linerex("(.*): (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            uint64_t res = stoul(linematch[1].str());
            auto v = split(linematch[2].str(), " ");
            if (does_match(res, v[0], v, 1))
                result += res;
        }
    }

    cout << result << endl;

    return 0;
}

