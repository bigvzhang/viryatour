#!/bin/bash
<<DOCUMENT
=========================================================================
${array[n]}                     # 数组的第n成员
${array[*]} 或${array[@]}       # 数组所有成员
${!array[*]} 或${!array[@]}     # 数组所有下标
${#array[*]} 或${#array[@]}     # 数组元素个数
${#array[0]}                    # 数组第一个成员的长度
=========================================================================
NOTICE
  "declare -a array" or "array=()" defines an indexed array
  "declare -A array" defines an associative array(non-indexed array)
=========================================================================
ENTRIES
  0. simple initialize - array=(1 2 3 "a b" "c d" 4 5)
  1. simple access -  {array[*]};  {!array[*]}
  2. access        -  {!array[@]}; {array[i]}
  3. operate       - add/del/sort
  4. pass an array as agrument
  5. read array(or string to array)
  6. null == empty?
  7. ((array[?]++))
=========================================================================
DOCUMENT
source shtour_common.sh
try_help

array=(one two three four [5]=five "100 thing")

function initialize_ {
	prompt_center 'INITIALIZE => array=(one two three four [5]=five)'
}

function access_mthd1_ {
	prompt_t1 'access - ${array[*]}, ${array[@]}, "${array[@]}"'
	echo "Array size: ${#array[*]}"
	echo "Array items:"
	for item in ${array[*]}
	do
		printf "   %s\n" $item
	done

	echo "Array indexes:"
	for index in ${!array[*]}
	do
		printf "   %d\n" $index
	done
	draw_line	
    explain 'NOTICE'
	explain '  use "${array[@]}" instead of ${array[@]} or ${array[*]}' 
	draw_line	
}

function print_items_and_indexes {  # access - "${!array[@]}" ${!array[$i]}"
	echo "Array indexes and content:"
	for index in "${!array[@]}"   # !!!notice must use "array[@]"
	do
		printf "%4s: %s\n" $index "${array[$index]}"
	done
}

function print_array__ {
	echo "content of $1"
    name=$1[@]
    for i in "${!name}"; do
        echo "    "$i
    done
}

function operate_ {
	prompt_center 'Original content of array'
	print_items_and_indexes

	prompt_center 'ADD: array+=([16]=sixteen seventeen) <= Notice the index of seventeen is 17'; trace_src 1
	array+=([16]=sixteen seventeen)
	print_items_and_indexes
	prompt "array[17] == ${array[17]}"

	prompt_center 'DEL: unset array[16]' ; trace_src 1
	unset array[16]
	print_items_and_indexes

	prompt_center "DEL: unset array[-1] == delete last"; trace_src 1
	unset array[-1]
	print_items_and_indexes

	prompt_center "Append array to array"; trace_src 1,3 
	x=("a b" "c d" "3 4")
	y=("e" "f g" "7 8")
	z=("${x[@]}" "${y[@]}")
	print_array__ x
	print_array__ y
	print_array__ z

	prompt_center "sort array"; trace_src 1
	readarray -t z1 < <(printf '%s\n' "${z[@]}" | sort | uniq)
	print_array__ z1;           trace_src 1
	IFS=$'\n' z2=($(sort <<<"${z[*]}")); unset IFS  # Notice cannot use $z[@]
	print_array__ z2
	# bad ===> #z3=($(printf "%s\n" "${z[@]}" | sort))
	#print_array__ z3
	
	horizontal2; REFERENCE "https://stackoverflow.com/questions/7442417/how-to-sort-an-array-in-bash"; horizontal2
}


function print_array_A {
	local -n myarray=$1
    for i in "${myarray[@]}"; do
        echo $i
    done
}

function print_array_B {
    eval myarray=('"${'$1'[@]}"')
    for i in "${myarray[@]}"; do
        echo $i
    done
}


function print_array_C {
    name=$1[@]
    for i in "${!name}"; do
        echo $i
    done
}


function print_array_D {
    for i; # in "$@"
	do
        echo $i
    done
}

function pass_array_ {
	prompt_t1 "How to pass array as an argument to a function in Bash"
	echo 'pass the name of array'
	echo ' 1. local -n myarray=$1, notice: version 4.3+ required'
	echo ' 2. eval myarray=("${=>$1<=[@]}")'
	echo ' 3. name=$1[@]; then use ${!name}'
	echo 'pass the content of array'
	echo ' 4. call "${array[@]}"'
	prompt "Method 1" && print_array_A array
	prompt "Method 2" && print_array_B array
	prompt "Method 3" && print_array_C array
	prompt "Method 4" && print_array_D "${array[@]}"


	draw_line
	prompt 'https://stackoverflow.com/questions/16461656/how-to-pass-array-as-an-argument-to-a-function-in-bash'
	prompt 'https://stackoverflow.com/questions/7442417'
	draw_line
}

function string_to_array_ {
	prompt_t1 "Split string to array"
	prompt "Using parenthesis"
	myvar="A1 A2 A3"
	myarray=($myvar)
	echo totalnumbers: ${#myarray[@]} "<=" $myvar

	prompt "Using read -a"
	myvar="B1 B2 B3"
	read -a myarray <<<$myvar
	echo totalnumbers: ${#myarray[@]} "<=" $myvar

	prompt "Using delimeter"
	myvar="string1;string2;string3"
	IFS=";" read -a myarray <<<$myvar
	echo totalnumbers: ${#myarray[@]} "<=" $myvar
}

function equal_ {
	draw_line
	a=(8)
	a+=("")
	b=(8 9)
	unset b[1]
	echo "a=> size:${#a[@]} content: { ${a[@]@Q} }"
	echo "b=> size:${#b[@]} content: { ${b[@]@Q} }"
	echo NOTICE
	echo '  a[1]  !=  b[1]'
	echo ' "a[1]" == "b[1]"'
	draw_line
}


function operator_ {
	local array1 array2
	declare -a array1
	declare -A array2
	draw_line
	((array1[0]++)); printf '%s => %s\n' '((array1[0]++))'  ${array1[0]}
	((array2[X]++)); printf '%s => %s\n' '((array2[X]++))'  ${array2[X]}
	draw_line
}


[[ $# -eq 0 ]] && { print_document; exit 0; }

if ! [[ $1 =~ ^[[:digit:]]+$ ]]; then
	unset array
	echo '====Convert Input Parameters to Array Then Print ======' 
	echo '--By $*------------------------------------------------'
	for i in $*; do
		array+=($i)
	done
	print_items_and_indexes

	echo '--By "$@"----------------------------------------------'
	unset array
	for i in "$@"; do
		array+=("$i")
	done
	print_items_and_indexes
else
	action=$1; shift
	case $action in
	0) initialize_                           ;;
	1) access_mthd1_                         ;;
	2) print_items_and_indexes               ;;
	3) operate_                              ;;
	4) pass_array_                           ;;
	5) string_to_array_                      ;;
	6) equal_                                ;;
	7) operator_                             ;;
	*) echo "Unsupported subcommand $action" ;;
	esac
fi

