#include "../lib.hpp"

bool iterate(vector<int> &program, long init_a, int k) {
    if (k < 0) {
        cout << init_a << endl;
        return true;
    }

    init_a <<= 3;
    for (int t = 0; t < 8; t++) {
        bool halt = false;
        int j = k, ptr = 0, op, val, combo;
        long reg_a = init_a + t, reg_b = 0, reg_c = 0;

        std::function<void()> ops[] = {
            [&]() { reg_a >>= combo;                    },  // adv
            [&]() { reg_b ^= val;                       },  // bxl
            [&]() { reg_b = combo & 7;                  },  // bst
            [&]() { if (reg_a != 0) ptr = val;          },  // jnz
            [&]() { reg_b ^= reg_c;                     },  // bxc
            [&]() { halt = (combo & 7) != program[j++]; },  // out
            [&]() { reg_b = reg_a >> combo;             },  // bdv
            [&]() { reg_c = reg_a >> combo;             },  // cdv
        };

        while (ptr < program.size() && !halt && j == k) {
            op = program[ptr++];
            val = program[ptr++];
            combo = (val == 4 ? reg_a : (val == 5 ? reg_b : (val == 6 ? reg_c : val)));
            ops[op]();
        }

        if (!halt && iterate(program, init_a + t, k - 1))
            return true;
    }

    return false;
}

int main() {
    string s;
    const regex linerexa("Register .: (.*)");
    const regex linerexp("Program: (.*)");
    getline(cin, s);

    smatch linematch;
    regex_match(s, linematch, linerexa);
    long init_a = stol(linematch[1].str());
    for (int i = 0; i < 4; i++)
        getline(cin, s);
    regex_match(s, linematch, linerexp);
    auto program = split_i(linematch[1].str(), ",");

    iterate(program, 0, program.size() - 1);
    return 0;
}

