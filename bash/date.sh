#!/bin/bash
<<DOCUMENT
NAME
    test_date 
SYNTAX
    test_date
TOUR
    1. date           --date='Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
    2. date  --date='TZ="UTC" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"   << STANDARD 
       date --date='TZ="-08" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"    << NOT always work
       date --date='TZ="-07" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
       date --date='TZ="Z-06" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"   << works
       date --date='TZ="Z-05" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
       date --date='TZ="UTC-04" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z" << works
       date --date='TZ="UTC-03" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
       date --date='TZ="UTC-02" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
       date --date='TZ="UTC-01" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
       date --date="TZ='UTC-01' Sat Sep  4 13:05:02 2021" "+%Y-%m-%d %H:%M:%S %z" << BAD
    3. date --date='TZ="Asia/Shanghai" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
       date --date='TZ="America/Los_Angeles" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
DOCUMENT
source shtour_common.sh
try_help

function  test_1_ {
	date  --date='Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
}
function  test_2_ {
       date  --date='TZ="UTC" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"  
       date --date='TZ="-08" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"    # NOT always work
       date --date='TZ="-07" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
       date --date='TZ="Z-06" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"   # works
       date --date='TZ="Z-05" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
       date --date='TZ="UTC-04" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z" # works
       date --date='TZ="UTC-03" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
       date --date='TZ="UTC-02" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
       date --date='TZ="UTC-01" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
       echo date --date="TZ='UTC-01' Sat Sep  4 13:05:02 2021" "+%Y-%m-%d %H:%M:%S %z"  BAD
}
function  test_3_ {
       date --date='TZ="Asia/Shanghai" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
       date --date='TZ="America/Los_Angeles" Sat Sep  4 13:05:02 2021' "+%Y-%m-%d %H:%M:%S %z"
}

[[ -z $1 ]] && { print_document; exit 0; }
case $1 in
1) test_1_ ;;
2) test_2_ ;;
3) test_3_ ;;
*) abort "unsupport option: $1" ;;
esac

