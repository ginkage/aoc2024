#include "../lib.hpp"

vector<string> grid;
int m, n;

int num_at(int i, int j) {
    if (i >= 0 && j >= 0 && i < m && j < n)
        return grid[i][j] - '0';
    return -1;
}

vector<vector<int>> rating;
queue<pair<int, int>> q;

void maybe_push(int i, int j, int num, int r) {
    if (num_at(i, j) == num) {
        if (rating[i][j] == 0)
            q.emplace(i, j);
        rating[i][j] += r;
    }
}

int score(int i, int j) {
    int sc = 0;

    rating.assign(n, vector<int>(m, 0));
    maybe_push(i, j, 0, 1);

    while (!q.empty()) {
        auto coord = q.front();
        q.pop();

        int num = num_at(coord.first, coord.second);
        int r = rating[coord.first][coord.second];
        if (num == 9)
            sc += r; // sc++ for A
        else {
            num++;
            maybe_push(coord.first + 1, coord.second, num, r);
            maybe_push(coord.first - 1, coord.second, num, r);
            maybe_push(coord.first, coord.second + 1, num, r);
            maybe_push(coord.first, coord.second - 1, num, r);
        }
    }

    return sc;
}

int main() {
    int result = 0;

    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        grid.push_back(s);
    }

    m = grid.size();
    n = grid[0].size();

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (num_at(i, j) == 0)
                result += score(i, j);

    cout << result << endl;

    return 0;
}

