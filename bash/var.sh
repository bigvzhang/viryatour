#!/bin/bash
<<DOCUMENT
NMAE
     var.sh - test variable declaration, substitutions 
SYNOPSIS
     var.sh [--subs-qm|subs|declare|local|nameref]
     var.sh [--help|-h]
DESCRIPTION
     --subs-qm substition in the form containing question mark 
     --subs    substition exception the form containing question mark
     --declare test 'declare' bash built-in command
     --local   test 'local' bash built-in key-word
     --nameref test 'declare -n' bash built-in command
DOCUMENT

source shtour_common.sh
PROGDIR=${0%/*}
PROGNAME=${0##*/}

  
function test_subs_qm {
	echo ${A:?A is not, exit(1) from process(not only from function)}
}

function test_subs {
	echo ${B:-This is from B} 
	echo ${C:=This is from C}
	echo ${B}
	echo ${C}
}

function print_ { # assistant function to print some varialbes
	let v0+=100	
	let v1+=1
	let v2+=2
	echo "v0:$v0 v1:$v1 v2:$v2 v3:$v3 v4:$v4 v5:$v5"
	declare -p v0 v1 v2 v3 v4 v5
}

function test_declare {
	declare -x v0=100
	           v1=1
	export	   v2=2
	declare    v3=3
	declare    v4=4
	declare -x v5=5
	v4=40
	v5=50
	prompt_t1 "first call"
	print_
	prompt "v0:$v0"

	prompt_t1 "call in sub"
	(print_)
	prompt "v0:$v0"

	prompt_t1 "second call"
	print_
	prompt "v0:$v0"


	auxifile=${PROGNAME%.sh}_au.sh

	prompt_t1 "call a shell file"
	$PROGDIR/$auxifile
	prompt_t1 "call a shell file directly(in the current shell)"
	. $PROGDIR/$auxifile
	draw_line
}

function test_local {
	horizontal #============================================
	explain "parent: local v1 v2 v3"
	explain "  sub1: local v1 v2       v5 v6"
	explain "  sub2: local v1 v2       v5 v6"
	horizontal3 #============================================
	local v1=1
	local v2=2
	local v3
	v3=300
	v4=400
	v5=500
	v6=600
	function sub1_ {
		local v1 v2 v5 v6
		v1=a
		v2=a
		v3=301
		v4=401
		v5=501
		echo "[/test_local/sub1/] $v1 $v2 $v3 $v4 $v5 $v6"
	}
	function sub2_ {
		local v1 v2 v5 v6
		v1=b
		v2=b
		v3=302
		v4=402
		v5=502
		echo "[/test_local/sub2/] $v1 $v2 $v3 $v4 $v5 $v6"
	}
	echo "[/test_local/     ] $v1 $v2 $v3 $v4 $v5 $v6"
	sub1_
	echo "[/test_local/     ] $v1 $v2 $v3 $v4 $v5 $v6"
	sub2_
	echo "[/test_local/     ] $v1 $v2 $v3 $v4 $v5 $v6"
	
	horizontal #============================================
	explain "SUMMARY"
	explain "    1. sub function could modify parent's variable whichever is local or non-local"
	explain "    2. sub function will not access parent's variale which is defined local in the sub"
	horizontal #============================================
}
function test_nameref {
	horizontal #===============================================
	local A=1          ; trace_exp_r A
	local -n X=A       ; trace_exp_r X
	((A++))            ; trace_exp_r A
	echon "X changes"  ; trace_exp_r X
	head3 "expansion of nameref" #===============================================
	local N=A          ; trace_exp_r N
	local -n M=N       ; trace_exp_r M
	echoe ${!N}        # value of A 
	echoe ${!M}        # name of the reference 
	horizontal #===============================================
}

PARSED_ARGV=$(getopt -o "h" -l help,subs-qm,subs,declare,local,nameref -n test17_var.sh -- "$@") || exit $?
set -- $PARSED_ARGV; PARSED_ARGS=("$@")
for((i=0; i<${#PARSED_ARGS[@]}; i++)); do
  case ${PARSED_ARGS[i]} in
    --subs-qm) test_subs_qm    ;;
    --subs)    test_subs       ;;
    --declare) test_declare    ;;
    --local)   test_local      ;;
    --nameref) test_nameref     ;;
	-h|--help) print_document; exit 0;;
	--) ;;
  esac
done

if ((i==1)); then # plus one, because "--" is appened
	draw_line	
	echo "Action: test substitions"
    test_subs
	draw_line	
fi





