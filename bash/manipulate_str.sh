#!/bin/bash
<<DOCUMENT
1.  simple
2.  trim  
    SYNTAX
        trim [a_string_to_test]
    [reference](https://stackoverflow.com/questions/369758/how-to-trim-whitespace-from-a-bash-variable)
3.  todo
    [reference](https://stackoverflow.com/questions/806906/how-do-i-test-if-a-variable-is-a-number-in-bash)
DOCUMENT
source shtour_common.sh
try_help


function run_and_print {
	printf "%-60s" $* 
}

function simple_1_ {   # basic
	name='viczhang@facemerry.com'
	s=abcABC123ABCabc
	echo ${s#a*C}
	echo ${s#b*C}
}

[[ $# -eq 0 ]] && { simple_1_; exit 0; } 


function simple_2_ {   # trim
	draw_line
	if [[ -z $1 ]]; then
		var="     hello  oh yeah    "
	else
		var=$1
	fi
	echo "origin: ==$var=="
	echo " triml: ==${var#${var%%[![:space:]]*}}=="   # remove leading whitespace characters
	echo " trimr: ==${var%${var##*[![:space:]]}}=="   # remove trailing whitespace characters
	draw_line
}
action=$1; shift
case $action in
1)  simple_1_      ;;
2)  simple_2_ "$@" ;;
*)  abort "Unsupported command $1"
esac
