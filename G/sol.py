MAXN = 52
W = [97, 1007]
MOD = [10**9 + 7, 10**9 + 33]

prefix_hash = [[], []] # [2][2][MAXN][MAXN];
WPOW = [] # [2][MAXN][MAXN];

class hash_t:
    def __init__(self):
        self.har = [0, 0]
        self.height = 0
        self.width = 0

    def __eq__(self, rhs):
        if self.har != rhs.har:
            return False

        return self.height == rhs.height  and  self.width == rhs.width

    def __hash__(self):
        return hash(tuple(self.har) + (self.height, self.width))


def getmod(x, mod):
   tmp = x % mod
   return tmp + mod if x < 0 else tmp


def make_wpow():
    for hh in range(len(W)):
        w = W[hh]
        mod = MOD[hh]
        cur = 1
        wp0 = []
        for i in range(MAXN):
            wp1 = []
            for j in range(MAXN):
                wp1.append(cur)
                cur = cur * w % mod
            wp0.append(wp1)
        WPOW.append(wp0)


def make_prefix_hashes(s, height, width, dest_h):
    for hh in range(len(W)):
        dest_h.append([])
        colhash = [0 for i in range(width)]
        mod = MOD[hh]
        for i in range(height):
            dest_h[hh].append([])
            for j in range(width):
                colhash[j] = (colhash[j] + ord(s[i][j]) * WPOW[hh][i][j] % mod)\
                        % mod
                dest_h[hh][i].append((
                        (dest_h[hh][i][-1] if j else 0) + colhash[j]) % mod)


def get_subhash(h, luy, lux, rdy, rdx):
    res = hash_t()
    for hh in range(len(W)):
        mod = MOD[hh]

        pref_all = h[hh][rdy][rdx];
        pref_up = h[hh][luy - 1][rdx] if luy > 0 else 0
        pref_left = h[hh][rdy][lux - 1] if lux > 0 else 0
        pref_up_left = h[hh][luy - 1][lux - 1] if luy > 0 and lux > 0 else 0

        subsq = getmod(getmod(getmod(
                pref_all - pref_up , mod) - pref_left, mod) + pref_up_left, mod)
        moved = subsq * WPOW[hh][MAXN - rdy - 1][MAXN - rdx - 1] % mod

        res.har[hh] = moved

    res.height = rdy - luy + 1
    res.width = rdx - lux + 1
    return res;


def check(height, width, sq_height, sq_width, res):
    used = {}
    for luy in range(height[0] - sq_height, -1, -1):
        for lux in range(width[0] - sq_width, -1, -1):
            rdy = luy + sq_height - 1
            rdx = lux + sq_width - 1
            curhash = get_subhash(prefix_hash[0], luy, lux, rdy, rdx)
            used[curhash] = (luy, lux)

    for luy in range(height[1] - sq_height, -1, -1):
        for lux in range(width[1] - sq_width, -1, -1):
            rdy = luy + sq_height - 1
            rdx = lux + sq_width - 1
            curhash = get_subhash(prefix_hash[1], luy, lux, rdy, rdx)
            if curhash in used:
                res[0] = used[curhash]
                res[1] = (luy, lux)
                return True

    return False


def main():
    s = []
    height, width = [0, 0], [0, 0]

    for iter in range(2):
        height[iter], width[iter] = [int(x) for x in input().strip().split(' ')]
        s.append([])
        for i in range(height[iter]):
            s[iter].append(input().strip())

    make_wpow()

    for i in range(2):
        make_prefix_hashes(s[i], height[i], width[i], prefix_hash[i])

    min_h, min_w = min(height), min(width)

    ans_sq = 0;
    anspt = [None, None]
    ans_hw = (None, None)

    for h in range(min_h, 0, -1):
        bspt = [None, None]
        l, r = 1, min_w
        while l + 1 < r:
            m = (l + r) // 2
            if h * m > ans_sq and check(height, width, h, m, bspt):
                l = m
            else:
                r = m - 1

        if l < r and h * r > ans_sq and check(height, width, h, r, bspt):
            l = r
        if h * l > ans_sq and check(height, width, h, l, bspt):
            ans_sq = h * l
            anspt = bspt
            ans_hw = (h, l)

    if ans_sq:
        print(ans_hw[0], ans_hw[1])
        for pt in anspt:
            print(pt[0] + 1, pt[1] + 1)
    else:
        print(0, 0)

main()
