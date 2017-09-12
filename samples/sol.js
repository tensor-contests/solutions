const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    terminal: false
});

var a = null, b = null;

rl.on('line', function (data) {
    if (a == null) {
        x = data.trim().split(' ');
        a = parseInt(x[0]);
        b = parseInt(x[1]);
        console.log(a + b);
        process.exit(0); // For interactive problem B.
    }
    else {
        // second and more lines
    }
});
