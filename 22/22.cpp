#include "../lib.hpp"

int main() {
    int64_t result_a = 0;
    unordered_map<uint32_t, int> sum;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        uint32_t hash = 0;
        unordered_set<uint32_t> sold;
        int secret = stoi(s), prev = secret % 10;
        for (int i = 0; i < 2000; i++) {
            secret = (secret ^ (secret << 6)) & 0xFFFFFF;
            secret = (secret ^ (secret >> 5)) & 0xFFFFFF;
            secret = (secret ^ (secret << 11)) & 0xFFFFFF;
            int price = secret % 10, dif = price - prev;
            hash = (hash << 8) | (dif & 0xFF);
            if (i >= 3 && (sold.find(hash) == sold.end())) {
                sum[hash] += price;
                sold.insert(hash);
            }
            prev = price;
        }
        result_a += secret;
    }

    int result_b = 0;
    for (auto &p : sum)
        result_b = max(result_b, p.second);
    cout << result_a << ' ' << result_b << endl;

    return 0;
}

