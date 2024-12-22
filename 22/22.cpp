#include "../lib.hpp"

union hasher_t {
    struct { int8_t d1, d2, d3, d4; } seq;
    uint32_t hash;
};

static inline long step(long secret) {
    secret = (secret ^ (secret << 6)) & 0xFFFFFF;
    secret = (secret ^ (secret >> 5)) & 0xFFFFFF;
    secret = (secret ^ (secret << 11)) & 0xFFFFFF;
    return secret;
}

int main() {
    unordered_map<uint32_t, uint64_t> sum;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        long secret = stol(s);
        int price = secret % 10;
        hasher_t h;
        unordered_set<uint32_t> sold;

        for (int i = 0; i < 2000; i++) {
            long next = step(secret);
            int np = next % 10, dif = np - price;

            h.seq.d1 = h.seq.d2;
            h.seq.d2 = h.seq.d3;
            h.seq.d3 = h.seq.d4;
            h.seq.d4 = dif;

            if (i >= 3 && (sold.find(h.hash) == sold.end())) {
                sum[h.hash] += np;
                sold.insert(h.hash);
            }

            secret = next;
            price = np;
        }
    }

    uint64_t result = 0;
    for (auto &p : sum)
        result = max(result, p.second);
    cout << result << endl;

    return 0;
}

