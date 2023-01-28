var path=require('path');
var currentPath = process.cwd();
console.log("cwd:", currentPath);
console.log("__dirname:", __dirname);
console.log(path.join(currentPath, "xyz"));
