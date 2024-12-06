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

union hasher {
    uint64_t hash;
    struct {
        int16_t i, j, di, dj;
    } pos;
};

vector<string> grid;
int m, n;

bool is_loop(int i, int j, int di, int dj, int ti, int tj) {
    hasher h { .pos = { i, j, di, dj } };
    unordered_set<uint64_t> visit;
    visit.insert(h.hash);

    while (true) {
        int ni = i + di, nj = j + dj;
        if (ni >= 0 && nj >= 0 && ni < m && nj < n) {
            if (grid[ni][nj] == '.' && (ni != ti || nj != tj)) {
                h.pos = { ni, nj, di, dj };
                if (!visit.insert(h.hash).second) {
                    return true;
                }

                i = ni;
                j = nj;
            }
            else {
                int tmp = di;
                di = dj;
                dj = -tmp;
            }
        }
        else break;
    }

    return false;
}

int main() {
    int i = 0, j, si = -1, sj = -1;

    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        for (j = 0; j < s.size(); j++)
            if (s[j] == '^') {
                s[j] = '.';
                si = i;
                sj = j;
            }
        grid.push_back(s);
        i++;
    }

    i = si;
    j = sj;
    m = grid.size();
    n = grid[0].size();

    int di = -1, dj = 0;
    int result_a = 1, result_b = 0;
    vector<vector<bool>> visit(m, vector<bool>(n, false));
    visit[i][j] = true;

    while (true) {
        int ni = i + di, nj = j + dj;
        if (ni >= 0 && nj >= 0 && ni < m && nj < n) {
            if (grid[ni][nj] == '.') {
                if (!visit[ni][nj]) {
                    visit[ni][nj] = true;
                    result_a++;
                    if (is_loop(i, j, di, dj, ni, nj))
                        result_b++;
                }

                i = ni;
                j = nj;
            }
            else {
                int tmp = di;
                di = dj;
                dj = -tmp;
            }
        }
        else break;
    }

    cout << result_a << ' ' << result_b << endl;

    return 0;
}

