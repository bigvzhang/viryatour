/*
 * The Promise object represents the eventual completion (or failure) of an asynchronous operation, and its resulting value.
 */

function test_basic(){
	let myFirstPromise = new Promise((resolve, reject) => {
	  // We call resolve(...) when what we were doing asynchronously was successful, and reject(...) when it failed.
	  // In this example, we use setTimeout(...) to simulate async code. 
	  // In reality, you will probably be using something like XHR or an HTML5 API.
	  setTimeout( function() {
		resolve("Success!")  // Yay! Everything went well!
	  }, 3000) 
	}) 

	console.log("Waiting...")
	myFirstPromise.then((successMessage) => {
	  // successMessage is whatever we passed in the resolve(...) function above.
	  // It doesn't have to be a string, but if it is only a succeed message, it probably will be.
	  console.log("Yay! " + successMessage) 
	});
}

async function test_await(){
	function operation() {
		return new Promise(function(resolve, reject) {
			let a = 0;
			let b = 1;
			a = a + b;
			a = 5;

			// may be a heavy db call or http request?
			resolve(a) // successfully fill promise
		})
	}

	async function app() {
		var a = await operation() // a is 5
		console.log("a = " + a);
	}
	
	console.log("before call app()");
	await app()
	console.log("after call app()");
}

test_await()
