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

    int n = 0;
    for (int i = 0; i < disk.size(); i++) {
        if (disk[i] < 0) {
            int id = file.size() - 1;
            auto &f = file[id];
            if (f.first < i) {
                n = i;
                break;
            }

            disk[i] = id;
            disk[f.second] = -1;
            f.second--;
            if (f.first > f.second)
                file.erase(file.begin() + id);
        }
    }

    long result = 0;
    for (int i = 0; i < n; i++)
        result += i * disk[i];
    cout << result << endl;

    return 0;
}

