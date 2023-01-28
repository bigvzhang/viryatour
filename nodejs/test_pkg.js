var tool= require('./test_pkg_1');                // form 0
var AddNumbers=require("./test_pkg_1").AddNumbers // form 1 
var {MinusNumbers}=require("./test_pkg_1")        // form 2 
console.log("a=5,b=6")
console.log("called by tool.AddNumbers/tool.MinusNumbers")
console.log("a+b", tool.AddNumbers(5,6))
console.log("a-b", tool.MinusNumbers(5,6))
console.log("called by AddNumbers/MinusNumbers")
console.log("a+b", AddNumbers(5,6))
console.log("a-b", MinusNumbers(5,6))
