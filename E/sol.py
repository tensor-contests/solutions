class FenwickTree:
    def __init__(self, n):
        self.t = [0 for i in range(n)]

    def sum(self, pos):
        res = 0
        while pos >= 0:
            res += self.t[pos]
            pos = (pos & (pos + 1)) - 1
        return res

    def add(self, pos, x):
        while pos < len(self.t):
            self.t[pos] += x
            pos |= pos + 1


n = int(input())
a = [int(x) for x in input().strip().split(' ')]
m = int(input())
q_by_r = {}
for i in range(m):
    L, R = [int(x) for x in input().strip().split(' ')]
    q_by_r.setdefault(R, []).append((L, i))

res = [0 for i in range(m)]
t = FenwickTree(n + 1)
prev_pos = {}
for i in range(n):
    t.add(prev_pos.setdefault(a[i], 0), 1)
    t.add(i + 1, -1)
    prev_pos[a[i]] = i + 1
    for L, i in q_by_r.setdefault(i, []):
        res[i] = t.sum(L)

print('\n'.join(str(x) for x in res))
