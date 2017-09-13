const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    terminal: false
});

var MAXN = 52;
var W = [97, 1007];
MOD = [40484569, 57985519];

var prefix_hash = [[], []]; // [2][2][MAXN][MAXN];
var WPOW = []; // [2][MAXN][MAXN];

function hash_t() {
    this.har = [0, 0];
    this.height = 0;
    this.width = 0;
}

hash_t.prototype.str = function() {
    return this.har[0] + ';' + this.har[1] + ';' +
        this.height + ';' + this.width;
}


function getmod(x, mod) {
    tmp = x % mod;
    return x < 0 ? tmp + mod : tmp;
}


function make_wpow() {
    for (var hh = 0; hh < W.length; ++hh) {
        var w = W[hh];
        var mod = MOD[hh];
        var cur = 1;
        var wp0 = [];
        for (var i = 0; i < MAXN; ++i) {
            var wp1 = [];
            for (var j = 0; j < MAXN; ++j) {
                wp1.push(cur);
                cur = cur * w % mod;
            }
            wp0.push(wp1);
        }
        WPOW.push(wp0);
    }
}


function make_prefix_hashes(s, height, width, dest_h) {
    for (var hh = 0; hh < W.length; ++hh) {
        dest_h.push([]);
        var colhash = new Array(width);
        for (var i = 0; i < width; ++i)
            colhash[i] = 0;
        var mod = MOD[hh];
        for (var i = 0; i < height; ++i) {
            dest_h[hh].push([]);
            for (var j = 0; j < width; ++j) {
                colhash[j] = (colhash[j] + s[i].charCodeAt(j) * WPOW[hh][i][j] % mod) % mod;
                dest_h[hh][i].push(((j ? dest_h[hh][i][j - 1] : 0) + colhash[j]) % mod);
            }
        }
    }
}


function get_subhash(h, luy, lux, rdy, rdx) {
    var res = new hash_t();
    for (var hh = 0; hh < W.length; ++hh) {
        var mod = MOD[hh];

        var pref_all = h[hh][rdy][rdx];
        var pref_up = luy > 0 ? h[hh][luy - 1][rdx] : 0;
        var pref_left = lux > 0 ? h[hh][rdy][lux - 1] : 0;
        var pref_up_left = luy > 0 && lux > 0 ? h[hh][luy - 1][lux - 1] : 0;

        var subsq = getmod(getmod(getmod(
                pref_all - pref_up , mod) - pref_left, mod) + pref_up_left, mod);
        var moved = subsq * WPOW[hh][MAXN - rdy - 1][MAXN - rdx - 1] % mod;

        res.har[hh] = moved;
    }

    res.height = rdy - luy + 1;
    res.width = rdx - lux + 1;
    return res;
}


function check(height, width, sq_height, sq_width, res) {
    var used = {};
    for (var luy = height[0] - sq_height; luy >= 0; --luy)
        for (var lux = width[0] - sq_width; lux >= 0; --lux) {
            var rdy = luy + sq_height - 1;
            var rdx = lux + sq_width - 1;
            var curhash = get_subhash(prefix_hash[0], luy, lux, rdy, rdx);
            used[curhash.str()] = [luy, lux];
        }

    for (var luy = height[1] - sq_height; luy >= 0; --luy)
        for (var lux = width[1] - sq_width; lux >= 0; --lux) {
            var rdy = luy + sq_height - 1;
            var rdx = lux + sq_width - 1;
            var curhash = get_subhash(prefix_hash[1], luy, lux, rdy, rdx);
            var chs = curhash.str();
            if (chs in used) {
                res[0] = used[chs];
                res[1] = [luy, lux];
                return true;
            }
        }

    return false;
}


var s = [];
var height = [], width = [];


function solve() {
    make_wpow();

    for (var i = 0; i < 2; ++i)
        make_prefix_hashes(s[i], height[i], width[i], prefix_hash[i]);

    var min_h = Math.min(height[0], height[1]);
    var min_w = Math.min(width[0], width[1]);

    var ans_sq = 0;
    var anspt = [null, null];
    var ans_hw = [null, null];

    for (var h = min_h; h >= 1; --h) {
        var bspt = [null, null];
        var l = 1, r = min_w;
        while (l + 1 < r) {
            var m = (l + r) >> 1;
            if (h * m > ans_sq && check(height, width, h, m, bspt))
                l = m;
            else
                r = m - 1;
        }

        if (l < r && h * r > ans_sq && check(height, width, h, r, bspt))
            l = r;
        if (h * l > ans_sq && check(height, width, h, l, bspt)) {
            var ans_sq = h * l;
            var anspt = bspt;
            var ans_hw = [h, l];
        }
    }

    if (ans_sq) {
        console.log(ans_hw[0], ans_hw[1]);
        console.log(anspt[0][0] + 1, anspt[0][1] + 1);
        console.log(anspt[1][0] + 1, anspt[1][1] + 1);
    }
    else
        console.log(0, 0);
}

var iter = 0, ln;
rl.on('line', function (data) {
    if (iter < 2) {
        if (height.length == iter) {
            var x = data.trim().split(' ')
            height.push(parseInt(x[0]));
            width.push(parseInt(x[1]));
            s.push([]);
            ln = 0;
            return;
        }
        s[iter].push(data.trim());
        ++ln;
        if (ln == height[iter])
            ++iter;
        if (iter == 2)
            solve();
    }
});

