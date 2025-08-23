for (let i = 0; i < 9; i++) {
    let res = `<div id="${i}" class="y">`;
    for (let j = 0; j < 9; j++) res += `<div id="${j}" class="x"></div>`;
    res += "</div>";
    document.querySelector("div.game").innerHTML += res;
}

players = ["X"]
turn = 0

document.querySelectorAll("div.game > div").forEach(ttt => {
    ttt.querySelectorAll("div").forEach(block => {
        block.addEventListener("click", function () {
            if (!block.innerHTML) {
                const x = Math.floor(ttt.id / 3);
                const y = ttt.id % 3;
                const z = Math.floor(block.id / 3);
                const m = block.id % 3;
                game[x][y][z] = game[x][y][z].slice(0, m) + players[turn] + game[x][y][z].slice(m + 1);
                const check = fourD(game);
                block.innerHTML = `<img src="/images/${players[turn]}.svg">`;
                turn += 1;
                turn %= players.length
                if (check) {
                    console.log(check["player"] + " won!")
                    console.log(check)
                    document.querySelectorAll("div.game > div")[Math.floor(check["pos"][0][2] % 3) + 3 * check["pos"][0][3]]
                        .querySelectorAll("div.game > div > div")[Math.floor(check["pos"][0][0] % 3) + 3 * check["pos"][0][1]]
                        .innerHTML = "Hello"
                    document.querySelectorAll("div.game > div")[Math.floor(check["pos"][1][2] % 3) + 3 * check["pos"][1][3]]
                        .querySelectorAll("div.game > div > div")[Math.floor(check["pos"][1][0] % 3) + 3 * check["pos"][1][1]]
                        .innerHTML = "World"
                    document.querySelectorAll("div.game > div")[Math.floor(check["pos"][2][2] % 3) + 3 * check["pos"][2][3]]
                        .querySelectorAll("div.game > div > div")[Math.floor(check["pos"][2][0] % 3) + 3 * check["pos"][2][1]]
                        .innerHTML = "!"
                }
            }
        });
    });
});