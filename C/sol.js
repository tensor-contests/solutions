
const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    terminal: false
});

var m = null, n = null
img = [Array(1010).join('.')]
var r = 1

function clear_shape(pos0)
{
    img[pos0[0]][pos0[1]] = '.'
    var q = [pos0]
    while (q.length > 0) {
        var p = q.pop()
        for (var di = -1; di <= 1; ++di)
            for (var dj = -1; dj <= 1; ++dj)
                if (di || dj) {
                    var toi = p[0] + di;
                    var toj = p[1] + dj;
                    if (img[toi][toj] == '*') {
                        img[toi][toj] = '.';
                        q.push([toi, toj])
                    }
                }
    }
}


rl.on('line', function (data) {
    if (m === null) {
        var x = data.split(' ')
        m = parseInt(x[0])
        n = parseInt(x[1])
        return;
    }
    img[r++] = ('.' + data + '.').split('')
    if (r == m) {
        img.push(img[0]);
        var cnt = 0;

        for (var i = 1; i <= m; ++i)
            for (var j = 1; j <= n; ++j)
                if (img[i][j] == '*') {
                    clear_shape([i, j])
                    ++cnt;
                }

        console.log(cnt % 2 ? 'crosses' : 'zeros')
    }
});

