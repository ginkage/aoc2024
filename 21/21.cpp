#include "../lib.hpp"

static vector<pair<char, pair<int, int>>> dir = {
    { '^', { -1, 0 } },
    { '>', { 0, 1 } },
    { 'v', { 1, 0 } },
    { '<', { 0, -1 } }
};

const char *numpad[] = {
    "789", 
    "456",
    "123",
    "#0A"
};

const char *dirpad[] = {
    "#^A", 
    "<v>"
};

typedef map<pair<char, char>, set<string>> paths_t;
paths_t numcmd, dircmd;

void gen_cmd(const char **keypad, int m, int n, paths_t &paths) {
    for (int si = 0; si < m; si++)
        for (int sj = 0; sj < n; sj++) {
            char from = keypad[si][sj];
            if (from == '#') continue;

            set<string> result;
            vector<vector<int>> score(m, vector<int>(n, -1));
            vector<vector<set<string>>> cmd(m, vector<set<string>>(n, set<string>()));
            queue<pair<int, int>> q;

            q.emplace(si, sj);
            score[si][sj] = 0;
            cmd[si][sj].insert("");
            while (!q.empty()) {
                auto p = q.front();
                int i = p.first, j = p.second;
                q.pop();

                int sc = score[i][j] + 1;
                for (auto &d : dir) {
                    char key = d.first;
                    int di = d.second.first, dj = d.second.second;
                    int ni = i + di, nj = j + dj;
                    if (ni >= 0 && nj >= 0 && ni < m && nj < n && keypad[ni][nj] != '#' && (score[ni][nj] < 0 || score[ni][nj] == sc)) {
                        score[ni][nj] = sc;
                        for (string ss : cmd[i][j])
                            cmd[ni][nj].insert(ss + key);
                        q.emplace(ni, nj);
                    }
                }
            }

            for (int ei = 0; ei < m; ei++)
                for (int ej = 0; ej < n; ej++) {
                    char to = keypad[ei][ej];
                    if (to != '#')
                        for (string s : cmd[ei][ej])
                            paths[make_pair(from, to)].insert(s + 'A');
                }
        }
}

unordered_map<int32_t, uint64_t> memo;

union hasher_t {
    struct { char from, to; int16_t depth; } p;
    uint32_t hash;
};

uint64_t iterate(paths_t &paths, const string &s, int depth);

uint64_t get_best(paths_t &paths, char from, char to, int depth) {
    if (depth > 25)
        return 1;

    hasher_t h = { .p = { .from = from, .to = to, .depth = (int16_t)depth } };
    auto it = memo.find(h.hash);
    if (it != memo.end())
        return it->second;

    uint64_t result = -1;
    for (const string &s : paths[make_pair(from, to)])
        result = min(result, iterate(dircmd, s, depth + 1));

    memo[h.hash] = result;
    return result;
}

uint64_t iterate(paths_t &paths, const string &s, int depth) {
    uint64_t result = 0;
    char prev = 'A';
    for (char c : s) {
        result += get_best(paths, prev, c, depth);
        prev = c;
    }
    return result;
}

int main() {
    gen_cmd(numpad, 4, 3, numcmd);
    gen_cmd(dirpad, 2, 3, dircmd);

    long result = 0;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        result += stol(s) * iterate(numcmd, s, 0);
    }
    cout << result << endl;

    return 0;
}

