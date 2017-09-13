a = input()
b = input()
left, right = [], []
res = ''

ai, bi = 0, 0
while ai < len(a):
    if bi < len(b) and a[ai] == b[bi]:
        left.append(ai)
        bi += 1
    else:
        res += a[ai]
    ai += 1

ai, bi = len(a) - 1, len(b) - 1
while ai >= 0:
    if bi >= 0 and a[ai] == b[bi]:
        right.append(ai)
        bi -= 1
    ai -= 1
right.reverse()

ai, ri, eq = 0, 0, 0
while ai < len(a) and ri < len(right):
    if a[ai] != a[eq]:
        eq = ai
    if ai == right[ri]:
        right[ri] = eq
        ri += 1
        eq += 1
    ai += 1

print(res if left == right else 'AMBIGUITY')
