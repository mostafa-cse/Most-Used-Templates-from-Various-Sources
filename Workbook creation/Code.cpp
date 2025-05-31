#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    string s;
    map<int, string> problems;
    while (getline(cin, s)) {
        string a, b, c;
        getline(cin, a);
        getline(cin, b);
        getline(cin, c);

        int pos = find(s.begin(), s.end(), '-') - s.begin();
        string id = "";
        for (int i = pos - 2; i >= 0; i--) {
            if (s[i] == ' ') break;;
            if (s[i] == 'E') break;
            id += s[i];
        }
        reverse(id.begin(), id.end());
        string name = "";
        for (int i = pos + 2,cnt = 0; i < s.size(); i++) {
            if (name.back() == ' ' and name.back() == s[i]) continue;
            if (isdigit(s[i])) break;
            name += s[i];
        }
        problems[stoi(id)] = name;
    }

    for (auto [f,s] : problems) {
        cout << "[problem:UVA-" << f << "] ";
        // cout << f << " " << s << endl;
    }
    return 0;
}
