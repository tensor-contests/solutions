#include <bits/stdc++.h>
using namespace std;

vector<int> t[270000];

void tree_push(int v, int tl, int tr, int l, int r, int pos)
{
    if (l > r)
        return;

    if (l == tl && r == tr) {
        t[v].push_back(pos);
        return;
    }
    int tm = (tl + tr) >> 1;
    tree_push(v << 1, tl, tm, l, min(r, tm), pos);
    tree_push((v << 1) + 1, tm + 1, tr, max(l, tm + 1), r, pos);
}

int tree_sum(int v, int tl, int tr, int pos, int r)
{
    int res = upper_bound(t[v].begin(), t[v].end(), r) - t[v].begin();
    if (tl < tr) {
        int tm = (tl + tr) >> 1;
        if (pos <= tm)
            res += tree_sum(v << 1, tl, tm, pos, r);
        else
            res += tree_sum((v << 1) + 1, tm + 1, tr, pos, r);
    }
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    unordered_map<int, int> prev_pos;
    for (int i = 0; i < n; ++i) {
        int a;
        scanf("%d", &a);
        int &pp = prev_pos[a];
        tree_push(1, 0, n - 1, pp, i, i);
        pp = i + 1;
    }

    int m;
    scanf("%d", &m);
    while (m--) {
        int L, R;
        scanf("%d%d", &L, &R);
        int res = tree_sum(1, 0, n - 1, L, R);
        printf("%d\n", res);
    }
    return 0;
}
