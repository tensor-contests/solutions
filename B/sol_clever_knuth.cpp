#include <bits/stdc++.h>
using namespace std;

pair<int, int> compare(int query, int ans)
{
    static bool used[10];
    memset(used, 0, sizeof(used));
    for (int x = query, i = 0; i < 4; ++i) {
        div_t dx = div(x, 10);
        used[dx.rem] = true;
        x = dx.quot;
    }
    pair<int, int> res;
    for (int i = 0; i < 4; ++i) {
        div_t dq = div(query, 10);
        div_t da = div(ans, 10);
        if (dq.rem == da.rem)
            ++res.first;
        else if (used[da.rem]) {
            ++res.second;
            used[da.rem] = false;
        }
        query = dq.quot;
        ans = da.quot;
    }
    return res;
}

void print(int x)
{
    printf("%.4d\n", x);
    fflush(stdout);
}

int main()
{
    unordered_set<int> s;
    for (int i = 0; i <= 9999; ++i) {
        static int d[4];
        for (int x = i, j = 0; j < 4; x /= 10, ++j)
            d[j] = x % 10;
        sort(d, end(d));
        if (adjacent_find(d, end(d)) == end(d))
            s.insert(i);
    }
    vector<char> used(10000, false);

    int q = 123;
    print(q);
    used[q] = true;

    for (;;) {
        pair<int, int> bc;
        scanf("%d%d", &bc.first, &bc.second);
        if (bc.first == 4 && bc.second == 0)
            return 0;
        for (auto it = s.begin(); it != s.end();) {
            pair<int, int> cmp = compare(q, *it);
            if (cmp != bc)
                s.erase(it++);
            else
                ++it;
        }

        int max_min_delcnt = -1, arg_maxmin = 0;
        bool arg_in_s = false;
        for (int qi = 0; qi <= 9999; ++qi)
            if (!used[qi]) {
                static int cnt[64];
                memset(cnt, 0, sizeof(cnt));
                for (int ans : s) {
                    pair<int, int> bc = compare(qi, ans);
                    ++cnt[(bc.first << 3) | bc.second];
                }
                int max_cnt = *max_element(cnt, end(cnt));
                int min_del_cnt = s.size() - max_cnt;
                bool in_s = s.count(qi);
                if (min_del_cnt > max_min_delcnt ||
                    (min_del_cnt == max_min_delcnt && !arg_in_s && in_s)) {
                    max_min_delcnt = min_del_cnt;
                    arg_maxmin = qi;
                    arg_in_s = in_s;
                }
            }

        q = arg_maxmin;
        print(arg_maxmin);
        used[arg_maxmin] = true;
    }

    return 0;
}
