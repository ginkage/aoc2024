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

    for (int i = 1; i < m - 1; i++)
        for (int j = 1; j < n - 1; j++)
            if (grid[i][j] == 'A') {
                if (
                    ((grid[i-1][j-1] == 'M' && grid[i+1][j+1] == 'S') || (grid[i-1][j-1] == 'S' && grid[i+1][j+1] == 'M')) &&
                    ((grid[i+1][j-1] == 'M' && grid[i-1][j+1] == 'S') || (grid[i+1][j-1] == 'S' && grid[i-1][j+1] == 'M'))
                   )
                        result++;
            }

    cout << result << endl;

    return 0;
}

