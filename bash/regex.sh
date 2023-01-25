#!/bin/bash
#if [[ $1 =~ ^[0-9]{8}$ ]]; then
#	echo "Matched"
#else
#	echo "DateFlag must as 20180305, But Input($1) not matched"
#	exit -1
#fi

if [[ $# -lt 2 ]]; then
    echo "Usage: $0 PATTERN STRINGS..."
    exit 1
fi
regex=$1
shift
echo "regex: $regex"
while [[ $1 ]]
do
    if [[ $1 =~ $regex ]]; then
        printf "%10s matches" "$1"
        i=1
        n=${#BASH_REMATCH[*]}
        while [[ $i -lt $n ]]
        do
            printf "(%s %s)" "[$i]" "${BASH_REMATCH[$i]}"
            let i++
        done
		printf "\n"
    else
        printf "%10s does not match\n" "$1"
    fi
    shift
done

