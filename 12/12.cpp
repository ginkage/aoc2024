#include "../lib.hpp"

vector<string> grid;
vector<vector<bool>> visit;
int m, n;

static inline char get(int i, int j) {
    return (i >= 0 && j >= 0 && i < m && j < n) ? grid[i][j] : '.';
}

int di[] = { -1, 0, 1, 0 };
int dj[] = { 0, -1, 0, 1 };

int ci[] = { -1, -1, 1, 1 };
int cj[] = { -1, 1, -1, 1 };

void fill(int i, int j, char c, long &perim, long &area) {
    if (visit[i][j])
        return;

    area++;
    visit[i][j] = true;

    for (int t = 0; t < 4; t++) {
        int ni = i + ci[t], nj = j + cj[t];
        if ((get(ni, j) != c && get(i, nj) != c)
            || (get(ni, nj) != c && get(ni, j) == c && get(i, nj) == c))
            perim++;
    }

    for (int t = 0; t < 4; t++) {
        int ni = i + di[t], nj = j + dj[t];
        if (get(ni, nj) == c)
            fill(ni, nj, c, perim, area);
//        else
//            perim++;
    }
}

int main() {
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        grid.push_back(s);
    }

    m = grid.size();
    n = grid[0].size();
    visit.assign(n, vector<bool>(m, false));

    long result = 0;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (!visit[i][j]) {
                long perim = 0, area = 0;
                fill(i, j, get(i, j), perim, area);
                result += perim * area;
            }

    cout << result << endl;

    return 0;
}

