#include "../lib.hpp"

const char *col = "wubrg";
unordered_set<uint32_t> towel;

long check(string &d, vector<long> &ways, int k) {
    if (ways[k] >= 0)
        return ways[k];

    long w = 0;
    int32_t t = 0;
    for (int len = 1; k + len <= d.size() && len <= 8; len++) {
        t = (t << 3) + (strchr(col, d[k + len - 1]) - col + 1);
        if (towel.find(t) != towel.end())
            w += check(d, ways, k + len);
    }

    ways[k] = w;
    return w;
}

int main() {
    long result = 0;
    string s;

    getline(cin, s);
    auto pattern = split_s(s, ", ");
    getline(cin, s);

    for (string &s : pattern) {
        int32_t t = 0;
        for (char c : s)
            t = (t << 3) + (strchr(col, c) - col + 1);
        towel.insert(t);
    }

    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        vector<long> ways(s.size() + 1, -1);
        ways[s.size()] = 1;

        result += check(s, ways, 0);
    }

    cout << result << endl;

    return 0;
}

