#include "../lib.hpp"

int main() {
    ifstream cin("input.txt");
    vector<vector<int>> keys, locks;
    vector<string> grid;
    int m, n;

    while (true) {
        string s;
        getline(cin, s);
        if (!s.size() || !cin) {
            m = grid.size();
            n = grid[0].size();
            
            if (grid[0][0] == '#') {
                vector<int> lock;
                for (int j = 0; j < n; j++)
                    for (int i = 0; i < m; i++)
                        if (grid[i][j] != '#') {
                            lock.push_back(i-1);
                            break;
                        }
                locks.push_back(lock);
            }
            else {
                vector<int> key;
                for (int j = 0; j < n; j++)
                    for (int i = m-1; i >= 0; i--)
                        if (grid[i][j] != '#') {
                            key.push_back(m-2-i);
                            break;
                        }
                keys.push_back(key);
            }
                        
            if (!cin) break;
            grid.clear();
        }
        else
            grid.push_back(s);
    }
    
    int result = 0;
    for (auto &key : keys)
        for (auto &lock : locks) {
            bool good = true;
            for (int i = 0; i < n && good; i++)
                if (key[i] + lock[i] >= m-1)
                    good = false;
            if (good)
                result++;
        }
    cout << result << endl;

    return 0;
}

