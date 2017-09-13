const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    terminal: false
});

var MOD = [40484569, 57985519, 59101579]; // random primes x3 against collisions

function mul(lhs, rhs) {
    return [
        lhs[0] * rhs[0] % MOD[0],
        lhs[1] * rhs[1] % MOD[1],
        lhs[2] * rhs[2] % MOD[2]];
}

function pow(x, p, m) {
    var res = 1;
    while (p) {
        if (p & 1)
            res = res * x % m;
        x = x * x % m;
        p >>= 1;
    }
    return res;
}

function rev(x) {
    return [
        pow(x[0], MOD[0] - 2, MOD[0]),
        pow(x[1], MOD[1] - 2, MOD[1]),
        pow(x[2], MOD[2] - 2, MOD[2])];
}

function eq(lhs, rhs) {
    return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[3];
}

function str(x) {
    return x[0] + ';' + x[1] + ';' + x[2];
}

var g;
var curs;
var used = new Array(1e5 + 100);

function search(start) {
    var q = [start]
    used[start] = true;
    while (q.length) {
        var v = q.pop();
        var ribs = g[v];
        for (var i = 0; i < ribs.length; ++i) {
            var r = ribs[i];
            var to = r[0];
            if (used[to])
                continue;
            used[to] = true;
            curs[to] = mul(curs[v], r[1]);
            q.push(to);
        }
    }
}

var ONE = [1, 1, 1];

var n = null, m = null, im = 0;

rl.on('line', function (data) {
    if (n == null) {
        var x = data.trim().split(' ');
        n = parseInt(x[0]);
        m = parseInt(x[1]);
        g = new Array(n + 1);
        for (var i = 1; i <= n; ++i)
            g[i] = [];
        curs = new Array(n + 1);
    }
    else if (im++ < m) {
        var x = data.trim().split(' ');
        var u = parseInt(x[0]);
        var v = parseInt(x[1]);
        var wu = parseInt(x[2]);
        var wv = parseInt(x[3]);
        var k = mul([wv, wv, wv], rev([wu, wu, wu]));//division in residue field
        g[u].push([v, k]);
        g[v].push([u, rev(k)]);

        if (im == m) {
            for (var i = 1; i <= n; ++i)
                if (!used[i]) {
                    curs[i] = ONE;
                    search(i);
                }

            var c = {};
            var cnt = 0;
            var res = [];
            for (var i = 1; i <= n; ++i) {
                var s = str(curs[i]);
                if (!(s in c))
                    c[s] = cnt++;
                res.push(c[s] + 1);
            }
            console.log(res.join('\n'));
        }
    }
});
