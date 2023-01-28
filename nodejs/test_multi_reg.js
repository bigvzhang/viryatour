let fs=require('fs')
function test_read(file) {
	let data= fs.readFileSync(file)
	if(!data){
		return 0
	}
	//let rg0 = /(.*)[\r]?\n/g;
	let rg0 = /([^\r\n]+)/g; // /([^\r\n]*)/g will result 
	let mr0 = null
	let line_no = 0
	console.log("Pattern:", rg0, "File:", file)
	while ((mr0 = rg0.exec(data)) != null)  {
		console.log("    ", ++line_no, mr0[1]);
	}
	return 1
}

function copy_file(file, file2) {
	let data= fs.readFileSync(file)
	if(!data){
		return 0
	}
	let rg0 = /(.*)[\r]?\n/g;
	let mr0 = null
	let line_no = 0
	let content = "";
	while ((mr0 = rg0.exec(data)) != null)  {
		content += "\n" + mr0[1]	
	}
	// now the content which first line is empty, the last line without '\n'
	fs.writeFileSync(file2, content)
}


copy_file('test_multi_reg1.txt', 'test_multi_reg3.txt')
test_read('test_multi_reg1.txt')
test_read('test_multi_reg2.txt')
test_read('test_multi_reg3.txt')

console.log('Conclusion: the rgx will match the last line whether it is terminated by newline!')
