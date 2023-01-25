#!/bin/bash
source shtour_common.sh
func1(){ 
	echo "Total Arguments:" $#  " => $*"
}
func2(){ 
	echo "Total Arguments:" $#  " => $@"
}
print_arguments1 () {
	for i in "$@"; do echo " $i"; done
}
print_arguments2 () {
	#!Notice, there are two forms:
	#   for((i=1;i<=$#;i++))   (1st form)
	#   for i in $(seq 1 $#)   (2nd form)
	for i in $(seq 1 $#) 
	do
		echo " $i => ${!i}"
	done
}
draw_line
echo "Rural:"
echo "Total Arguments:" $#
echo '  $@ :' $@
echo ' "$@":' "$@"
echo '  $* :' $*
echo ' "$*":' "$*"
draw_line
echo '== iterate args by phrase as for in in "$@"'
print_arguments1 "$@"
echo '== iterate args by phrase as for ((i++)) ${!i}'
print_arguments2 "$@"
draw_line
echo "=====assign value to one array===="
args=("$@")
echo '==("$@")' "==>ValueOfStar: ${#args[*]} ValueOfAt:${#args[@]}"
for((i=0;i<${#args[*]};i++)) do echo "   $i => ${args[i]}"; done
args=($@)
echo '==($@)'   "==>ValueOfStar: ${#args[*]} ValueOfAt:${#args[@]}"
for((i=0;i<${#args[*]};i++)) do echo "   $i => ${args[i]}"; done

args=("$*")
echo '==("$*")' "==>ValueOfStar: ${#args[*]} ValueOfAt:${#args[@]}"
for((i=0;i<${#args[*]};i++)) do echo "   $i => ${args[i]}"; done
args=($*)
echo '==($*)'   "==>ValueOfStar: ${#args[*]} ValueOfAt:${#args[@]}"
for((i=0;i<${#args[*]};i++)) do echo "   $i => ${args[i]}"; done

draw_line
echo 'pass parameter as $*'
func1 $*
draw_line
echo 'pass parameter as $@'
func2 $@
draw_line
echo 'pass parameter as "$@"'
func2 "$@"
draw_line
args=("$@")
echo '==pass parameter as "${args[@]}"'
func2 "${args[@]}"
echo '==pass parameter as ${args[@]}'
func2 ${args[@]}
echo '==pass parameter as "${args[*]}"'
func2 "${args[*]}"
echo '==pass parameter as ${args[*]}'
func2 ${args[*]}
draw_line
echo '==for v in "$@" testing'
for v in "$@"; do
	echo " $v"
done
draw_line
echo '==for v in "${args[@]}" testing'
for v in "${args[@]}"; do
	echo " $v"
done

draw_line
prompt "testing BASH_ARGV0"
echo "BASH_ARGV0=${BASH_ARGV0}"
echo '$0'="${0}"
annotate1 "Summary"
annotate1 " 1. BASH_ARGV0/BASH_ARGV is available only in the current bash execution call stack"
annotate1 " 2. \$0 is available in function"

draw_line
