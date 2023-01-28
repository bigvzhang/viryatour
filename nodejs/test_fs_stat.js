const fs = require('fs')
const vio = require('./vya_io')

let dir1='/tmp/testdir01' // existing
let dir2='/tmp/testdir02' // not existing
let dir3='/tmp/testdir03' // exsiting but it's not a directory


function test(param_dir){
	try{
		let stat = fs.lstatSync(param_dir)
		vio.print_obj(stat)
	}catch(err){
		vio.print_obj(err)
	}
}

// The following is to init the 
try{
	fs.mkdirSync(dir1)
}catch(err){}
try{
	fs.openSync('file.txt', 'w')
}catch(err){console.log(err)}


test(dir1)
test(dir3)
test(dir2)


