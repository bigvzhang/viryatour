var printf = require('./vya_io').printf;
var x;
var y = 10;


printf("Type of x: [%s] ", [typeof x]);
printf("Type of y: [%s] ", [typeof y]);
printf("Type of z: [%s] ", [typeof z]);

if(typeof z !== 'undefined'){
	// this statement will not execute
	printf("Variable z is defined.");
}else{
	printf("Variable z is undefined.");
}

/* Throws Uncaught ReferenceError: z is not defined,
   and halt the execution of the script */
if(x != null){
	printf("Variable z is defined.");
}
if(z != null){
	// this statement will not execute
	printf("Variable z is defined.");
}

/* If the following statement runs, it will also
throw the Uncaught ReferenceError: z is not defined */
if(z){
	// this statement will not execute
	printf("Variable z is true");
}
