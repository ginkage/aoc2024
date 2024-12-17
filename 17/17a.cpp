#include "../lib.hpp"

int main() {
    string s;
    const regex linerexa("Register .: (.*)");
    const regex linerexp("Program: (.*)");
    getline(cin, s);

    smatch linematch;
    regex_match(s, linematch, linerexa);
    long reg_a = stol(linematch[1].str()), reg_b = 0, reg_c = 0;
    for (int i = 0; i < 4; i++)
        getline(cin, s);
    regex_match(s, linematch, linerexp);
    auto program = split_i(linematch[1].str(), ",");

    int ptr = 0;
    vector<int> output;
    while (ptr < program.size()) {
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
                output.push_back(combo & 7);
                break;
            case 6: // bdv
                reg_b = reg_a >> combo;
                break;
            case 7: // cdv
                reg_c = reg_a >> combo;
                break;
        }
    }

    for (int i = 0; i < output.size(); i++) {
        if (i) cout << ',';
        cout << output[i];
    }
    cout << endl;

    return 0;
}

