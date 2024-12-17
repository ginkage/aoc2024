#include "../lib.hpp"

bool iterate(vector<int> &program, long init_a, int k) {
    if (k < 0) {
        cout << init_a << endl;
        return true;
    }

    init_a <<= 3;
    for (int t = 0; t < 8; t++) {
        bool halt = false;
        int j = k, ptr = 0;
        long reg_a = init_a + t, reg_b = 0, reg_c = 0;
        while (ptr < program.size() && !halt) {
            int op = program[ptr++];
            long val = program[ptr++], combo = val;

            if (val == 4) combo = reg_a;
            else if (val == 5) combo = reg_b;
            else if (val == 6) combo = reg_c;

            switch (op) {
                case 0: // adv
                    reg_a >>= combo;
                    break;
                case 1: // bxl
                    reg_b ^= val;
                    break;
                case 2: // bst
                    reg_b = combo & 7;
                    break;
                case 3: // jnz
                    if (reg_a != 0)
                        ptr = val;
                    break;
                case 4: // bxc
                    reg_b ^= reg_c;
                    break;
                case 5: // out
                    if ((combo & 7) != program[j])
                        halt = true;
                    else
                        j++;
                    break;
                case 6: // bdv
                    reg_b = reg_a >> combo;
                    break;
                case 7: // cdv
                    reg_c = reg_a >> combo;
                    break;
            }
        }

        if (!halt)
            if (iterate(program, init_a + t, k - 1))
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

