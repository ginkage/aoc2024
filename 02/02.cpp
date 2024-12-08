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

bool is_safe(vector<int> &levels) {
    bool asc = levels[0] < levels[1], safe = true;
    for (int i = 1; i < levels.size() && safe; i++) {
        int dif = levels[i] - levels[i - 1], ad = abs(dif);
        safe = ((dif > 0) == asc) && (dif != 0) && (ad >= 1) && (ad <= 3);
    }
    return safe;
}

int main() {
    int result = 0;

    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        auto levels = split(s, " ");
        if (is_safe(levels))
            result++;
        else {
            vector<int> cp(levels.size() - 1);
            for (int j = 0; j < levels.size(); j++) {
                copy(levels.begin(), levels.begin() + j, cp.begin());
                copy(levels.begin() + j + 1, levels.end(), cp.begin() + j);
                if (is_safe(cp)) {
                    result++;
                    break;
                }
            }
        }
    }

    cout << result << endl;

    return 0;
}

