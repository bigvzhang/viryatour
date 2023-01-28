var print_obj =require('virya_io').print_obj;
var print_obj_prop =require('virya_io').print_obj_prop;
var print_obj_type =require('virya_io').print_obj_type;
var type =require('virya_io').type;
var printf    =require('virya_io').printf;
var print     =require('virya_io').print;
var DRAW_LINE=require('virya_io').DRAW_LINE;
var EXPLAIN=require('virya_io').EXPLAIN;

var {HEAD,HEAD2,REFERENCE,HORIZONTAL}=require('virya_io');

HORIZONTAL() /////////////////////////////////////////////////////
HEAD("Arrays cannot use strings as element indexes? But seems ok(forEach doesn't work)!"); 
HORIZONTAL()
HEAD2("Array a's index is string")
var a = new Array();
a['First']  = 'A 1';
a['Second'] = 'A 2';
a['Third']  = 'A 3';
print("Type of a: %s <= seems good!", type(a))
print("Array Length:%s", a.length);
for (var x in a){
	print("%8s => %s", x, a[x]);
}
EXPLAIN("using Array.forEach <- bad")
a.forEach(element => console.log(element))
EXPLAIN("A's properties!")
print_obj_prop(a)

HEAD2("Array b's index is integer") /////////////////////////////////////////////////////
var b = new Array();
b[0] = 'B 1';
b[1] = 'B 2';
b[2] = 'B 3';
b[3] = 'B 4';
b[4] = 'B 5';
b[5] = 'B 6';
print("Type of b: %s <= good!", type(b))
print("Array Length:%s", b.length);
for (var x in b){
	print("%8s => %s", x, b[x]);
}
EXPLAIN("using Array.forEach <- good")
b.forEach(element => console.log(element))
EXPLAIN("B's properties!")
print_obj_prop(b)

HEAD("randomize(shuffle) a JavaScript array")  /////////////////////////////////////////////////////
REFERENCE("https://stackoverflow.com/questions/2450954")
REFERENCE("https://stackoverflow.com/questions/521295")
HEAD2("using Math.random")
print("%s",[1,2,3,4,5,6,7,8,9,0].sort( () => .5 - Math.random() ))
print("%s",[1,2,3,4,5,6,7,8,9,0].sort( () => .5 - Math.random() ))
HEAD2("using random with seed")
var seed = 1;
function random() {
    return Math.sin(seed++);
}
print("%s",[1,2,3,4,5,6,7,8,9,0].sort( () => .5 - random() ))
seed=1
print("%s",[1,2,3,4,5,6,7,8,9,0].sort( () => .5 - random() ))


HEAD("splice");  /////////////////////////////////////////////////////
function printB(title){
	print(title)
	for (var x in b){
		print("%8s => %s", x, b[x]);
	}
}
/*original*/           printB("Original:")
b.splice(2,1);         printB("After splice(2,1)         ~ delete  No. 2")
b.splice(2,1, 0);      printB("After splice(2,1,0)       ~ replace No. 2")
b.splice(2,0, 999);    printB("After splice(2,0,999)     ~ insert  No. 2")
b.splice(2,1,100,200); printB("After splice(2,1,100,200) ~ replace No. 2 and insert No.3")

HEAD("append");  /////////////////////////////////////////////////////
b.push('8888');        printB("After b.push('8888'):")


HORIZONTAL();
