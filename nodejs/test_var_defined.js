var io = require('virya_io')
var {HEAD, HORIZONTAL, EXPLAIN, SET_LINEWIDTH} = require('virya_io')
SET_LINEWIDTH(120)

HORIZONTAL()
EXPLAIN("In global area, x,y is defined, while z is not.")
EXPLAIN("In function foo, u is defined by var, v is defined by let and w is set directly.")
HEAD("check whether a variable is defined")
var x;
var y = 10;
function foo() {
	var u = 100;
	let v = 200
	w = 300
}

io.print("Type of x: [%s] ", typeof x);
io.print("Type of y: [%s] ", typeof y);
io.print("Type of z: [%s] ", typeof z);

if(typeof z !== 'undefined'){
	// this statement will not execute
	io.print("Variable z is defined.");
}else{
	io.print("Variable z is undefined.");
}

/* Throws Uncaught ReferenceError: z is not defined,
   and halt the execution of the script */
if(x != null){
	io.print("Variable x is defined.");
}
try{
	if(z != null){ // this statement will not execute
		io.print("Variable z is defined.");
	}
}catch(e){
	io.print("Variable z is not defined; throws when access it(method: z != null)")
}

/* If the following statement runs, it will also
throw the Uncaught ReferenceError: z is not defined */
try {
	if(z){
		io.print("Variable z is true");
	}
}catch(e){
	io.print("Variable z is not defined; throws when access it(method: if z)")
}

foo()
try {
	if(u){
		io.print("Variable u is true");
	}
}catch(e){
	io.print("Variable u is not defined; throw when access it")
}
	if(w){
		io.print("Variable w is true");
	}

HORIZONTAL()
HEAD("! If a var is not defined, typeof return 'undefined', but Object.prototype.toString.call throws.")
HORIZONTAL()
