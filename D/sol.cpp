#include <bits/stdc++.h>
using namespace std;

int main()
{
    string a, b;
    cin >> a >> b;
    int alen = a.size(), blen = b.size();

    deque<int> vleft, vright;
    string res;

    // search subsequence from left to right
    for (int ia = 0, ib = 0; ia < alen; ++ia)
        if (ib < blen && a[ia] == b[ib]) {
            vleft.push_back(ia);
            ++ib;
        }
        else
            res.push_back(a[ia]);

    // search subsequence from right to left
    // and shift founded positions to left within segment of equal characters
    for (int ia = alen - 1, ib = blen - 1; ib >= 0 && ia >= 0; --ia)
        if (a[ia] == b[ib]) {
            vright.push_front(ia);
            --ib;
        }

    for (int ia = 0, ivr = 0, eq = 0; ia < alen && ivr < vright.size(); ++ia) {
        if (a[ia] != a[eq])
            eq = ia;
        if (vright[ivr] == ia)
            vright[ivr++] = eq++;
    }

    if (vleft == vright)
        cout << res;
    else
        cout << "AMBIGUITY";
    return 0;
}
