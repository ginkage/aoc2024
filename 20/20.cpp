#include "../lib.hpp"

static int di[] = { -1, 0, 1, 0 };
static int dj[] = { 0, -1, 0, 1 };

int main() {
    vector<string> grid;
    int si = -1, sj = -1;
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

    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> score(n, vector<int>(m, -1));
    queue<pair<int, int>> q;

    q.emplace(si, sj);
    score[si][sj] = 0;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        int s = score[p.first][p.second] + 1;
        for (int k = 0; k < 4; k++) {
            int i = p.first + di[k], j = p.second + dj[k];
            if (i >= 0 && j >= 0 && i < m && j < n && grid[i][j] != '#' && (score[i][j] < 0 || score[i][j] > s)) {
                score[i][j] = s;
                q.emplace(i, j);
            }
        }
    }

    int mc = 20;
    map<int, int> cheat;
    for (int i = 1; i < m - 1; i++)
        for (int j = 1; j < n - 1; j++) {
            int ss = score[i][j];
            if (ss >= 0) {
                for (int ni = max(i - mc, 1); ni <= min(i + mc, m - 2); ni++)
                    for (int nj = max(j - mc, 1); nj <= min(j + mc, n - 2); nj++) {
                        int d = abs(i - ni) + abs(j - nj);
                        if (d > 0 && d <= mc && grid[ni][nj] != '#') {
                            int ds = score[ni][nj] - ss - d;
                            if (ds > 0)
                                cheat[ds]++;
                        }
                    }
            }
        }

    int result = 0;
    for (auto &c : cheat)
        if (c.first >= 100)
            result += c.second;
    cout << result << endl;

    return 0;
}

