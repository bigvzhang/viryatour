#!/bin/bash
<<DOCUMENT
PURPOSE
    ssh_pipe.sh 
DESCRIPTION
    [Reference](http://linux.icydog.net/ssh/piping.php)
    [io redirection](https://stackoverflow.com/questions/54469312)
EXAMPLES
	ssh vic02 'stat   -c %y f1  f2 f3  /d/tmp/f1 f4 2>&1'
	ssh vic02 '"stat" -c %y f1 "f2 f3" /d/tmp/f1 f4 2>&1'
DOCUMENT
source shtour_common.sh
print_document
