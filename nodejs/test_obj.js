var DRAW_LINE=require('virya_io').DRAW_LINE;
var EXPLAIN=require('virya_io').EXPLAIN;
var print_obj =require('virya_io').print_obj;
var print_obj_prop =require('virya_io').print_obj_prop;
var printf    =require('virya_io').printf;

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



DRAW_LINE();
const yoshi = { skulk: true };
const hattori = { sneak: true };
const kuma = { creep: true };
if ("skulk" in yoshi) 
    console.log("Yoshi can skulk");
if (!("sneak" in yoshi)) 
    console.log("Yoshi cannot sneak");
if (!("creep" in yoshi)) 
    console.log("Yoshi cannot creep");

DRAW_LINE('-');
Object.setPrototypeOf(yoshi, hattori);
if ("sneak" in yoshi)
    console.log("Yoshi can now sneak");
if (!("creep" in hattori))
    console.log("Hattori cannot creep");

DRAW_LINE('-');
Object.setPrototypeOf(hattori, kuma);
if ("creep" in hattori)
    console.log("Hattori can now creep");
if ("creep" in yoshi)
    console.log("Yoshi can also creep");
