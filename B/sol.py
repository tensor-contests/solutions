import random

def compare(q, ans):
    bulls, cows = 0, 0
    used = set(c for c in q)
    for i in range(4):
        if q[i] == ans[i]:
            bulls += 1
        elif ans[i] in used:
            cows += 1
    return bulls, cows

ans = ['%.4d' % (i,) for i in range(10000) if len(set(c for c in '%.4d' % (i,))) == 4]

q = random.choice(ans)
print(q)
while True:
    resp = tuple(int(x) for x in input().strip().split(' '))
    if resp == (4, 0):
        exit(0)
    ans = [x for x in ans if compare(q, x) == resp]
    q = random.choice(ans)
    print(q)
