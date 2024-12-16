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

    vector<pair<int, int>> boxes;
    set<pair<int, int>> new_boxes, next_boxes;
    new_boxes.emplace(ci, cj);

    while (!new_boxes.empty()) {
        for (auto &box : new_boxes) {
            int ni = box.first + di, nj = box.second + dj;

            if (grid[ni][nj] == '#') // Can't move
                return;
            else if (grid[ni][nj] == '[' && (new_boxes.find({ni, nj}) == new_boxes.end())) {
                next_boxes.emplace(ni, nj);
                next_boxes.emplace(ni, nj + 1);
            }
            else if (grid[ni][nj] == ']' && (new_boxes.find({ni, nj}) == new_boxes.end())) {
                next_boxes.emplace(ni, nj - 1);
                next_boxes.emplace(ni, nj);
            }

            boxes.push_back(box);
        }

        swap(new_boxes, next_boxes);
        next_boxes.clear();
    }

    vector<string> new_grid = grid;
    for (auto &box : boxes)
        new_grid[box.first][box.second] = '.';
    for (auto &box : boxes)
        new_grid[box.first + di][box.second + dj] = grid[box.first][box.second];
    swap(grid, new_grid);

    ci += di;
    cj += dj;
}

void print() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            cout << grid[i][j];
        cout << endl;
    }
}

int main() {
    while (true) {
        string s;
        getline(cin, s);
        if (!s.size()) break;
        stringstream ss;
        for (char c : s)
            if (c == '#')
                ss << "##";
            else if (c == 'O')
                ss << "[]";
            else if (c == '.')
                ss << "..";
            else if (c == '@') {
                ci = grid.size();
                cj = ss.str().size();
                ss << "@.";
            }
        grid.push_back(ss.str());
    }

    m = grid.size();
    n = grid[0].size();

    string moves;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        moves += s;
    }

    // cout << "\033[2J\033[1;1H";
    // print();
    for (char c : moves) {
        try_move(c);
        // usleep(100000);
        // cout << "\033[2J\033[1;1H";
        // print();
    }

    long result = 0;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == '[')
                result += 100 * i + j;

    cout << result << endl;

    return 0;
}

