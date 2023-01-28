var DOC =
`#The process.env object forces all of its properties to be of type string, 
     since environment variables must always be strings.
  - we cannot use for(var i = 0) to read them but can use for(var e in process.env)
#The process.env will be different in NodeJS than in the client(WEB browser) as:
  - the number is different, the number in NodeJS is bigger than WEB browser


[Reference](https://www.cnblogs.com/zdz8207/p/nodejs-process-env.html)
`


const printf          = require('virya_io').printf;
const print           = require('virya_io').print;
const print_obj_prop  = require('virya_io').print_obj_prop;
const EXPLAIN         = require('virya_io').EXPLAIN;
const DRAW_LINE       = function(c,l=80){require('virya_io').DRAW_LINE(c,l)};


DRAW_LINE();
for (let e in process.env) {
	print("%-30s %s",e, process.env[e]);
}
DRAW_LINE();
EXPLAIN("The followings are properties of process object");
print_obj_prop(process);
DRAW_LINE();
printf(DOC)
DRAW_LINE('*');

