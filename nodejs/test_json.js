const io = require('virya_io.js');

let v1 = require( "./test_json1.json");
let v2 = require( "./test_json2.json");

io.printf("content of v1\n")
io.print_obj_type(v1);
console.log(v1);
io.printf("file:%s title:%s\n", v1.files[0].file, v1.files[0].title);

io.printf("content of v2\n")
io.print_obj_type(v2);
console.log(v2);
io.printf("file:%s title:%s\n", v2[0].file, v2[0].title);
