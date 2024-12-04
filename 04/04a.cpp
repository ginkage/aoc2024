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

vector<string> grid;
int m, n;

string xmas = "XMAS";

bool find(int i, int j, int di, int dj, int k) {
    if (k == xmas.size())
        return true;

    if (i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == xmas[k])
        if (find(i + di, j + dj, di, dj, k + 1))
            return true;

    return false;
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
            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++)
                    if ((di != 0 || dj != 0) && find(i, j, di, dj, 0))
                        result++;

    cout << result << endl;

    return 0;
}

