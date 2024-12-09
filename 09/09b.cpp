#include "../lib.hpp"

int main() {
    string s;
    getline(cin, s);

    vector<pair<int, int>> file;

    int size = 0, id = 0;
    for (int i = 0; i < s.size(); i++) {
        int k = s[i] - '0';
        if (!(i&1))
            file.emplace_back(size, size + k - 1);
        size += k;
    }

    vector<int> disk(size, -1);
    for (int id = 0; id < file.size(); id++)
        for (int i = file[id].first; i <= file[id].second; i++)
            disk[i] = id;

    for (int id = file.size() - 1; id >= 0; id--) {
        auto &f = file[id];
        int fs = f.second - f.first + 1;

        for (int i = 0; i < size && i < f.first; i++) {
            if (disk[i] < 0) {
                pair<int, int> s(i, size - 1);
                for (int j = i + 1; j < size; j++)
                    if (disk[j] >= 0) {
                        s.second = j - 1;
                        break;
                    }

                int ss = s.second - s.first + 1;
                if (fs <= ss) {
                    for (int i = 0; i < fs; i++) {
                        disk[f.first + i] = -1;
                        disk[s.first + i] = id;
                    }
                    f.first = s.first;
                    f.second = f.first + fs - 1;
                    break;
                }

                i = s.second;
            }
        }
    }

    long result = 0;
    for (int i = 0; i < size; i++)
        if (disk[i] >= 0)
            result += i * disk[i];
    cout << result << endl;

    return 0;
}

