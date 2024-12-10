#include "../lib.hpp"

vector<string> grid;
int m, n;

int num_at(int i, int j) {
    if (i >= 0 && j >= 0 && i < m && j < n)
        return grid[i][j] - '0';
    return -1;
}

vector<vector<bool>> visit;
queue<pair<int, int>> q;

void maybe_push(int i, int j, int num) {
    if (num_at(i, j) == num && !visit[i][j]) {
        q.emplace(i, j);
//        visit[i][j] = true;
    }
}

int score(int i, int j) {
    int sc = 0;

    visit.assign(n, vector<bool>(m, false));
    maybe_push(i, j, 0);

    while (!q.empty()) {
        auto coord = q.front();
        q.pop();

        int num = num_at(coord.first, coord.second);
        if (num == 9)
            sc++;
        else {
            num++;
            maybe_push(coord.first + 1, coord.second, num);
            maybe_push(coord.first - 1, coord.second, num);
            maybe_push(coord.first, coord.second + 1, num);
            maybe_push(coord.first, coord.second - 1, num);
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

