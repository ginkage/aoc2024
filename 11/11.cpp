#include "../lib.hpp"

int main() {
    string s;
    getline(cin, s);

    unordered_map<uint64_t, uint64_t> count, next;
    for (uint64_t num : split_u64(s, " "))
        count[num]++;

    for (int t = 0; t < 75; t++) {
        for (auto &p : count) {
            uint64_t num = p.first, cnt = p.second;
            if (num == 0)
                next[1] += cnt;
            else {
                int p = floor(log10(num));
                if (p & 1) {
                    uint64_t pp = pow(10, (p / 2) + 1);
                    next[num / pp] += cnt;
                    next[num % pp] += cnt;
                }
                else
                    next[num * 2024] += cnt;
            }
        }

        count.swap(next);
        next.clear();
    }

    uint64_t result = 0;
    for (auto &p : count)
        result += p.second;

    cout << result << endl;

    return 0;
}

