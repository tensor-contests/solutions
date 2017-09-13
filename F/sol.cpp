#include <bits/stdc++.h>
using namespace std;

const int MN = 2;
const int MOD[MN] = {1000000009, 1000000033};
const int MAXN = int(1e5 + 100);

int binpow(int64_t a, int p, int m)
{
    int64_t res = 1;
    while (p) {
        if (p & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        p >>= 1;
    }
    return static_cast<int>(res);
}

struct num {
    int d[MN];

    num() = default;

    num(int x)
    {
        for (int i = 0; i < MN; ++i)
            d[i] = x;
    }

    static const num ONE;
    num operator * (const num &rhs) const
    {
        num res;
        for (int i = 0; i < MN; ++i)
            res.d[i] = int64_t(d[i]) * rhs.d[i] % MOD[i];
        return res;
    }

    num rev() const
    {
        num res;
        for (int i = 0; i < MN; ++i)
            res.d[i] = binpow(d[i], MOD[i] - 2, MOD[i]);
        return res;
    }

    bool operator == (const num &rhs) const
    {
        return equal(d, end(d), rhs.d);
    }
};

namespace std {

template<>
struct hash<num> {
    size_t operator()(const num &x) const
    {
        return accumulate(x.d, end(x.d), 0);
    }
};

} // namespace std

const num num::ONE(1);

vector<pair<int, num>> g[MAXN];
num curs[MAXN];
bool used[MAXN];

void bfs(int start)
{
    static deque<int> q;
    q.clear();
    q.push_back(start);
    used[start] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (const pair<int, num> &r : g[v]) {
            int to = r.first;
            if (used[to])
                continue;
            used[to] = true;
            curs[to] = curs[v] * r.second;
            q.push_back(to);
        }
    }
}

int main()
{
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int u, v, wu, wv;
        scanf("%d%d%d%d", &u, &v, &wu, &wv);
        num k = num(wv) * num(wu).rev();
        g[u].push_back(make_pair(v, k));
        g[v].push_back(make_pair(u, k.rev()));
    }

    for (int i = 1; i <= n; ++i)
        if (!used[i]) {
            curs[i] = num::ONE;
            bfs(i);
        }

    unordered_map<num, int> c;
    for (int i = 1; i <= n; ++i) {
        auto it = c.find(curs[i]);
        if (it == c.end())
            it = c.insert(make_pair(curs[i], c.size())).first;
        printf("%d\n", it->second + 1);
    }
    return 0;
}
