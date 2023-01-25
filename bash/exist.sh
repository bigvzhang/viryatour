#!/bin/awk -f
function file_exists(file) {
  n=(getline _ < file);
  if (n > 0) {
    print "Found: " file;
    return 1;
  } else if (n == 0) {
    print "Empty: " file;
    return 1;
  } else {
    print "Error: " file;
    return 0;
  }
}

BEGIN {
	if(ARGV[1] == ""){
		print("Please input file name")
	}else{
		file_exists(ARGV[1]);
	}
}
