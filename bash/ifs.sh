#!/bin/bash
<<DOCUMENT
NAME
    test_ifs - test IFS(internal field seperator) 
TOUR
    1. "$*" == "$1$IFS$2..."
DOCUMENT
source shtour_common.sh
try_help

function  test_1_ {
	[[ $# -lt 2 ]] && { echo "Please input at least two items to test!"; return 1; } 
	local IFS='~'
	echo "IFS: '$IFS'" 
	echo ' $*: '"$*" 
}


[[ -z $1 ]] && { print_document; exit 0; }
action=$1; shift
case $action in
1) test_1_ "$@" ;;
*) abort "unsupport action: $action" ;;
esac

