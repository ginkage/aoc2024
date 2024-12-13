#include "../lib.hpp"

int main() {
    long result = 0;

    const regex linerexa("Button A: X\\+(\\d+), Y\\+(\\d+)");
    const regex linerexb("Button B: X\\+(\\d+), Y\\+(\\d+)");
    const regex linerexp("Prize: X=(\\d+), Y=(\\d+)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        long ax, ay, bx, by, px, py;

        smatch linematch;
        if (regex_match(s, linematch, linerexa) && linematch.size() == 3) {
            ax = stoi(linematch[1].str());
            ay = stoi(linematch[2].str());
        }
        getline(cin, s);
        if (regex_match(s, linematch, linerexb) && linematch.size() == 3) {
            bx = stoi(linematch[1].str());
            by = stoi(linematch[2].str());
        }
        getline(cin, s);
        if (regex_match(s, linematch, linerexp) && linematch.size() == 3) {
            px = stoi(linematch[1].str());
            py = stoi(linematch[2].str());
        }
        getline(cin, s);

        px += 10000000000000;
        py += 10000000000000;

        long l = ay * bx - ax * by, r = ay * px - ax * py;
        if (l != 0) {
            long b = r / l, a = (px - bx * b) / ax;
            if (ax * a + bx * b == px && ay * a + by * b == py)
                result += 3 * a + b;
        }
    }

    cout << result << endl;

    return 0;
}

