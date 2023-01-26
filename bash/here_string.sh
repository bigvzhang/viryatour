#!/bin/bash
<<DOCUMENT
PURPOSE
    Test here string - varialbe and array as pipe input 
DOCUMENT
source shtour_common.sh
try_help


function print_array {
	echo "content of $1"
    name=$1[@]
    for i in "${!name}"; do
        echo "    "$i
    done
}
head1 "For one string"       ; trace_src 1
cat <<<"HelloWorld"
                               trace_src 1
cat <<<"$HOME"

head1 "For an array"         ; trace_src 1
x=("a" "b" "x" "y z" "d e")
print_array x
horizontal4;	               trace_src 1
cat <<<"${x[*]}"
	                           trace_src 1
cat <<<"${x[@]}"
	                           trace_src 1
cat <<<"${x[*]@Q}"
	                           trace_src 1
cat <<<"${x[@]@Q}"
horizontal4;                   trace_src 1
IFS=$'\n' 
	                           trace_src 1
cat <<<"${x[*]}"
	                           trace_src 1
cat <<<"${x[@]}"
	                           trace_src 1
cat <<<"${x[*]@Q}"
	                           trace_src 1
cat <<<"${x[@]@Q}"

horizontal5
