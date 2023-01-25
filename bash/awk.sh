#!/bin/bash
PROGDIR=$(dirname $0)
. $PROGDIR/shtour_common.sh
linesize=80

draw_line '='
prompt "Using wak's ARGV array"
awk 'BEGIN{for(i=0; i <length(ARGV); i++) printf("%s %s\n",i, ARGV[i]);}' a b c


draw_line '='
prompt 'pass shell variables to awk using "-v" option on awk'
awk -va=1 -vb=2 'BEGIN{printf("a=%s b=%s\n", a, b);}'

draw_line 
prompt 'Referece http://daemonforums.org/showthread.php?t=6135'
draw_line
#prompt 'gensub demos'
cmd1=$(cat <<-END
awk -F\" '{print gensub(/\\/, "\\/", "g", \$2)}' Test.txt
END
)
prompt "[replace '\' by '/']"; echo $cmd1 

#draw_line '.'
cmd1=$(cat <<-END
echo "abc def 123 456" | awk '{print gensub(/(\S+) (\S+)/, "\\2 \\1", "g", \$0)}'
END
)
prompt "[switch word positions]"; echo  $cmd1
draw_line


echo "/A/B/C/file" | awk '{print $0 " ==**as dirname**=> " substr($0, 1,match($0, /\/[^\/]+$/))}' 
draw_line
