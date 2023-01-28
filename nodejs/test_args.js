const io = require('virya_io.js');
const path = require('path')


const args = process.argv;
for(var i=0; i < args.length; i++){
	io.vprint("Arg[%s] %s",[i, args[i]]);
}

io.vprint("NodeHome => %s", [path.dirname(args[0])]);
console.log(`NodeHome => ${path.dirname(args[0])}`)

