var io = require('virya_io.js');
var str = 'hello AND AND NOT there AND NOT how NOT are you';
var x = str.split(/(?:\s*(?:AND\s*)*)NOT\s*/).filter(String);
console.log(x)
var y = str.split(/(?:\s*(?:AND\s*)*)NOT\s*/)
console.log("ARRAY.toString() => ", y.toString())
console.log("ARRAY.join()     => ", y.join("@"))
console.log('ARRAY + " "      => ',  y+"")
