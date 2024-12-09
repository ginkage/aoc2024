#include "../lib.hpp"

int main() {
    unordered_map<long, long> list1, list2;

    int n = 0;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        stringstream ss(s);
        long id1, id2;
        ss >> id1 >> id2;
        list1[id1]++;
        list2[id2]++;
    }

    long long result = 0;
    for (auto id : list1)
        result += id.first * id.second * list2[id.first];
    cout << result << endl;

    return 0;
}

