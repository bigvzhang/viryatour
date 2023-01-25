#!/bin/bash
echo "Columns: $COLUMNS"
#stty size
tput cols
function term_size
{
    local i=0 digits='' tens_fmt='' tens_args=()
    for i in {80..8}
    do
        echo $i $(( i - 2 ))
    done
    echo "If columns below wrap, LINES is first number in highest line above,"
    echo "If truncated, LINES is second number."
    for i in {1..14}
    do
        digits="${digits}1234567890"
        tens_fmt="${tens_fmt}%10d"
        tens_args=("${tens_args[@]}" $i)
    done
    printf "$tens_fmt\n" "${tens_args[@]}"
    echo "$digits"
}
#term_size
