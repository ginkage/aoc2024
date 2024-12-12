#include "../lib.hpp"

vector<string> grid;
vector<vector<bool>> visit;
int m, n;

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
        if ((grid[ni][j] != c && grid[i][nj] != c)
            || (grid[ni][nj] != c && grid[ni][j] == c && grid[i][nj] == c))
            perim++;
    }

    for (int t = 0; t < 4; t++) {
        int ni = i + di[t], nj = j + dj[t];
        if (grid[ni][nj] == c)
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
        s = '.' + s + '.';
        grid.push_back(s);
    }

    string border(grid[0].size(), '.');
    grid.insert(grid.begin(), border);
    grid.push_back(border);

    m = grid.size();
    n = grid[0].size();
    visit.assign(n, vector<bool>(m, false));

    long result = 0;

    for (int i = 1; i < m-1; i++)
        for (int j = 1; j < n-1; j++)
            if (!visit[i][j]) {
                long perim = 0, area = 0;
                fill(i, j, grid[i][j], perim, area);
                result += perim * area;
            }

    cout << result << endl;

    return 0;
}

