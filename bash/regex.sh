#!/bin/bash
<<DOCUMENT
NAME 
    regex.sh
SYNOPSIS
    regex.sh [--bash] PATTERN STRINGS...
    regex.sh  --grep
    regex.sh  --awk   PATTERN STRINGS...
    
DOCUMENT
source shtour_common.sh
try_help



function bash_regex {
	[[ $# -lt 2 ]] && abort "invalid arguments; please check help"
	regex=$1
	shift
	echo "regex: $regex"
	while [[ -n $1 ]]
	do
		if [[ $1 =~ $regex ]]; then
			printf "  %-10s matches" "$1"
			i=1
			n=${#BASH_REMATCH[*]}
			while [[ $i -lt $n ]]
			do
				printf "(%s %s)" "[$i]" "${BASH_REMATCH[$i]}"
				let i++
			done
			printf "\n"
		else
			printf "  %-10s does not match\n" "$1"
		fi
		shift
	done
}

# from https://stackoverflow.com/questions/16172245
function grep_regex {
	matches=();

	# Used a "Process Substitution" because of the loop's subshell
	while read match
	do
		matches+=( "$match" );
	done \
	< <(
		printf '%s\n%s' \
			'somedata{a917am}some{8ka81a}data' \
			'awd123{ad123d}adad' \
			| grep -Eobn '\{[0-9a-z]{6}\}' # The magic is here
	);

	for (( i = 0; i < ${#matches[@]}; i++ ));
	do
		matchRaw="${matches[$i]}";
		match="${matchRaw#*\:}";
		match="${match#*\:}";
		matchLine="${matchRaw%%\:*}";
		matchChar="${matchRaw#*\:}";
		matchChar="${matchChar%%\:*}";
		matchLength="${#match}";

		printf 'Match #%s, line %2s, char %2s, length %2s: "%s"\n' \
			"$((i + 1))" \
			"$matchLine" \
			"$matchChar" \
			"$matchLength" \
			"$match";
	done
}

function awk_regex {
	[[ $# -lt 2 ]] && abort "invalid arguments; please check help"
	regex=$1
	shift
	echo "regex: $regex"
	while [[ -n $1 ]]
	do
		printf "  %-10s \n" "$1"
		awk -v regex=$regex '{s=$0; i=1; idx=0; 
		   while(i>0){ 
			   i=match(s, regex); 
			   if(i>0) {
					  idx += i;
					  printf("    %s %s\n", idx, RLENGTH); 
					  s=substr(s, i+RLENGTH);
					  idx += RLENGTH-1
			   }
		   }
		}' <<< $1
		shift
	done
}

action=bash
args=()
for ((i=1; i<=$#; i++)); do
	case ${!i} in
	--bash) action=bash      ;;
	--grep) action=grep      ;;
	--awk)  action=awk       ;;
	*)      args+=("${!i}")  ;;
	esac
done

case $action in
	bash) bash_regex  "${args[@]}"        ;;	
	grep) grep_regex  "${args[@]}"        ;;	
	awk)  awk_regex   "${args[@]}"        ;;	
	*)    abort "Invalid action: $action" ;;
esac
