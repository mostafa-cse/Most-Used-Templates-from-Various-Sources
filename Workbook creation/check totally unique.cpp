#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    string s;
    
    map<string, int> cnt;
    while (getline(cin, s)) {
        if (s[0] != '[') {
            cout << s << endl;
            continue;
        } 
        string num = "";
        set<int> problem;
        for (char c : s) {
            if (c == ']') {
                if (stoi(num) >= 100) {
                    if (!cnt.count(num)) problem.insert(stoi(num));
                    cnt[num]++;
                }
                num = "";
            }
            if (isdigit(c)) {
                num += c;
            }
        }
        for (auto f : problem) {
            cout << "[problem:UVA-" << f << "] ";
        }
        cout << endl;
    }
    
    for (auto [f,s] : cnt) {
        cout << s;
    }
    return 0;
}

