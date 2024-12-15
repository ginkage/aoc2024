#include "../lib.hpp"

vector<string> grid;
int ci = -1, cj = -1, m, n;

static unordered_map<char, pair<int, int>> dir = {
    { '^', { -1, 0 } },
    { 'v', { 1, 0 } },
    { '<', { 0, -1 } },
    { '>', { 0, 1 } }
};

void try_move(char c) {
    auto &d = dir[c];
    int di = d.first, dj = d.second;
    int ni = ci + di, nj = cj + dj;

    for (int i = ni, j = nj; grid[i][j] != '#'; i += di, j += dj)
        if (grid[i][j] == '.') {
            swap(grid[ni][nj], grid[i][j]);
            ci = ni;
            cj = nj;
            break;
        }
}

void print() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            if (i == ci && j == cj)
                cout << '@';
            else
                cout << grid[i][j];
        cout << endl;
    }
    cout << endl;
}

int main() {
    while (true) {
        string s;
        getline(cin, s);
        if (!s.size()) break;
        grid.push_back(s);
    }

    m = grid.size();
    n = grid[0].size();

    for (int i = 0; i < m && ci < 0; i++)
        for (int j = 0; j < n && cj < 0; j++)
            if (grid[i][j] == '@') {
                grid[i][j] = '.';
                ci = i;
                cj = j;
                break;
            }

    string moves;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        moves += s;
    }

    for (char c : moves) {
        try_move(c);
        //print();
    }

    long result = 0;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == 'O')
                result += 100*i + j;

    cout << result << endl;

    return 0;
}

