#include "../lib.hpp"

struct node_t {
    unordered_map<char, unique_ptr<node_t>> child;
    bool leaf { false };
};
node_t root;

long check(string &d, vector<long> &ways, int k) {
    if (ways[k] >= 0)
        return ways[k];

    long w = 0;
    node_t *node = &root;
    for (int j = k; j < d.size(); j++) {
        auto it = node->child.find(d[j]);
        if (it == node->child.end()) break;
        node = it->second.get();
        if (node->leaf)
            w += check(d, ways, j + 1);
    }

    return (ways[k] = w);
}

int main() {
    string s;
    getline(cin, s);
    for (string &p : split_s(s, ", ")) {
        node_t *node = &root;
        for (char c : p) {
            if (!node->child[c].get())
                node->child[c] = make_unique<node_t>();
            node = node->child[c].get();
        }
        node->leaf = true;
    }
    getline(cin, s);

    long result_a = 0, result_b = 0;
    while (true) {
        getline(cin, s);
        if (!cin) break;
        vector<long> ways(s.size() + 1, -1);
        ways[s.size()] = 1;
        long w = check(s, ways, 0);
        result_a += w > 0;
        result_b += w;
    }
    cout << result_a << ' ' << result_b << endl;

    return 0;
}

