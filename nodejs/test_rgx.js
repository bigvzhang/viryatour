let a = new Array(
	 "ABC",
	 "Java",
	 "xx Java",
	 "Java.",
);
	
let pattern = "Java";

function f1(str){ 
	let result = str.match("^"+pattern);
	if(result != null){
		console.log(str+"=>"+result[0]); // null
		//console.log(result.length); 
	}else{
		console.log(str+"=>"+"Doesn't match"); // null
	}
}
for(let i = 0; i < a.length; i++){
	f1(a[i]);	
}
