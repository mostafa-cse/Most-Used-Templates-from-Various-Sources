#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    string s;
    
    set<int> problem;
    while (getline(cin, s)) {
        string num = "";
        for (char c : s) {
            if (c == ']') {
                problem.insert(stoi(num));
                num = "";
            }
            if (isdigit(c)) {
                num += c;
            }
        }
    }
    for (auto f : problem) {
        cout << "[problem:UVA-" << f << "] ";
    }
    return 0;
}

