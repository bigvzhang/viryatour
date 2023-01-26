#!/bin/bash
PROGDIR=$(dirname $0)
. $PROGDIR/shtour_common.sh
linesize=125


prompt "Remove the carriage in the bash"
echo 'Command => A=${A%$\r}'
A="abcd"
B=${A%$'\r'}
echo "$A => $B"
echo 'Command => A=${A%?} <== remove last character'
draw_line

prompt "Remove Carriage Return character with sed"
echo 'sed -i s/\r// filename <== Notice -i option will replace the source file'

prompt "Remove carriage return with tr"
echo "tr -d '\r' < file_with_carriagereturns > file_without_carriage_returns"

prompt "Remove carriages withawk(pattern scanning and processing language)"
echo 'awk "sub($, \r)" inputf_with_crs.txt > outputf_without_crs.txt'

prompt "Delete r CR with VIM editor"
echo ':%s/\r//g'

prompt "Converting  file DOS / UNIX OSes with dos2unix and unix2dos command line tools"
echo "dos2unix filename"

draw_line
echo "Reference http://www.pc-freak.net/blog/remove-carriage-return-from-string-of-file-linux-windows-with-sed-bash-awk-tr-vim/"
draw_line
