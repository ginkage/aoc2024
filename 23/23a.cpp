#include "../lib.hpp"

int main() {
    unordered_map<int, unordered_set<int>> connect;
    const regex linerex("(.*)-(.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            int id1 = remap(linematch[1].str());
            int id2 = remap(linematch[2].str());
            connect[id1].insert(id2);
            connect[id2].insert(id1);
        }
    }

    int n = names.size();
    vector<string> name(n);
    for (auto &it : names)
        name[it.second] = it.first;

    int result = 0;
    for (int i = 0; i < n; i++) {
        string &ni = name[i];
        auto &ci = connect[i];
        for (int j = i + 1; j < n; j++) {
            string &nj = name[j];
            auto &cj = connect[j];
            for (int k = j + 1; k < n; k++) {
                string &nk = name[k];
                auto &ck = connect[k];
                if ((ni[0] == 't' || nj[0] == 't' || nk[0] == 't') &&
                        ci.find(j) != ci.end() && cj.find(k) != cj.end() && ck.find(i) != ci.end())
                    result++;
            }
        }
    }
    cout << result << endl;

    return 0;
}

