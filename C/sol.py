img = [['.' for i in range(1010)]]

def clear_shape(pos0):
    q = [pos0]
    img[pos0[0]][pos0[1]] = '.'
    while q:
        i, j = q.pop()
        for di in range(-1, 2):
            for dj in range(-1, 2):
                if di or dj:
                    toi, toj = i + di, j + dj
                    if img[toi][toj] == '*':
                        q.append((toi, toj))
                        img[toi][toj] = '.'

m, n = (int(x) for x in input().strip().split(' '))
for i in range(m):
    img.append(['.'] + [c for c in input()] + ['.'])
img.append(img[0])

cnt = 0
for i in range(1, m + 1):
    for j in range(1, n + 1):
        if img[i][j] == '*':
            cnt += 1
            clear_shape((i, j))

print('crosses' if cnt % 2 else 'zeros')
