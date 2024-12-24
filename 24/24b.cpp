#include "../lib.hpp"

typedef function<int(int, int)> fun_t;

enum op_t {
    op_and,
    op_or,
    op_xor
};

static map<string, op_t> name_op = {
    { "AND", op_and },
    { "OR", op_or },
    { "XOR", op_xor }
};

static map<op_t, fun_t> op_fun = {
    { op_and, [](int a, int b) { return a & b; } },
    { op_or, [](int a, int b) { return a | b; } },
    { op_xor, [](int a, int b) { return a ^ b; } }
};

struct eval_t {
    int in1, in2;
    string opname;
    op_t op;
    fun_t fun;
};

unordered_map<int, int> ins;
unordered_map<int, eval_t> gates;
vector<string> name;

long eval(int out) {
    auto it = ins.find(out);
    if (it != ins.end())
        return it->second;

    eval_t ev = gates[out];
    int res = ev.fun(eval(ev.in1), eval(ev.in2));
    ins[out] = res;
    return res;
}

string tab(int depth) {
    return string (depth, ' ');
}

void print(int out, int depth) {
    auto it = gates.find(out);
    if (it == gates.end())
        cout << tab(depth) << name[out] << endl;
    else {
        cout << tab(depth) << "( " << endl;
        eval_t ev = it->second;
        print(ev.in1, depth + 1);
        cout << tab(depth) << ' ' << ev.opname << endl;
        print(ev.in2, depth + 1);
        cout << tab(depth) << " )" << endl;
    }
}

enum node_type {
    nd_in,
    nd_xor,
    nd_and,
    nd_or,
    nd_sand,
    nd_sxor
};

unordered_map<int, pair<node_type, int>> guess;

void check(int id) {
    eval_t &ev = gates[id];
    string &nm = name[id];
    eval_t &e1 = gates[ev.in1], &e2 = gates[ev.in2];
    auto it1 = guess.find(ev.in1), it2 = guess.find(ev.in2);
    string &name1 = name[ev.in1], &name2 = name[ev.in2];

    if (nm[0] == 'z' && nm != "z45") {
        if (ev.op != op_xor) {
            cout << nm << " expected XOR, got " << ev.opname << endl;
            cout << e1.opname << endl;
            if (it1 != guess.end())
                cout << it1->second.second << endl;
            cout << e2.opname << endl;
            if (it2 != guess.end())
                cout << it2->second.second << endl;
        }
    }

    auto ig = guess.find(id);
    if (ig != guess.end())
        return;

    if (ev.op == op_and || ev.op == op_xor) {
        if ((e1.op == op_xor && e2.op == op_or) || (e1.op == op_or && e2.op == op_xor)) {
        }
        else {
            cout << "Malformed AND/XOR at " << nm << endl;
        }
    }
    else if (ev.op == op_or) {
        if (e1.op == op_and && e2.op == op_and) {
        }
        else {
            cout << "Malformed OR at " << nm << endl;
        }
    }
}

int main() {
    ifstream cin("input.txt");
    const regex linerex("(.*): (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (s.size() == 0) break;
        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            string name = linematch[1].str();
            int in = remap(name);
            int val = stoi(linematch[2].str());
            ins[in] = val;
            guess[in] = make_pair(nd_in, stoi(name.substr(1, 2)));
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
            string opname = linematch[2].str();
            int in2 = remap(linematch[3].str());
            int out = remap(linematch[4].str());
            op_t op = name_op[opname];
            fun_t fun = op_fun[op];
            gates[out] = eval_t { .in1 = in1, .in2 = in2, .opname = opname, .op = op, .fun = fun };
        }
    }

    swap(gates[remap("z12")], gates[remap("kth")]);
    swap(gates[remap("z26")], gates[remap("gsd")]);
    swap(gates[remap("z32")], gates[remap("tbt")]);
    swap(gates[remap("vpm")], gates[remap("qnf")]);

    name.resize(names.size());
    for (auto &it : names)
        name[it.second] = it.first;

    // Step 0: Initial inputs
    for (auto &it : gates) {
        int out = it.first;
        eval_t &ev = it.second;
        string &name1 = name[ev.in1], &name2 = name[ev.in2];
        if ((name1[0] == 'x' || name1[0] == 'y') &&
                (name2[0] == 'x' || name2[0] == 'y')) {
            int i1 = stoi(name1.substr(1, 2));
            int i2 = stoi(name2.substr(1, 2));
            if (i1 != i2)
                cout << i1 << ' ' << i2 << endl;
            else if (ev.op == op_and)
                guess[out] = make_pair(nd_and, i1);
            else if (ev.op == op_xor)
                guess[out] = make_pair(nd_xor, i1);
            else
                cout << "wtf" << endl;
        }
    }

    // Step 1
    for (auto &it : gates) {
        int out = it.first;
        eval_t &ev = it.second;
        if (ev.op == op_and || ev.op == op_xor) {
            auto it1 = guess.find(ev.in1), it2 = guess.find(ev.in2);
            if (it1 != guess.end() && it2 != guess.end()) {
                auto g1 = it1->second, g2 = it2->second;
                if ((g1.first == nd_xor && g1.second == 1 && g2.first == nd_and && g2.second == 0) ||
                        (g2.first == nd_xor && g2.second == 1 && g1.first == nd_and && g1.second == 0))
                    guess[out] = make_pair(ev.op == op_and ? nd_sand : nd_sxor, 1);
            }
        }
    }

    // Boundary conditions
    guess[remap("z00")] = make_pair(nd_xor, 0);
    guess[remap("z45")] = make_pair(nd_or, 44);

    uint64_t result = 0;
    for (auto nm : names) {
        const string &node = nm.first;
        int id = nm.second;
        check(id);
        if (node[0] == 'z') {
            long bit = stoi(node.substr(1, 2));
            result |= eval(id) << bit;
/*
            if (bit < 5) {
                cout << endl << node << " = ";
                print(id, 0);
                cout << endl;
            }
*/
        }
    }
    cout << result << endl;

    return 0;
}

