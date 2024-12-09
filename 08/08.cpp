#include "../lib.hpp"

int main() {
    unordered_map<char, vector<pair<int, int>>> freq;

    int m = 0, n;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        n = s.size();
        for (int j = 0; j < n; j++)
            if (s[j] != '.')
                freq[s[j]].emplace_back(m, j);

        m++;
    }

    set<pair<int, int>> loc;

    for (auto &f : freq) {
        auto &p = f.second;
        for (int i = 0; i < p.size(); i++) {
            auto &pi = p[i];
            for (int j = i + 1; j < p.size(); j++) {
                auto &pj = p[j];
                int dr = pj.first - pi.first;
                int dc = pj.second - pi.second;
                for (int k = 0; ; k++) {
                    pair<int, int> a1(pi.first - dr * k, pi.second - dc * k);
                    if (a1.first >= 0 && a1.first < m && a1.second >= 0 && a1.second < n)
                        loc.insert(a1);
                    else break;
                }
                for (int k = 0; ; k++) {
                    pair<int, int> a2(pj.first + dr * k, pj.second + dc * k);
                    if (a2.first >= 0 && a2.first < m && a2.second >= 0 && a2.second < n)
                        loc.insert(a2);
                    else break;
                }
            }
        }
    }

    cout << loc.size() << endl;

    return 0;
}

