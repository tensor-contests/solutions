MOD = [1000000009, 1000000033]

class num:
    def __init__(self, x = 0):
        self.d = (x, x)

    def __mul__(self, rhs):
        res = num()
        res.d = (self.d[0] * rhs.d[0] % MOD[0],
                 self.d[1] * rhs.d[1] % MOD[1])
        return res;

    def rev(self):
        res = num()
        res.d = (pow(self.d[0], MOD[0] - 2, MOD[0]),
                 pow(self.d[1], MOD[1] - 2, MOD[1]))
        return res

    def __eq__(self, rhs):
        return self.d == rhs.d

    def __hash__(self):
        return hash(self.d)

ONE = num(1)
g = [[] for x in range(10**5 + 100)]
curs = [None for x in range(10**5 + 100)]
used = [False for x in range(10**5 + 100)]


def search(start):
    q = [start]
    used[start] = True
    while q:
        v = q.pop()
        for r in g[v]:
            to = r[0]
            if used[to]:
                continue
            used[to] = True
            curs[to] = curs[v] * r[1]
            q.append(to)


def main():
    n, m = [int(x) for x in input().strip().split(' ')]
    for i in range(1, m + 1):
        u, v, wu, wv = [int(x) for x in input().strip().split(' ')]
        k = num(wv) * num(wu).rev()
        g[u].append((v, k))
        g[v].append((u, k.rev()))

    for i in range(1, n + 1):
        if not used[i]:
            curs[i] = ONE
            search(i)

    c = {}
    res = []
    for i in range(1, n + 1):
        res.append(str(c.setdefault(curs[i], len(c)) + 1))
    print('\n'.join(res))

if __name__ == '__main__':
    main()
