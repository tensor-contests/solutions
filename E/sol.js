
const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    terminal: false
});

var n = null, m = null, a = null, qi = 0;
var q_by_r = {};

function FenwickTree(n) {
    this.t = new Int32Array(n);

    this.sum = function(pos) {
        var res = 0;
        for (var i = pos; i >= 0; i = (i & (i + 1)) - 1)
            res += this.t[i];
        return res;
    };

    this.add = function(pos, x) {
        for (var i = pos; i < this.t.length; i |= i + 1)
            this.t[i] += x;
    };
}

rl.on('line', function (data) {
    if (n === null)
        n = parseInt(data.trim())
    else if (a === null) {
        a = new Array(n)
        x = data.trim().split(' ')
        for (var i = 0; i < n; ++i) {
            a[i] = parseInt(x[i])
            q_by_r[i] = [];
        }
    }
    else if (m === null)
        m = parseInt(data.trim())
    else if (qi < m) {
        var x = data.trim().split(' ')
        var L = parseInt(x[0]);
        var R = parseInt(x[1]);
        q_by_r[R].push({L: L, id: qi++})

        if (qi == m) {
            var t = new FenwickTree(a.length + 1);
            var res = new Array(m);
            var prev_pos = {};
            for (var i = 0; i < n; ++i) {
                var pp = a[i] in prev_pos ? prev_pos[a[i]] : 0;
                t.add(pp, 1);
                t.add(i + 1, -1);
                prev_pos[a[i]] = i + 1;
                var q = q_by_r[i];
                for (var j = 0; j < q.length; ++j)
                    res[q[j].id] = t.sum(q[j].L);
            }

            console.log(res.join("\n"));
        }
    }
});


