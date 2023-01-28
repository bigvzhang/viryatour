var sprintf = require('virya_io').sprintf
var vsprintf = require('virya_io').vsprintf
var DRAW_LINE=require('virya_io').DRAW_LINE;
var EXPLAIN=require('virya_io').EXPLAIN;
var print_obj =require('virya_io').print_obj;
var print_obj_prop =require('virya_io').print_obj_prop;
var vprint     =require('virya_io').vprint;
var printf    =require('virya_io').printf;

a=sprintf('%2$s %3$s a %1$s', 'cracker', 'Polly', 'wants')
b=vsprintf('The first 4 letters of the english alphabet are: %s, %s, %s and %s', ['a', 'b', 'c', 'd'])
console.log(a);
console.log(b);


DRAW_LINE();
var room = {
	no : 1,
	address : "China"
};
var cat = {
	name     : "Catty",
	age      : 5,
	salary   : 1000.0,
	merriage : true,
    whoami   : function(){return "I'm " +this.name + ", " + this.age +"year(s) old!"},
	address  : room
};
EXPLAIN('vprint object');
print_obj(cat);
EXPLAIN("vprint object type of properties");
print_obj_prop(cat);
printf(cat.whoami());
EXPLAIN("vprint one array!");
print_obj([1, 2, 3, "4"]);
EXPLAIN("vprint one string");
print_obj("Good Morning");
DRAW_LINE();

