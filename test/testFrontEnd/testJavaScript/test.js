const communication = require("readline/promises").createInterface({
	input: process.stdin,
	output: process.stdout,
})
const map = Array.from(new Array(15), () => {
	return new Array(15).fill(-1)
})
/**
 * 向评测机发送落子请求
 * @arg {number} gamer 已落子的当前玩家
 * @arg {number} x 落子横坐标
 * @arg {number} y 落子纵坐标
 */
function gamerRequest(gamer, x, y) {
	const content = {}
	Reflect.set(content, String(gamer ^ 1), `${x} ${y}`)
	console.log(JSON.stringify({
		command: "request",
		display: JSON.stringify({
			gamer,
			x,
			y,
		}),
		content,
	}))
}
/**
 * 向评测机发送游戏结束信息
 * @arg {number} gamer 当前玩家
 * @arg {number} x 落子横坐标
 * @arg {number} y 落子纵坐标
 * @arg {string} error 错误信息，若非空则当前玩家判负
 */
function gamerWin(gamer, x, y, error = "") {
	const content = {}
	const winner = gamer ^ Boolean(error)
	Reflect.set(content, String(winner & 1), 1)
	Reflect.set(content, String((winner & 1) ^ 1), 0)
	console.log(JSON.stringify({
		command: "finish",
		display: JSON.stringify({
			gamer,
			x,
			y,
			winner,
			error,
			map,
		}),
		content,
	}))
}
/**
 * 判断几连子，若五连子则结束游戏
 * @arg {number} count 连子数
 * @arg {number} gamer 当前玩家
 * @arg {number} i 判断横坐标
 * @arg {number} j 判断纵坐标
 * @arg {number} x 落子横坐标
 * @arg {number} y 落子纵坐标
 * @return count 的新值，若游戏结束则返回 undefined
 */
function solve(count, gamer, i, j, x, y) {
	if (gamer != map[i][j]) {
		return 0
	}
	if (count < 4) {
		return count + 1
	}
	gamerWin(gamer, x, y)
}
(async () => {
	gamerRequest(1, -1, -1)
	for (let gamer = 0; true; gamer ^= 1) {
		/**
		 * 当前回合玩家的操作
		 * @prop raw 操作内容，即 bot 的输出
		 * @prop verdict 操作结果，若为“OK”则表示操作成功，否则表示操作失败（TLE 之类的）
		 * @type {{verdict: string, raw: string}}
		 */
		const gamerOperation = JSON.parse(await communication.question(""))[String(gamer)]
		if (!gamerOperation || gamerOperation.verdict != "OK" || typeof gamerOperation.raw != "string") {
			gamerWin(gamer, -1, -1, "异常退出")
			break
		}
		let [x, y] = gamerOperation.raw.split(" ").map(s => {
			return parseInt(s)
		})
		if (x < 0 || x > 14 || y < 0 || y > 14 || map[x][y] != -1) {
			gamerWin(gamer, x, y, "落点违规")
			break
		}
		map[x][y] = gamer
		for (let i = 0; i <= 14; i++) {
			let count = 0
			for (let j = 0; j <= 14; j++) {
				count = solve(count, gamer, i, j, x, y)
				if (count == undefined) {
					return
				}
			}
		}
		for (let j = 0; j <= 14; j++) {
			let count = 0
			for (let i = 0; i <= 14; i++) {
				count = solve(count, gamer, i, j, x, y)
				if (count == undefined) {
					return
				}
			}
		}
		for (let k = 4; k <= 14; k++) {
			let count = 0
			for (let j = k; j >= 0; j--) {
				count = solve(count, gamer, k - j, j, x, y)
				if (count == undefined) {
					return
				}
			}
		}
		for (let k = 1; k <= 10; k++) {
			let count = 0
			for (let i = k; i <= 14; i++) {
				count = solve(count, gamer, i, k - i + 14, x, y)
				if (count == undefined) {
					return
				}
			}
		}
		for (let k = 10; k >= 0; k--) {
			let count = 0
			for (let j = k; j <= 14; j++) {
				count = solve(count, gamer, j - k, j, x, y)
				if (count == undefined) {
					return
				}
			}
		}
		for (let k = 1; k <= 10; k++) {
			let count = 0
			for (let i = k; i <= 14; i++) {
				count = solve(count, gamer, i, i - k, x, y)
				if (count == undefined) {
					return
				}
			}
		}
		gamerRequest(gamer, x, y)
	}
})().finally(() => {
	communication.close()
})
