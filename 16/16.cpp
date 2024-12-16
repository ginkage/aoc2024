#include "../lib.hpp"

vector<string> grid;
int m, n;

union hasher {
    struct {
        int16_t i, j, di, dj;
    } pos;
    uint64_t hash;
};

struct state {
    hasher h;
    uint64_t prev;
    long score;
};

int16_t ci[] = { 0, -1, 0, 1 };
int16_t cj[] = { -1, 0, 1, 0 };

int main() {
    int16_t si = -1, sj = -1;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        if (si < 0)
            for (sj = 0; sj < s.size(); sj++)
                if (s[sj] == 'S') {
                    si = grid.size();
                    break;
                }

        grid.push_back(s);
    }

    m = grid.size();
    n = grid[0].size();

    long result = -1;
    unordered_map<uint64_t, long> best;
    unordered_map<uint64_t, unordered_set<uint64_t>> prev;
    unordered_set<uint64_t> ends;
    queue<state> q;
    q.push(state { .h = { .pos = { si, sj, 0, 1 } }, .prev = 0, .score = 0 });

    while (!q.empty()) {
        state s = q.front();
        q.pop();

        auto it = best.find(s.h.hash);
        if (it != best.end()) {
            if (s.score < it->second)
                prev[s.h.hash].clear();
            else {
                if (s.score == it->second)
                    prev[s.h.hash].insert(s.prev);
                continue;
            }
        }

        best[s.h.hash] = s.score;
        prev[s.h.hash].insert(s.prev);
        int16_t i = s.h.pos.i, j = s.h.pos.j, di = s.h.pos.di, dj = s.h.pos.dj;
        for (int k = 0; k < 4; k++) {
            int16_t ndi = ci[k], ndj = cj[k];
            if (grid[i + ndi][j + ndj] != '#') {
                long ds = 1;
                if (ndi == -di && ndj == -dj)
                    ds += 2000;
                else if (ndi != di || ndj != dj)
                    ds += 1000;
                q.push(state { .h = { .pos = { i + ndi, j + ndj, ndi, ndj } }, .prev = s.h.hash, .score = s.score + ds });
            }
        }

        if (grid[i][j] == 'E') {
            if (result < 0 || result > s.score) {
                ends.clear();
                result = s.score;
            }
            if (result == s.score)
                ends.insert(s.h.hash);
        }
    }

    cout << result << endl;

    queue<uint64_t> bt;
    for (uint64_t h : ends)
        bt.push(h);

    set<pair<int, int>> cells;
    while (!bt.empty()) {
        hasher h { .hash = bt.front() };
        bt.pop();

        cells.emplace(h.pos.i, h.pos.j);
        if (grid[h.pos.i][h.pos.j] != 'S')
            for (uint64_t p : prev[h.hash])
                bt.push(p);
    }
    cout << cells.size() << endl;

    return 0;
}

