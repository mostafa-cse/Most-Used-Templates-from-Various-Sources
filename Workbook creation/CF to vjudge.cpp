#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    string s;
    int cnt = 1;
    while (cin >> s) {
        s = s.substr(42);
        string a;
        for (char c : s) {
            if (c != '/') {
                a.push_back(c);
            }
        }
        cout << "CodeForces	|	" << a << "	|	1	|	\n";
    }
    return 0;
}

