
const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    terminal: false
});

var a = null, b = null

rl.on('line', function (data) {
    if (a == null)
        a = data;
    else if (b == null) {
        b = data;
        var left = [], right = [];
        var res = '';

        for (var ai = 0, bi = 0; ai < a.length; ++ai)
            if (bi < b.length && a[ai] == b[bi]) {
                left.push(ai);
                ++bi;
            }
            else
                res += a[ai];

        for (var ai = a.length - 1, bi = b.length - 1; ai >= 0; --ai)
            if (bi >= 0 && a[ai] == b[bi]) {
                right.push(ai);
                --bi;
            }
        right.reverse();

        for (var ai = 0, eq = 0, ri = 0; ai < a.length && ri < right.length; ++ai) {
            if (a[ai] != a[eq])
                eq = ai;
            if (ai == right[ri]) {
                right[ri] = eq++;
                if (right[ri] != left[ri]) {
                    console.log('AMBIGUITY');
                    return;
                }
                ++ri;
            }
        }

        console.log(res)
    }
});


