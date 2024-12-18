#include "../lib.hpp"

int m = 71, n = 71;
vector<string> grid(m, string(n, '.'));

static int di[] = { -1, 0, 1, 0 };
static int dj[] = { 0, -1, 0, 1 };

int path_len() {
    vector<vector<int>> score(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    q.emplace(0, 0);
    score[0][0] = 0;
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
    return score[m - 1][n - 1];
}

int main() {
    int kb = 1024;
    const regex linerex("(.*),(.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            int x = stoi(linematch[1].str());
            int y = stoi(linematch[2].str());
            // if (--kb >= 0)
                grid[y][x] = '#';
            if (path_len() < 0) {
                cout << x << ',' << y << endl;
                break;
            }
        }
    }

    //cout << path_len() << endl;

    return 0;
}

