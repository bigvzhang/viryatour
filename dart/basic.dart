import "dart:io";

void identifiers() {
	var name    = "World";
	var _name   = "_name";
	var $name   = "$name";     // valid, addition to c/c++
	var name1   = "name1";
	var n2ame   = "n2ame";     // valid, but some document says no
	var name_1  = "name_1";
	var name__1 = "name__1";   // valid, but some document says no
}

void types() {
	// number
	int    i  = 80;
	double pi = 3.14;
	// string
	var msg = "Welcome";
}

void main(List<String> args) {
	String cmd = "";
	for(String arg in args){ 
		if(arg == "identifiers"){
			cmd=arg;
		}else if(arg == "types"){
			cmd=arg;
		}else{
			print("invald argument - $arg");
			exit(1); // require dart:io
		}
	}
	if     (cmd == "identifiers"){ identifiers(); }
	else if(cmd == "types"){ types(); }
	else                   { types(); }
}
