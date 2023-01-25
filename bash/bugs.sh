#!/bin/bash
#!/bin/bash
<<DOCUMENT
PURPOSE
     bugs - shown known bugs
DOCUMENT

source shtour_common.sh

if [ $# -ne 1 ]; then
	echo "Instruction"
	echo '	First : bugs.sh <anything except "(">'
	echo '	Second: bugs.sh "("'
	echo '	Thrid : Compare the difference'
	exit 1
fi

draw_line	
if [ -z "$1" ]; then
	echo '$1 is empty'
fi
if [ -z "$1" -o -z "$1" ]; then
	echo '$1 is empty'
fi
if [ "$1" == "a" -o "$1" == "b" ]; then
	echo '$1 == a or b'
fi
draw_line	
