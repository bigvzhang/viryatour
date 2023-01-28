const io =require('virya_io');
const {HEAD,HEAD2,REFERENCE,HORIZONTAL}=require('virya_io');

HEAD("Test whether timeout is cleared/running")
var hanler1 ;
handler1 = setTimeout(()=>io.print_obj(handler1,"FinishedEventHandler"), 3000);
io.print_obj(handler1,"OriginalEventHandler");
HORIZONTAL()

HEAD("Test async/await")

      function func1 (){ console.log("Func1 sync  => cannot wait sync functions in nodejs, but can in browser") }
async function func2 (){ console.log("Func1 async") }
async function func3 (){
	console.log("Func1 async") }
	//await func1()
	await func2()
}
