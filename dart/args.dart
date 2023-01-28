import 'dart:io';
import 'dart:core';

void main(List<String> args) {
	String exe=Platform.executable;
	var flags=Platform.executableArguments;
	Uri    script=Platform.script;
	print("exe=$exe");
	print("flags=$flags");
	print("script=$script");
	
	for(int i = 0; i < args.length; i++) 
		print("[arg-$i] ${args[i]}");
}
