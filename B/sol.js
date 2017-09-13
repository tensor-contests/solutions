const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    terminal: false
});

function compare(query, ans)
{
    used = {}
    for (var x = query, i = 0; i < 4; ++i) {
        used[x % 10] = true;
        x = Math.floor(x / 10)
    }

    res = [0, 0];
    for (var i = 0; i < 4; ++i) {
        var mq = query % 10;
        var ma = ans % 10;
        if (mq == ma)
            ++res[0];
        else if (ma in used) {
            ++res[1];
            delete used[ma]
        }
        query = Math.floor(query / 10)
        ans = Math.floor(ans / 10)
    }
    return res;
}

var s = {}
for (var i = 0; i <= 9999; ++i) {
    var d = {}
    var good = true;
    for (var x = i, j = 0; j < 4; ++j) {
        var m = x % 10;
        if (m in d) {
            good = false;
            break;
        }
        d[m] = true
        x = Math.floor(x / 10)
    }
    if (good)
        s[i] = true;
}

var q = 123

function ask() {
    var qs = q + '';
    while (qs.length < 4)
        qs = '0' + qs;
    console.log(qs)
}

ask();

rl.on('line', function (data) {
    inp = data.trim().split(' ');
    if (inp[0] == 4 && inp[1] == 0)
        process.exit(0)

    for (var ans in s) {
        var cmp = compare(q, ans);
        if (cmp[0] != inp[0] || cmp[1] != inp[1])
            delete s[ans]
    }

    var rnd = Math.floor(Math.random() * s.size);
    for (var x in s)
        if (!rnd--) {
            q = x;
            break;
        }
    ask();
});
