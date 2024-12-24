#include "../lib.hpp"

typedef function<int(int, int)> op_t;

static map<string, op_t> ops = {
    { "AND", [](int a, int b) { return a & b; } },
    { "OR", [](int a, int b) { return a | b; } },
    { "XOR", [](int a, int b) { return a ^ b; } }
};

struct eval_t {
    int in1, in2;
    op_t op;
};

unordered_map<int, int> ins;
unordered_map<int, eval_t> gates;

long eval(int out) {
    auto it = ins.find(out);
    if (it != ins.end())
        return it->second;

    eval_t ev = gates[out];
    int res = ev.op(eval(ev.in1), eval(ev.in2));
    ins[out] = res;
    return res;
}

int main() {
    const regex linerex("(.*): (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (s.size() == 0) break;
        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            int in = remap(linematch[1].str());
            int val = stoi(linematch[2].str());
            ins[in] = val;
        }
    }

    const regex linerex2("(.*) (.*) (.*) -> (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        smatch linematch;
        if (regex_match(s, linematch, linerex2) && linematch.size() == 5) {
            int in1 = remap(linematch[1].str());
            string op = linematch[2].str();
            int in2 = remap(linematch[3].str());
            int out = remap(linematch[4].str());
            gates[out] = eval_t { .in1 = in1, .in2 = in2, .op = ops[op] };
        }
    }

    uint64_t result = 0;
    for (auto nm : names) {
        const string &name = nm.first;
        int id = nm.second;
        if (name[0] == 'z') {
            long bit = stoi(name.substr(1, 2));
            result |= eval(id) << bit;
        }
    }
    cout << result << endl;

    return 0;
}

