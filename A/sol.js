const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    terminal: false
});

var layout1 = null, layout2 = null, s = null;

rl.on('line', function (data) {
    if (layout1 === null)
        layout1 = data;
    else if (layout2 === null)
        layout2 = data;
    else if (s === null) {
        m = {}
        for (var i = 0; i < 26; ++i) {
            m[layout1[i]] = layout2[i];
            m[layout1[i].toUpperCase()] = layout2[i].toUpperCase();
        }

        s = data
        res = ''
        for (var i = 0; i < s.length; ++i)
            if (s[i] in m)
                res += m[s[i]];
            else
                res += s[i]

        console.log(res)
    }
});
