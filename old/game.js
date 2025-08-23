function oneD(a) {
    if (a[0] === a[1] && a[1] === a[2] && a[0] !== '.') {
        return a[0];
    }
    return false;
}

function twoD(a) {
    const lines = a;
    for (let i = 0; i < lines.length; i++) {
        let line = lines[i];
        let l = oneD(line);
        if (l) {
            return {
                "player": l[0],
                "pos": [[0, i], [1, i], [2, i]]
            };
        }
    }

    for (let col = 0; col < lines[0].length; col++) {
        let l = "";
        for (let line of lines) {
            l += line[col];
        }
        l = oneD(l);
        if (l) return {
            "player": l[0],
            "pos": [[col, 0], [col, 1], [col, 2]]
        };
    }

    let l = oneD(lines[0][0] + lines[1][1] + lines[2][2]);
    if (l) return {
        "player": l[0],
        "pos": [[0, 0], [1, 1], [2, 2]]
    };

    l = oneD(lines[0][2] + lines[1][1] + lines[2][0]);
    if (l) return {
        "player": l[0],
        "pos": [[2, 0], [1, 1], [0, 2]]
    };

    return false;
}

function threeD(a) {
    for (let i = 0; i < a.length; i++) {
        let ttt = a[i];
        let t = twoD(ttt);
        if (t) {
            t["pos"][0].push(i);
            t["pos"][1].push(i);
            t["pos"][2].push(i);
            return t
        };

        t = [];
        for (let ttt of a) {
            t.push(ttt[i]);
        }
        t = twoD(t);
        if (t) {
            t["pos"][0].push(0);
            t["pos"][1].push(1);
            t["pos"][2].push(2);
            t["pos"][0][1] = i;
            t["pos"][1][1] = i;
            t["pos"][2][1] = i;
            return t
        };

        t = [];
        for (let ttt of a) {
            let r = "";
            for (let line of ttt) {
                r += line[i];
            }
            t.push(r);
        }
        t = twoD(t);
        if (t) {
            t["pos"][0].push(0);
            t["pos"][1].push();
            t["pos"][2].push(2);
            return t
        };
    }


    let mid = a[1][1][1];
    let t = oneD(a[0][0][0] + mid + a[2][2][2]);
    if (t) return {
        "player": t,
        "pos": [[0, 0, 0], [1, 1, 1], [2, 2, 2]]
    };

    t = oneD(a[0][0][2] + mid + a[2][2][0]);
    if (t) return {
        "player": t,
        "pos": [[0, 0, 2], [1, 1, 1], [2, 2, 0]]
    };

    t = oneD(a[0][2][0] + mid + a[2][0][2]);
    if (t) return {
        "player": t,
        "pos": [[0, 2, 0], [1, 1, 1], [2, 0, 2]]
    };

    t = oneD(a[0][2][2] + mid + a[2][0][0]);
    if (t) return {
        "player": t,
        "pos": [[0, 2, 2], [1, 1, 1], [2, 0, 0]]
    };

    return false;
}

function fourD(a) {
    for (let i = 0; i < a.length; i++) {
        let cube = a[i];
        let t = threeD(cube);
        if (t) {
            t["pos"][0].push(i);
            t["pos"][1].push(i);
            t["pos"][2].push(i);
            return t
        };

        t = threeD([a[0][i], a[1][i], a[2][i]]);
        if (t) {
            t["pos"][0].push(0);
            t["pos"][1].push(1);
            t["pos"][2].push(2); 
            return t
        };
    }

    let mid = a[1][1];
    let t = threeD([a[0][0], mid, a[2][2]]);
    if (t) {
        t["pos"][0].push(0);
        t["pos"][1].push(1);
        t["pos"][2].push(2);
        return t
    };

    t = threeD([a[0][2], mid, a[2][0]]);
    if (t) {
        t["pos"][0].push(2);
        t["pos"][1].push(1);
        t["pos"][2].push(1);
        return t
    };

    return false;
}

function resetGame() {
    document.querySelectorAll("div.game > div").forEach(ttt => {
        ttt.querySelectorAll("div").forEach(block => {
            block.innerHTML = ""
        });
    });
    return [
        [
            ["...", "...", "..."],
            ["...", "...", "..."],
            ["...", "...", "..."]
        ],
        [
            ["...", "...", "..."],
            ["...", "...", "..."],
            ["...", "...", "..."]
        ],
        [
            ["...", "...", "..."],
            ["...", "...", "..."],
            ["...", "...", "..."]
        ]
    ];
}

function bot() {
    return
}

game = resetGame()