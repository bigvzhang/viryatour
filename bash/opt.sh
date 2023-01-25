#!/bin/bash
<<DOCUMENT
Usage
	Try the following when invoking this script:
		<cmd> -[a|b|c|r|h]
		<cmd> --[help|recursive]
		<cmd> -d
		<cmd> -d XYZ
		<cmd> -dXYZ
		<cmd> -z
	Explain the results of each of the above.
Reference
	https://stackoverflow.com/questions/402377/using-getopts-to-process-long-and-short-command-line-options
	https://unix.stackexchange.com/questions/162624/how-to-use-getopt-in-bash-command-line-with-only-long-options
DOCUMENT

source shtour_common.sh

  
PARSED_ARGV=`getopt -n tour_getopt -o "abcd:hr" --long help,recursive -- "$@" `
ERRORCODE=$?
if [ $ERRORCODE -ne 0 ]; then
	exit $ERRORCODE
fi

#echo $PARSED_ARGV

eval set -- "$PARSED_ARGV" #TODO, merged the two setences to one
                           #TODO, find out differenc, eval/NoEval, quote/NoQuote
PARSED_ARGS=("$@")
#PARSED_ARGS=($PARSED_ARGV)
for((i=0;i<${#PARSED_ARGS[@]};i++))
do
  case ${PARSED_ARGS[i]} in
	-h|--help) print_document; break;;
    -a) echo "Option \"a\"";;
    -b) echo "Option \"b\"";;
    -c) echo "Option \"c\"";;
    -r|--recursive) echo "Option \"${PARSED_ARGS[i]}\"";;
    -d) let i++; echo "Option \"d\" ${PARSED_ARGS[i]}";;
	--) ;;
     *) echo "Plain: [${PARSED_ARGS[i]}]" ;;
  esac
done


exit 0
