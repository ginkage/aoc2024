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

    vector<int> best;
    for (int i = 0; i < n; i++) {
        unordered_set<int> clique = connect[i];
        clique.insert(i);

        for (int j : connect[i]) {
            unordered_set<int> &edge = connect[j];
            vector<int> out;
            for (int k : clique)
                if (k != j && edge.find(k) == edge.end())
                    out.push_back(k);
            if (out.size() < 3)
                for (int k : out)
                    clique.erase(k);
        }

        if (clique.size() > best.size())
            best.assign(clique.begin(), clique.end());
    }

    set<string> result;
    for (int id : best)
        result.insert(name[id]);
    for (const string &nm : result)
        cout << ',' << nm;
    cout << endl;

    return 0;
}

