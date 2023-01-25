#!/bin/bash
<<DOCUMENT
PURPOSE
     read_line.sh read command to prevent leading/trailing whitespace from being trimmed
SYNOPSIS
     read_line.sh --file file
     read_line.sh [1|2|3|4|5|9]
		   1-5 - test functions to read array
           9   - read lines from ipconfig; only print part of the content
           ""  - run functions from 1 to 5
DESCRIPTION
     [Reference](https://www.cyberciti.biz/faq/unix-howto-read-line-by-line-from-file/)
DOCUMENT

source shtour_common.sh
try_help


function read_from_file { 
	while IFS= read -e line
	do
		echo "$line"
	done < "$1"
}


function read_line_to_array_1 { 
	prompt_t1 "use default IFS; read -a"
	while read -e line; do 
		read -a  words <<<$line
		for ((i=0; i < ${#words[@]}; i++)); do
			v=${words[i]}
			printf "%-45s ~ [%2d] => [%2d] %s\n" "$line" ${#line}  "${#v}" "'${v}'"
		done
	done < <( cat <<LINES
    /c/nodejs13
    /d/VicTour/nd01          -exclude  x y z
  /d/msys64B
    /e/MyWinApp2/virya-win32-x64
LINES
)
	prompt_t3 "OK, but the line is trimmed"
}

function read_line_to_array_2 { 
	prompt_t1 "use IFS=''; read -a"
	local IFS
	IFS=""
	while read -e line; do 
		read -a words <<<$line
		for ((i=0; i < ${#words[@]}; i++)); do
			v=${words[i]}
			printf "%-45s ~ [%2d] => [%2d] %s\n" "$line" ${#line}  "${#v}" "'${v}'"
		done
	done < <( cat <<LINES
    /c/nodejs13
    /d/VicTour/nd01          -exclude  x y z
  /d/msys64B
    /e/MyWinApp2/virya-win32-x64
LINES
)

	prompt_t3 "Bad"
}

function read_line_to_array_3 { 
	prompt_t1 "use IFS=''; readarray -t -d ' '"
	local IFS
	IFS=""
	while read -e line; do 
		readarray -t -d ' ' words <<<$line
		for ((i=0; i < ${#words[@]}; i++)); do
			v=${words[i]}
			printf "%-45s ~ [%2d] => [%2d] %s\n" "$line" ${#line}  "${#v}" "'${v}'"
		done
	done < <( cat <<LINES
    /c/nodejs13
    /d/VicTour/nd01          -exclude  x y z
  /d/msys64B
    /e/MyWinApp2/virya-win32-x64
LINES
)

	prompt_t3 "will produce extra"
}



function read_line_to_array_4 { 
	prompt_t1 "use default IFS; read -d ' ' -a"
	while read -e line; do 
		read -d ' ' -a words <<<$line
		for ((i=0; i < ${#words[@]}; i++)); do
			v=${words[i]}
			printf "%-45s ~ [%2d] => [%2d] %s\n" "$line" ${#line}  "${#v}" "'${v}'"
		done
	done < <( cat <<LINES
    /c/nodejs13
    /d/VicTour/nd01          -exclude  x y z
  /d/msys64B
    /e/MyWinApp2/virya-win32-x64
LINES
)

	prompt_t3 "will produce extra"
}


function read_line_to_array_5 { 
	prompt_t1 "changes IFS each time before read"
	local IFS
	oldIFS=$IFS
	IFS=''
	while read line; do 
		IFS=' '
		read -a words <<<$line
		for ((i=0; i < ${#words[@]}; i++)); do
			v=${words[i]}
			printf "%-45s ~ [%2d] => [%2d] %s\n" "$line" ${#line}  "${#v}" "'${v}'"
		done
		IFS=''
	done < <( cat <<LINES
    /c/nodejs13
    /d/VicTour/nd01          -exclude  x y z
  /d/msys64B
    /e/MyWinApp2/virya-win32-x64
LINES
)

	prompt_t3 "Perfect"
}


function ipcfg0_ {
	prompt_t6 "while read -r line"
	local to_print
	while read -r line; do
		if [[ $line =~ adapter ]]; then
			[[ $to_print == "1" ]] && break
			to_print=1
		fi
		[[ $to_print == 1 ]] && echo "==test0=="$line
	done < <(/c/Windows/system32/ipconfig)
}
function ipcfg1_ {
	prompt_t6 "IFS=;while read -r line"
	local IFS=
	local to_print
	while read -r line; do
		if [[ $line =~ adapter ]]; then
			[[ $to_print == "1" ]] && break
			to_print=1
		fi
		[[ $to_print == 1 ]] && echo "==test1=="$line
	done < <(/c/Windows/system32/ipconfig)
}
function ipcfg2_ {
	prompt_t6 "while IFS= read -r line"
	local to_print
	while IFS= read -r line; do
		if [[ $line =~ adapter ]]; then
			[[ $to_print == "1" ]] && break
			to_print=1
		fi
		[[ $to_print == 1 ]] && echo "==test2=="$line
	done < <(/c/Windows/system32/ipconfig)
}
function ipcfg3_ {
	prompt_t6 'IFS="\r";while read -r line'
	local IFS="\r"
	local to_print
	while read -r line; do
		if [[ $line =~ adapter ]]; then
			[[ $to_print == "1" ]] && break
			to_print=1
		fi
		[[ $to_print == 1 ]] && echo "==test3=="$line
	done < <(/c/Windows/system32/ipconfig)
}
function ipcfg4_ {
	prompt_t6 'while IFS="\r" read -r line'
	local to_print
	while IFS="\r" read -r line; do
		if [[ $line =~ adapter ]]; then
			[[ $to_print == "1" ]] && break
			to_print=1
		fi
		[[ $to_print == 1 ]] && echo "==test4=="$line
	done < <(/c/Windows/system32/ipconfig)
}
function ipcfg5_ {
	prompt_t6 'while IFS="\r" read -r line'
	local to_print
	while IFS="\r" read -r line; do
		if [[ $line =~ adapter ]]; then
			[[ $to_print == "1" ]] && break
			to_print=1
		fi
		[[ $to_print == 1 ]] && echo $line
	done < <(/c/Windows/system32/ipconfig)
}
function test_9_ {
	draw_line
	ipcfg0_
	ipcfg1_
	ipcfg2_
	ipcfg3_
	ipcfg4_
	ipcfg5_
}




if [[ $# -eq 2  && "$1" == "--file" ]]; then
	read_from_file $2 ;	exit 0 
fi
if [[ $# -eq 0 ]]; then
	read_line_to_array_1
	read_line_to_array_2
	read_line_to_array_3
	read_line_to_array_4
	read_line_to_array_5
else
	for ((i = 1; i <= $#; i++)); do
		case ${!i} in
		1) read_line_to_array_1 ;;
		2) read_line_to_array_2 ;;
		3) read_line_to_array_3 ;;
		4) read_line_to_array_4 ;;
		5) read_line_to_array_5 ;;
		9) test_9_              ;;
		*) echo "Invalid argument: ${!i}"; exit 1;;
		esac
	done
fi

draw_line
explain "CONCLUSION"
explain "    1. delimiter is not equal to IFS"
explain "    2. 'read -a' not equal to 'readarray'" 
explain "    3. set IFS each time before read as case 5"
explain "SUMMARY"
explain "    1. expression 'while IFS= read -r line'      does NOT work properly to read whole lines"
explain "                  'IFS=;  while read -r line'    works"
explain "    2. expression 'while IFS='\r' read -r line'  does NOT work"
explain "                  'IFS='\r'; while read -r line' works"
explain "TORESEARCH"
explain "    Check the difference between test4 and test 5; why there is special space in test4 ?"
draw_line
