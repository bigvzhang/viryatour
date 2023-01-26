#!/bin/bash
<<DOCUMENT
NAME
    expansion.sh - tour on shell expansions 
DEFINITION
    Expansion is performed on the command line AFTER it has been split into tokens. 
    There are seven kinds of expansion performed.
ENTRIES
    1. compare -- $* "$*" $@ "$@"           -- cmd options: such as 'a b c "1 2"'
    2. ${!name} ${!name@} ${!name*}
    3. passed_name=$1[@] ${!passed_name}    -- used to print an array
    4. ${var#x} and ${var%x}
       - ltrim: ${var#${var%%[![:space:]]*}}
       - rtrim: ${var%${var##*[![:space:]]}}
    -. brace expansion
       - echo a{b,c,d,e,f}H
       - echo a{b..g}H
       - echo a{02..5}H
       - ls -d /usr/{bin,lib}/exp*
       - echo /usr/{bin/{ls,awk},lib/{libxml*.*,how_ex}}
    -. tilde expansion
       - ~ == $HOME
       - ~USER == $HOME of USER
       - ~+    == $PWD
       - ~-    == $OLDPWD
       - ~N    == dirs +N                    # work with pushd and popd
         ~+N   == dirs +N; ~+0 == dirs +0
         ~-N   == dirs -N; ~-0 == dirs -0
    -. shell parameter expansion
       - basic form of parameter expansion
         - ${parameter}
         - $1, ${1}, ${10} are vaild; $10 could be invalid(according to doc)
       - indirect expansion
         - simple    - ${!varname} == ${var}
         - reference - ${!nameref} == varname
         - ${!prefix*}  == array of varname prefixed 
         - ${!name[@]}  == array index
       - general cases(word is subject to tilde|parameter|command|arithmetic expansion)
         - ${parameter:-word}   
         - ${parameter:=word}
         - ${parameter:?word}
         - ${parameter:+word}
         - ${parameter:offset}
           ${parameter:offset:length}
			   string=01234567890abcdefgh
			   ${string:7:0} == ""
			   ${string:7:2} == "78"
			   ${string:7:-2} == "7890abcdef"
			   ${string:7:0} == ""
			   ${string: -7:2} == "bc"
			   ${string: -7:-2} == "bcdef"
         - ${!prefix*}
           ${!prefix@}
         - ${!name[@]}
           ${!name[*]}
         - ${#parameter}
         - ${parameter#word}
           ${parameter##word}
         - ${parameter%word}
           ${parameter%%word}
         - ${parameter/pattern/string}
           ${parameter//pattern/string}
           ${parameter/#pattern/string}
           ${parameter/%pattern/string}
         - ${parameter^pattern}
           ${parameter^^pattern}
           ${parameter,pattern}
           ${parameter,,pattern}
         - ${parameter@operator}
    -. command expansion
       - $(command) == `command`
       - $(< file)  faster $(cat file)
    -. arithmetic expansion
       - $((i++))
    -. process expansion
       - wc <(ls) -c  # <(ls) is referred to using as a filename
    -. word split
       - TODO
    -. filename expansion
       - TODO
    -. quote removal
       - TODO
REFERENCE
    https://guide.bash.academy/expansions/
    https://stackoverflow.com/questions/369758/how-to-trim-whitespace-from-a-bash-variable
DOCUMENT

source shtour_common.sh


function test_1 { # $* "$*" $@ "$@"
	function count_of_args { echo "; repassed argc: $#; repassed argv: '$@' "; } 
	head5 'comparing $* "$*" $@ "$@"'; trace_src 1
	local IFS=' '	
	echo -n '   $*  == '$* 	    ;count_of_args $*
	echo -n '  "$*" == '"$*"  ;count_of_args "$*"
	echo -n '   $@  == '$@ 	    ;count_of_args $@
	echo -n '  "$@" == '"$@"  ;count_of_args "$@"	
	trace_src 1
	local IFS='~'	
	echo -n '   $*  == '$* 	    ;count_of_args $*
	echo -n '  "$*" == '"$*"  ;count_of_args "$*"
	echo -n '   $@  == '$@ 	    ;count_of_args $@
	echo -n '  "$@" == '"$@"  ;count_of_args "$@"	

	horizontal5
	explain '1. IFS will be used when concatenate "$*", such as "a b c" expand to "a~b~c"'
	explain '2. IFS will influence the arguments of calling function '
	horizontal5
}

function my_print_A { # print an array whose name is the first argument
	prompt3 "VarName: $1 <<Function A"
    name=$1[@]
    for i in "${!name}"; do
        echo "  $i"
    done
	#printf '  ~~name=>[%s] ${!name}=>[%s] ${!name@}=>[%s] ${!name*}=>[%s] \n' $name "${!name}" "${!name@}" "${!name*}"
	#echo "  ~~name=>[$name] \${!name}=>[${!name}] \${!name@}=>[${!name@}] \${!name*}=>[${!name*}]"
}
function my_print_B {  # a try of printting an array whose name is the first argument - bad
	prompt3 "VarName: $1 <<Function B"
    name=$1
    for i in "${!name[@]}"; do
        echo "  $i"
    done
}

function test_3 {
	head6 '${!name} -- print an array through its name'; trace_src 1,2 
	a=(x y z "a b")
	s="Hello"
	horizontal4 
	prompt3 'functionA: name=$1[@]; then loop ${!name} <= Correct'
	prompt3 'functionB: name=$1; then loop ${!name[@]} <= Negative' 
	horizontal4 
	my_print_A   a
	my_print_A   s 
	my_print_B   a
	my_print_B   s
	horizontal6
}

function my_print_C {
    for i in ${!x*}; do 
		name=$i
		echo "$name => ${!name}"
	done
}
function my_print_D {
    for i in ${!x@}; do 
		name=$i
		echo "$name => ${!name}"
	done
}
function my_print_E {
	prompt "vars whose names begin with '$1'" 
    eval names='(${!'$1'@})'
    for i in ${names[@]}; do 
		name=$i
		echo "  $name => ${!name}"
	done
}

function test_2 {
	head1 '${!name} ${!name@} ${!name*}'; trace_src +1,+4
	iloveworld=good
	iloveworldLevel2=ilove-better
	iloveworldLevel3=ilove-best
	name=iloveworld
	printf 'name            => "%s"\n'  $name
	printf '${iloveworld}   => "%s"\n'  ${iloveworld}
	printf '${!name}        => "%s" <= %s\n'  ${name} "Substituted"
	printf '${!iloveworld*} => "%s" <= whole\n' "${!iloveworld*}"
	printf '${!iloveworld@} => "%s" <= each\n' "${!iloveworld@}"

	x="!!!this is value from x!!!"
	x1="!!!this is value from x1!!!"
	x2="!!!This is value from x2!!!"
	x3="!!!This is value from x3!!!"
	prompt_t2 "loop"
	prompt 'loop ${!x*}'
	my_print_C
	prompt 'loop ${!x@}'
	my_print_D
	#prompt_t2 "in the sub function"
	my_print_E x
	my_print_E iloveworld
}

function test_4 {
	horizontal1; trace_src 1,2
	x="1234.abcd.efg"
	y="1234_abcd_efg"
	echo "%efg  ~ $x => ${x%efg}  $y=>${y%efg}"
	echo "%.efg ~ $x => ${x%.efg} $y=>${y%.efg}"
	echo "%.*   ~ $x => ${x%.*}"
	echo "%%.*  ~ $x => ${x%%.*}"
	echo "#*.   ~ $x => ${x#*.}"
	echo "##*.  ~ $x => ${x##*.}"
	echo "%[[:alpha:]]* ~ $y => ${y%[[:alpha:]]*}  # trim only one char"
	echo "#*[[:digit:]] ~ $y => ${y#*[[:digit:]]}  # trim only one char"

	head5 '{/#/}'
	x="0000012345"
	echo "x          => $x"
	echo '{x/#0/}    =>' ${x/#0/}
	echo '{x/#*(0)/} =>' ${x/#*(0)/}
	shopt -s extglob
	prompt_t2 '"shopt -s extglob" to enable the "*(p...)" composite pattern which maches zero or more occurrences of the given patterns'
	echo '{x/#*(0)/} =>' ${x/#*(0)/}
	echo '{x#*(0)}   =>' ${x#*(0)}  "  <= !!! the composite pattern doesn't work!"
	head5 'ltrim and rtrim'; trace_src 1
	var1="     abc 123     "
	echoe ${var1#${var1%%[![:space:]]*}} # ltrim
	echoe ${var1%${var1##*[![:space:]]}} # rtrim
	                                       trace_src 1
	var1="    *abc 123*    "             
	echoe ${var1#${var1%%[![:space:]]*}} # ltrim 
	echoe ${var1%${var1##*[![:space:]]}} # rtrim
	                                       trace_src 1
	var1="    -abc 123-    "
	echoe ${var1#${var1%%[![:space:]]*}} # ltrim
	echoe ${var1%${var1##*[![:space:]]}} # rtrim
	horizontal1
}


[[ $# -eq 0 ]] && { print_document; exit 0; }

action=$1; shift
case $action in
1) test_1  "$@"                     ;;
2) test_2  "$@"                     ;;
3) test_3  "$@"                     ;;
4) test_4  "$@"                     ;;
*) echo "Unsupported subcommand $action" ;;
esac
