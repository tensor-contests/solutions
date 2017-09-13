#include <bits/stdc++.h>
using namespace std;

char img[1010][1010];

void clear_shape_bfs(int i0, int j0)
{
    deque<pair<int, int>> q {{i0, j0}};
    img[i0][j0] = ' ';
    while (!q.empty()) {
        pair<int, int> pt = q.front();
        q.pop_front();
        for (int di = -1; di <= 1; ++di)
            for (int dj = -1; dj <= 1; ++dj)
                if (di || dj) {
                    int toi = pt.first + di, toj = pt.second + dj;
                    if (img[toi][toj] == '*') {
                        q.emplace_back(toi, toj);
                        img[toi][toj] = ' ';
                    }
                }
    }
}

int main()
{
    int m, n;
    scanf("%d%d\n", &m, &n);
    for (int i = 1; i <= m; ++i)
        fgets(&img[i][1], sizeof(img[i]) - 1, stdin);

    int cnt_shapes = 0;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (img[i][j] == '*') {
                ++cnt_shapes;
                clear_shape_bfs(i, j);
            }

    if (cnt_shapes % 2)
        puts("crosses");
    else
        puts("zeros");
    return 0;
}
