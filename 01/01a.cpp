#include "../lib.hpp"

int main() {
    vector<long> list1, list2;

    int n = 0;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        stringstream ss(s);
        long id1, id2;
        ss >> id1 >> id2;
        list1.push_back(id1);
        list2.push_back(id2);
        n++;
    }

    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    long result = 0;
    for (int i = 0; i < n; i++)
        result += abs(list1[i] - list2[i]);

    cout << result << endl;

    return 0;
}

