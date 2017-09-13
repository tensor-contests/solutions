#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s1, s2, s;
    cin >> s1 >> s2 >> s;
    map<char, char> m;
    for (int i = 0; i < 26; ++i) {
        m[s1[i]] = s2[i];
        m[toupper(s1[i])] = toupper(s2[i]);
    }
    for (char c : s)
        if (m.count(c))
            putchar(m[c]);
        else
            putchar(c);
    return 0;
}
