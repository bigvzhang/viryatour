var io = require('virya_io.js');

function pathnameOfUrl(url) { // similar to dirname of C
	let rtn =  /^.*\//.exec(url)
	if(rtn != null)
		return rtn[0]
	else
		return ""
}

function test(url){
	io.print("url:%-20s pathname:%s", url, pathnameOfUrl(url))
}

test('abc/efg/hij')
test('abc')
test('/hij')
test('///hij')
