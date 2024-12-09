#include "../lib.hpp"

bool is_safe(vector<int> &levels) {
    bool asc = levels[0] < levels[1], safe = true;
    for (int i = 1; i < levels.size() && safe; i++) {
        int dif = levels[i] - levels[i - 1], ad = abs(dif);
        safe = ((dif > 0) == asc) && (dif != 0) && (ad >= 1) && (ad <= 3);
    }
    return safe;
}

int main() {
    int result = 0;

    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        auto levels = split_i(s, " ");
        if (is_safe(levels))
            result++;
        else {
            vector<int> cp(levels.size() - 1);
            for (int j = 0; j < levels.size(); j++) {
                copy(levels.begin(), levels.begin() + j, cp.begin());
                copy(levels.begin() + j + 1, levels.end(), cp.begin() + j);
                if (is_safe(cp)) {
                    result++;
                    break;
                }
            }
        }
    }

    cout << result << endl;

    return 0;
}

