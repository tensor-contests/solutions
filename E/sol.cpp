#include <bits/stdc++.h>
using namespace std;

struct query {
    int id, l, r;
};

int a[1000000], n, m;
query q[1000000];
int t[1000001], result[1000000];

void fenwick_tree_add(int x, int val)
{
    for (; x <= n; x |= x + 1)
        t[x] += val;
}

int fenwick_tree_prefix_sum(int x)
{
    int res = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1)
        res += t[x];
    return res;
}

void solve()
{
    sort(q, q + m, [](query const &x, query const &y) { return x.r < y.r; });
    unordered_map<int, int> prev_pos;
    for (size_t i = 0, q_ptr = 0; i < n; ++i) {
        int &pp = prev_pos[a[i]];
        fenwick_tree_add(pp, 1);
        fenwick_tree_add(pp = i + 1, -1);
        for (; q_ptr < m && q[q_ptr].r == i; ++q_ptr)
            result[q[q_ptr].id] = fenwick_tree_prefix_sum(q[q_ptr].l);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        q[i].id = i;
        scanf("%d%d", &q[i].l, &q[i].r);
    }

    solve();

    for (int i = 0; i < m; ++i)
        printf("%d\n", result[i]);
    return 0;
}
