#!/bin/bash
<<DOCUMENT
TOURS
    1. set positional parameters
    2. set -o vi   - option vi off
       set +o vi   - option vi off
DOCUMENT
source shtour_common.sh
try_help


function set_of_ {
	echo
	echo "Positional parameters before  set \`uname -a\` :"
	echo "Command-line argument #1 = $1"
	echo "Command-line argument #2 = $2"
	echo "Command-line argument #3 = $3"


	set `uname -a` # Sets the positional parameters to the output
				   # of the command `uname -a`

	echo
	echo +++++
	echo $_        # +++++
	# Flags set in script.
	echo $-        # hB
	#                Anomalous behavior?
	echo

	echo "Positional parameters after  set \`uname -a\` :"
	# $1, $2, $3, etc. reinitialized to result of `uname -a`
	echo "Field #1 of 'uname -a' = $1"
	echo "Field #2 of 'uname -a' = $2"
	echo "Field #3 of 'uname -a' = $3"
	echo \#\#\#
	echo $_        # ###
	echo
}

function set_vi_ {
	set -o | grep "\<vi\>"
	set -o vi; set -o | grep "\<vi\>"
	set +o vi; set -o | grep "\<vi\>"
}

[[ $# -eq 0 ]] && exit
action=$1; shift
case $action in
	1) set_of_ "$@" ;;
	2) set_vi_ "$@" ;;
	*) exit 1       ;;
esac
