/**
 *[Ref1 - call mechanism & async await ](https://stackoverflow.com/questions/47158979/node-wait-for-async-function-before-continue)
 *[Ref2 - async wait ](https://blog.risingstack.com/mastering-async-await-in-nodejs/)
 */

function simple_test() {
	function delayF() {         // delay 3 seconds and return a string
		return new Promise(resolve => {
			setTimeout(() => {
				resolve('I am a async result')
			}, 3000)
		})
	}

	async function testAwait() { // the function who will wait
		var start = Date.now()
		console.log("Begin:" + start);
		console.log(await delayF())
		console.log(`cost ${Date.now() - start} ms`)
		var end = Date.now()
		console.log(" End:" + end);
	}
	testAwait()
}

simple_test()
