#include <bits/stdc++.h>
using namespace std;

int const MAXN = 52;
int const HN = 2;
int64_t const W[HN] = {97, 1007};
int64_t const MOD[HN] = {int64_t(1e9 + 7.5), int64_t(1e9 + 33.5)};

int64_t prefix_hash[2][HN][MAXN][MAXN];
int64_t WPOW[HN][MAXN][MAXN];

struct hash_t {
    int har[HN];
    int height;
    int width;

    bool operator == (hash_t const &rhs) const
    {
        for (int i = 0; i < HN; ++i)
            if (har[i] != rhs.har[i])
                return false;

        if (height != rhs.height || width != rhs.width)
            return false;

        return true;
    }
};

inline int64_t getmod(int64_t x, int64_t mod)
{
   int64_t tmp = x % mod;
   return x < 0 ? tmp + mod : tmp;
}

void make_wpow()
{
    for (int hh = 0; hh < HN; ++hh) {
        int64_t w = W[hh];
        int64_t mod = MOD[hh];

        int64_t cur = 1;
        for (int i = 0; i < MAXN; ++i)
            for (int j = 0; j < MAXN; ++j) {
                WPOW[hh][i][j] = cur;
                cur = getmod(cur * w, mod);
            }
    }
}

int64_t colhash[HN][MAXN];
void make_prefix_hashes(vector<string> const &s, int height, int width,
        int64_t (&dest_h)[HN][MAXN][MAXN])
{
    memset(colhash, 0, sizeof(colhash));
    for (int hh = 0; hh < HN; ++hh) {
        int64_t mod = MOD[hh];
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j) {
                colhash[hh][j] = getmod(
                        colhash[hh][j] + getmod((s[i][j]) * WPOW[hh][i][j],
                        mod), mod);
                dest_h[hh][i][j] = getmod(
                        (j > 0 ? dest_h[hh][i][j - 1] : 0) + colhash[hh][j],
                        mod);
            }
    }
}

hash_t get_subhash(int64_t const (&h)[HN][MAXN][MAXN],
        int luy, int lux, int rdy, int rdx)
{
    hash_t res;
    for (int hh = 0; hh < HN; ++hh) {
        int64_t mod = MOD[hh];

        int64_t pref_all = h[hh][rdy][rdx];
        int64_t pref_up = luy > 0 ? h[hh][luy - 1][rdx] : 0;
        int64_t pref_left = lux > 0 ? h[hh][rdy][lux - 1] : 0;
        int64_t pref_up_left = luy > 0 && lux > 0 ? h[hh][luy - 1][lux - 1] : 0;

        int64_t subsq = getmod(getmod(getmod(
                pref_all - pref_up , mod) - pref_left, mod) + pref_up_left,
                mod);
        int64_t moved = getmod(
                subsq * WPOW[hh][MAXN - rdy - 1][MAXN - rdx - 1], mod);

        res.har[hh] = moved;
    }

    res.height = rdy - luy + 1;
    res.width = rdx - lux + 1;
    return res;
}

struct point {
    int y, x;
    point(int y = 0, int x = 0) : y(y), x(x) {}
};

template<typename T>
void hash_combine(size_t &seed, T const &v)
{
    seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
    template<>
    struct hash<hash_t> {
        size_t operator()(hash_t const &x) const
        {
            size_t seed = 0;
            for (int hh = 0; hh < HN; ++hh)
                hash_combine(seed, x.har[hh]);

            hash_combine(seed, x.height);
            hash_combine(seed, x.width);
            return seed;
        }
    };
}

bool check(int const (&height)[2], int const (&width)[2],
        int sq_height, int sq_width, point (&res)[2])
{
    static unordered_map<hash_t, point> used;
    used.clear();
    for (int luy = height[0] - sq_height; luy >= 0; --luy)
        for (int lux = width[0] - sq_width; lux >= 0; --lux) {
            int rdy = luy + sq_height - 1;
            int rdx = lux + sq_width - 1;
            hash_t curhash = get_subhash(prefix_hash[0], luy, lux, rdy, rdx);
            used[curhash] = point(luy, lux);
        }

    for (int luy = height[1] - sq_height; luy >= 0; --luy)
        for (int lux = width[1] - sq_width; lux >= 0; --lux) {
            int rdy = luy + sq_height - 1;
            int rdx = lux + sq_width - 1;
            hash_t curhash = get_subhash(prefix_hash[1], luy, lux, rdy, rdx);
            auto it = used.find(curhash);
            if (it != used.end()) {
                res[0] = it->second;
                res[1] = point(luy, lux);
                return true;
            }
        }

    return false;
}

int main()
{
    freopen("input.txt", "rt", stdin );
    freopen("output.txt", "wt", stdout );


    vector<string> s[2];
    int height[2];
    int width[2];

    for (int iter = 0; iter < 2; ++iter) {
        cin >> height[iter] >> width[iter];
        s[iter].resize(height[iter]);
        for (int i = 0; i < height[iter]; ++i)
            cin >> s[iter][i];
    }

    make_wpow();

    for (int i = 0; i < 2; ++i)
        make_prefix_hashes(s[i], height[i], width[i], prefix_hash[i]);

    int min_h = *min_element(height, end(height));
    int min_w = *min_element(width, end(width));

    int ans_sq = 0;
    point anspt[2];
    pair<int, int> ans_hw;

    for (int h = min_h; h >= 1; --h) {
        point bspt[2];
        int l = 1, r = min_w;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (h * m > ans_sq && check(height, width, h, m, bspt))
                l = m;
            else
                r = m - 1;
        }

        if (l < r && h * r > ans_sq && check(height, width, h, r, bspt))
            l = r;
        if (h * l > ans_sq && check(height, width, h, l, bspt)) {
            ans_sq = h * l;
            memcpy(anspt, bspt, sizeof(bspt));
            ans_hw = make_pair(h, l);
        }
    }

    if (ans_sq) {
        cout << ans_hw.first << " " << ans_hw.second << endl;
        for (int i = 0; i < 2; ++i)
            cout << (anspt[i].y + 1) << " " << (anspt[i].x + 1) << endl;
    }
    else
        cout << 0 << " " << 0 << endl;

    return 0;
}
