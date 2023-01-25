#!/bin/bash
<<DOCUMENT
TOURS
   1. lastpipe 
   2. pipefail 
   3. process substitution
OPTIONS
   1: [-u|*-s]
   2: [-u|*-s|-o] file... 
   3: file...
DOCUMENT
source shtour_common.sh
try_help

if [[ $BASH_VERSION =~ ^([[:digit:]])+\.([[:digit:]]+) ]]; then
	 (( BASH_REMATCH[1] < 4 || ( BASH_REMATCH[1] == 4 && BASH_REMATCH[2] < 2) )) && abort "Bash version must > 4.2"
else
	abort "BASH_VERSION error: $BASH_VERSION"
fi

function lastpipe_ {
	# backup current state of lastpipe option...
	[[ $BASHOPTS == *lastpipe* ]] && old_lastpipe="-s" || old_lastpipe="-u"
	if [[ -z $1 ]]; then
		shopt -s lastpipe 
	else
		case $1 in
		-s) shopt -s lastpipe ;;
		-u) shopt -u lastpipe ;;
		*) abort "Invalid lastpipe option: $1" ;;
		esac
	fi

	cmd=(echo)
	seq 5 | while read n; do
		cmd+=($n)
		"${cmd[@]}"
	done
	# => 1
	# => 1 2
	# => 1 2 3
	# => 1 2 3 4
	# => 1 2 3 4 5 

	# Restore lastpipe state, in case you want to add more code below
	shopt "${old_lastpipe}" lastpipe
	declare -p cmd  # => declare -a cmd=([0]="echo")
}

function pipefail_ {
	if [[  $# -eq 0 ]] ; then
		shopt -o pipefail
	else
		shopt ${1}o pipefail || abort "unsupported option: $1"
		shift
	fi
	ls "$1"  | cat "$2"  | while read -r line; do echo $line; done 	
	echo "'\$?': $?"
}

function process_substitute_ {
	draw_line
    REFERENCE "https://unix.stackexchange.com/questions/52026/bash-how-to-read-one-line-at-a-time-from-output-of-a-command"
    REFERENCE "https://stackoverflow.com/questions/43736021/get-exit-code-of-process-substitution-with-pipe-into-while-loop"
	REFERENCE "http://mywiki.wooledge.org/ProcessSubstitution"
	draw_line
	explain "TASK: Get exit code of process substitution with pipe into while loop" 

	prompt_t3 "normal process substitution"
	while read -r line; do
		echo $line
	done < <(ls "$@" 2>&1; status=$?)
	echo "return code of process sustitution: $status"
	annotate1 "result: failed"

	prompt_t3 "while read line; do ... done < <(process; echo code:\$?)  "
	while read -r line; do
		if [[ $line =~ code:([[:digit:]]+) ]]; then
			status=${BASH_REMATCH[1]}
		else
			echo $line
		fi
	done < <(ls "$@" 2>&1; echo code:$?)
	echo "return code of process sustitution: $status"
	annotate1 "result: ok; not perfect; ensure the adding information is unique"

	draw_line
}

[[ $# -lt 1 ]] && { print_document; exit 0; }

action=$1
shift
case $action in
1) lastpipe_           "$@" ;;
2) pipefail_           "$@" ;;
3) process_substitute_ "$@" ;;
*) abort "unsupported action: $action" ;;
esac
