#!/bin/bash
function func01 {
	echo "1) for arg in [list] <= Simple for loops"
	for arg in "a" "b" "c"
	do
		echo $arg
	done
}
function func02 {
	echo "for loop with two parameters in each [list] element"
	for planet in "Mecury 36" "Venus 67" "Earch 93" "Mars 142"
	do
		set -- $planet
		echo "$1 $2.000.000 miles from the sun"
	done
}
function func03 {
	echo "Fileinfo: operating on a file list contained in a variable"
FILES=".bash_profle
.bash_profile
JOBS
/usr/bin/ls"
	for file in $FILES
	do	
		if [ -f $file ]; then
			echo $file is a file
		elif [ -d $file ]; then
			echo $file is a directory
		elif [ -e $file ]; then
			echo $file exists
		else
			echo "$file doesn't exist"
		fi
	done

}

function func04 {
	echo "Operating on files with a for loop, wildcast"
	for file in *
	do
		echo "$file in the current dir"
	done
}

function func05 {
	echo "for i in {1..5}"
	for i in {1..5}
	do
	   echo "Welcome i => $i"
	done
	echo 

	echo "for i in {1..10..2}"
	for i in {1..10..2}
	do
	   echo "Welcome i => $i"
	done

	echo 
	echo 'for i in $(seq 1 2 20)'
	for i in $(seq 1 2 20)
	do
	   echo "Welcome i => $i"
	done

	echo ""
	echo 'for (( c=1; c<=5; c++ ))'
	for (( c=1; c<=5; c++ ))
	do  
	   echo "Welcome c => $c"
	done
}


function print_help {
echo "=============================
Please input loop test number:
    1)Simple List
    2)List => for set -- 
    3)List Lines 
    4)*
    5){1..5} ((i=1;i<5;i++)) ...
"
}

if [ $# -eq 0 ]; then
	input_no=5
elif [ $1 == "help" -o $1 == "--help" ]; then
	print_help
	exit 0
else 
	input_no=$1
fi

case $input_no in
	1) func01 ;;
	2) func02 ;;
	3) func03 ;;
	4) func04 ;;
	5) func05 ;;
esac
