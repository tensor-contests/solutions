#include <bits/stdc++.h>
using namespace std;

pair<int, int> compare(string const &query, string const & ans)
{
    static bool used[10];
    memset(used, 0, sizeof(used));
    for (char c : query)
       used[c - '0'] = true;

    pair<int, int> res;
    for (int i = 0; i < 4; ++i)
        if (query[i] == ans[i])
            ++res.first;
        else if (used[ans[i] - '0']) {
            ++res.second;
            used[ans[i] - '0'] = false;
        }
    return res;
}

void print(string const &q)
{
    puts(q.c_str());
    fflush(stdout);
}

int main()
{
    vector<string> s;
    for (int i = 0; i <= 9999; ++i) {
        static char d[4], buf[5] = {};
        for (int x = i, j = 3; j >= 0; x /= 10, --j)
            buf[j] = d[j] = x % 10 + '0';
        sort(d, end(d));
        if (adjacent_find(d, end(d)) == end(d))
            s.push_back(buf);
    }

    string q = "0123";
    print(q);
    for (;;) {
        pair<int, int> bc;
        scanf("%d%d", &bc.first, &bc.second);
        if (bc.first == 4 && bc.second == 0)
            return 0;
        s.erase(remove_if(s.begin(), s.end(), [q, bc](string const &ans) {
                 return compare(q, ans) != bc; }), s.end());

        q = s[rand() % s.size()];
        print(q);
    }

    return 0;
}
