var print_obj =require('virya_io').print_obj;
var print_obj_prop =require('virya_io').print_obj_prop;
var print_obj_type =require('virya_io').print_obj_type;
var type =require('virya_io').type;
var printf    =require('virya_io').printf;
var print     =require('virya_io').print;
var DRAW_LINE=require('virya_io').DRAW_LINE;
var EXPLAIN=require('virya_io').EXPLAIN;

var {HEAD,HEAD2,REFERENCE,HORIZONTAL}=require('virya_io');

HEAD("Test whether sub-function modify the parameter - primitive")
let a = "String A"
function sub(x) {  x = "String B"; print(" ==>[%s]",x) }
print("initial =>[%s]", a)
sub(a)
print(" after =>[%s]", a)
HEAD2("if the string is const")
const x = "String X"
print("intial =>[%s]", x)
sub(x)
print("intial =>[%s]", x)

HEAD("Test whether sub-function modify the parameter - primitive")
a = {name:"A", value:"String A"}
function sub(x) {  x.value = "String B"; print(" ~~[%s, %s]",x.name, x.value) }
print("initial =>[%s, %s]",a.name, a.value)
sub(a)
print("  after =>[%s, %s]",a.name, a.value)
HEAD2("if the var is const")
const y = {name:"A", value:"String A"}
print("initial =>[%s, %s]",y.name, y.value)
sub(y)
print("  after =>[%s, %s]",y.name, y.value)
HORIZONTAL()

