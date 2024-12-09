#include "../lib.hpp"

int main() {
    int result = 0;
    bool enable = true;
    const regex linerex(".*mul\\(([\\d]+),([\\d]+)");
    const regex enrex(".*do(n't)*\\(");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        for (auto line : split_s(s, ")")) {
            smatch linematch;
            if (regex_match(line, linematch, enrex) && linematch.size() == 2)
                enable = linematch[1].str().size() == 0;

            if (regex_match(line, linematch, linerex) && linematch.size() == 3) {
                long a = stol(linematch[1].str());
                long b = stol(linematch[2].str());
                if (enable)
                    result += a * b;
            }
        }
    }

    cout << result << endl;

    return 0;
}

