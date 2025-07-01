#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    string s;
    while (cin >> s) {
        int pos1 = s.find(':') + 1;
        int pos2 = s.find('-');

        string oj = s.substr(pos1, pos2 - pos1);
        pos2 += 1;
        string id = s.substr(pos2, s.size() - pos2 - 1);
        cout << oj << "    |    " << id << "    |    " << 1 << "    |    \n";
    }
    return 0;
}
