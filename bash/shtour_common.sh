#!/bin/bash

function abort {
	if [ $# -gt 0 ]; then
		echo "$@"
	fi
	exit 1
}

function abortn {
	if [ $# -eq 0 ]; then
		exit 1
	fi
	local rtnVal=$1 
	shift
	if [ $# -gt 0 ]; then
		echo "$@"
	fi
	exit $rtnVal
}


function echon { [ 1=1 ]; } # do nothing

   	# prompt one string with leading '====='
function prompt  { if [ $# -ge 1 ]; then printf "%s%s\n" '====' "$*"; fi; }
function prompt1 { if [ $# -ge 1 ]; then printf "%s%s\n" '====' "$*"; fi; }
function prompt2 { if [ $# -ge 1 ]; then printf "%s%s\n" '\x2D---' "$*"; fi; }
function prompt3 { if [ $# -ge 1 ]; then printf "%s%s\n" '~~~~' "$*"; fi; }
function prompt4 { if [ $# -ge 1 ]; then printf "%s%s\n" '....' "$*"; fi; }
function prompt5 { if [ $# -ge 1 ]; then printf "%s%s\n" '____' "$*"; fi; }
function prompt6 { if [ $# -ge 1 ]; then printf "%s%s\n" '****' "$*"; fi; }
function prompt7 { if [ $# -ge 1 ]; then printf "%s%s\n" '////' "$*"; fi; }
function prompt8 { if [ $# -ge 1 ]; then printf "%s%s\n" '\\\\' "$*"; fi; }
function prompt9 { if [ $# -ge 1 ]; then printf "%s%s\n" '++++' "$*"; fi; }

function explain { echo "$@"; }
function REFERENCE { echo "Reference - $@"; }

function prompt_line { # ... --pchar c 
	__args=()
	__columns="" 
	for (( i = 1; i <= $# ; i++ )); do
		if [[ ${!i} == 	"--pchar" ]]; then
			(( i++ ))
			if (( i <= $# )); then
				__pchar=${!i}
			fi
		elif [[ -z $__columns ]]; then # first one is columns
			__columns=${!i}
		else
			__args+=("${!i}")
		fi
	done
	__pchar=${__pchar:-*}
	__columns=${__columns:-80}
	if [ ${#__args[@]} -ge 1 ]; then
		printf $__pchar'%.0s' {1..4}
		printf "%s" "${__args[*]}"
		s="${__args[*]}"
		mylen=$(( __columns - 4 - ${#s}))
		[[ $mylen -gt 0 ]] && eval "printf '$__pchar%.0s' {1..$mylen}"
		printf '\n'
	fi
}

COLUMNS=${COLUMNS:=$(tput cols)} # set default line size

function prompt_center { prompt_line $COLUMNS "$@"; }
function prompt_t1 { prompt_line $COLUMNS       "$@" --pchar '='; }
function prompt_t2 { prompt_line $((COLUMNS-4)) "$@" --pchar '\x2D'; } # 0x2D: '-'
function prompt_t3 { prompt_line $((COLUMNS-4)) "$@" --pchar '~'; }
function prompt_t4 { prompt_line $((COLUMNS-4)) "$@" --pchar '.'; }
function prompt_t5 { prompt_line $((COLUMNS-4)) "$@" --pchar '_'; }
function prompt_t6 { prompt_line $((COLUMNS-4)) "$@" --pchar '*'; }
function prompt_t7 { prompt_line $((COLUMNS-4)) "$@" --pchar '/'; }
function prompt_t8 { prompt_line $((COLUMNS-4)) "$@" --pchar '\'; }
function prompt_t9 { prompt_line $((COLUMNS-4)) "$@" --pchar '+'; }

function head1 { prompt_line $COLUMNS "$@" --pchar '='; }
function head2 { prompt_line $COLUMNS "$@" --pchar '\x2D'; } # 0x2D: '-'
function head3 { prompt_line $COLUMNS "$@" --pchar '~'; }
function head4 { prompt_line $COLUMNS "$@" --pchar '.'; }
function head5 { prompt_line $COLUMNS "$@" --pchar '_'; }
function head6 { prompt_line $COLUMNS "$@" --pchar '*'; }
function head7 { prompt_line $COLUMNS "$@" --pchar '/'; }
function head8 { prompt_line $COLUMNS "$@" --pchar '\'; }
function head9 { prompt_line $COLUMNS "$@" --pchar '+'; }


function annotate1 { echo "// ""$@"; }

<<DOCUMENT
NAME
    draw_line - print one line in the terminal
SYNOPSIS
	draw_line              (1st form)
	draw_line char         (2nd form)
	draw_line char width   (3rd form)
DESCRIPTION
	In the lst form, print a line whose width equals the columns of xterm and whose 
    char is '='. In the 2nd from and 3rd form, the line's char is the the first 
	argument. In the 3rd, the line's width is the second argument. 
DOCUMENT
function draw_line {
	if [ $# -eq 2 ]; then
		if [[ $2 =~ ^[0-9]+$ ]]; then
			eval printf "'$1%.0s'" {1..$2}
		else  
			eval printf "'$1%.0s'" {1..$COLUMNS}
		fi
	elif [ $# -eq 1 ]; then
		eval printf "'$1%.0s'" {1..$COLUMNS}
	else
		eval printf "'=%.0s'" {1..$COLUMNS}
	fi
	printf '\n'
}
function draw_line1   { draw_line '='; }
function draw_line2   { draw_line '\x2D'; }
function draw_line3   { draw_line '~'; }
function horizontal   { draw_line '='; }
function horizontal1  { draw_line '='; }
function horizontal2  { draw_line '\x2D'; }
function horizontal3  { draw_line '~'; }
function horizontal4  { draw_line '.'; }
function horizontal5  { draw_line '_'; }
function horizontal6  { draw_line '*'; }
function horizontal7  { draw_line '/'; }
function horizontal8  { draw_line '\'; }
function horizontal9  { draw_line '+'; }
function horizontal1s { draw_line '=' $((COLUMNS-4)); }
function horizontal2s { draw_line '\x2D' $((COLUMNS-4)); }
function horizontal3s { draw_line '~' $((COLUMNS-4)); }
function horizontal4s { draw_line '.' $((COLUMNS-4)); }
function horizontal5s { draw_line '_' $((COLUMNS-4)); }
function horizontal6s { draw_line '*' $((COLUMNS-4)); }
function horizontal7s { draw_line '/' $((COLUMNS-4)); }
function horizontal8s { draw_line '\' $((COLUMNS-4)); }
function horizontal9s { draw_line '+' $((COLUMNS-4)); }

<<DOCUMENT
NAME
    print_document - search the DOCUMENT in the file and print
SYNOPSIS
	print_document [filename]
DESCRIPTION
	if there's no filename, the filename defaults value of ENV BASH_SOURCE[1].
DOCUMENT
function print_document {
	local file=${BASH_SOURCE[1]}
	if [ $# -eq 1 ]; then
		file=$1	
	fi
	awk '{if(/^<<DOCUMENT/){to_print=1}else if(/^DOCUMENT/){to_print=0} else if(to_print==1) print($0)}' $file
}

function try_help {
	local i
	for i in ${BASH_ARGV[@]}; do
		if [[ $i == "--help" ]]; then
			print_document ${BASH_SOURCE[1]} # this file's no is 0; the caller 1
			exit 0
		fi
	done
}

function trace_src {
	# $1: n[,n]
	#echo ${BASH_SOURCE[0]} ${BASH_SOURCE[1]} ${BASH_SOURCE[2]} cnt:${#BASH_SOURCE[@]}
    #echo ${BASH_LINENO[0]} ${BASH_LINENO[1]} ${BASH_LINENO[2]} cnt:${#BASH_LINENO[@]} 
	[[ -n $1 && $1 =~ ^([\+\-]?[[:digit:]]+)(,(([\+\-]?[[:digit:]]+))){0,1}$ ]] || return 1
	local file=${BASH_SOURCE[1]}
	local lineno lineno1 lineno2
	local lines line i
	lineno=${BASH_LINENO[0]}
	((lineno1=lineno+${BASH_REMATCH[1]}))
	local IFS=$'\n'
	if [[ -z ${BASH_REMATCH[3]} ]]; then
		lines=($(sed -n "${lineno1}p"  "$file"))
	else
		((lineno2=lineno+${BASH_REMATCH[3]}))
		lines=($(sed -n "${lineno1},${lineno2}p"  "$file"))
	fi
	for((i=0;i<${#lines[@]};i++)); do
		line=${lines[i]}
		[[ $line =~ ^(.*)trace_src[[:space:]] ]] && line=${BASH_REMATCH[1]}
		line=${line#${line%%[![:space:]]*}}
		line=${line%${line##*[![:space:]]}}
		echo "++ $line"
	done	
}

function trace_code {  # trace one line of code
	local file=${BASH_SOURCE[1]}
	local lineno
	local lines line i
	lineno=${BASH_LINENO[0]}
	local IFS=$'\n'
	lines=($(sed -n "${lineno}p"  "$file"))
	for((i=0;i<${#lines[@]};i++)); do
		line=${lines[i]}
		[[ $line =~ ^[[:space:]]*trace_code[[:space:]]+(.*) ]] && line=${BASH_REMATCH[1]}
		line=${line#${line%%[![:space:]]*}}
		line=${line%${line##*[![:space:]]}}
		echo "$line" 
	done	
}

function echoe {  # echo current expression
	local file=${BASH_SOURCE[1]}
	local lineno lines line comment i
	lineno=${BASH_LINENO[0]}
	local IFS=$'\n'
	lines=($(sed -n "${lineno}p"  "$file"))
	for((i=0;i<${#lines[@]};i++)); do
		line=${lines[i]}
		[[ $line =~ ^[[:space:]]*echoe[[:space:]]+(.*) ]] || continue 
		line=${BASH_REMATCH[1]}
		if [[ $line =~ ^(.*)[[:space:]]+(#.*)$ ]]; then
			line=${BASH_REMATCH[1]}
			comment=" ${BASH_REMATCH[2]}"
		else
			comment=""
		fi
		line=${line#${line%%[![:space:]]*}}
		line=${line%${line##*[![:space:]]}}
		echo -n "$line => \`" 
		eval "echo -n $line" 
		echo "\`$comment"
	done	
}


function trace_exp_v {  # print leading expression and the v
	local file=${BASH_SOURCE[1]}
	local lineno lines line comment i
	lineno=${BASH_LINENO[0]}
	local IFS=$'\n'
	lines=($(sed -n "${lineno}p"  "$file"))
	for((i=0;i<${#lines[@]};i++)); do
		line=${lines[i]}
		[[ $line =~ ^[[:space:]]*(.*)\; ]] || continue 
		[[ $line =~ ^echon.(.*) ]] && line="${BASH_REMATCH[1]}      "
		echo "$line => $@"
	done	
}
function trace_exp_r {  # print leading expression and the v
	local file=${BASH_SOURCE[1]}
	local lineno lines line comment i
	lineno=${BASH_LINENO[0]}
	local IFS=$'\n'
	lines=($(sed -n "${lineno}p"  "$file"))
	for((i=0;i<${#lines[@]};i++)); do
		line=${lines[i]}
		[[ $line =~ ^[[:space:]]*(.*)\; ]] || continue 
		line=${BASH_REMATCH[1]}
		[[ $line =~ ^echon.(.*) ]] && line="${BASH_REMATCH[1]}      "
		echo "$line => ${1}: ${!1}"
	done	
}
