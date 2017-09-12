#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64_t a, b;
    scanf("%" SCNd64 "%" SCNd64, &a, &b);
    printf("%" PRId64, a + b);
    fflush(stdout); // Only for interactive problem B.
    return 0;
}
