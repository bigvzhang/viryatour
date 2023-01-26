#!/bin/bash
PROGDIR=$(dirname $0)
. $PROGDIR/shtour_common.sh
linesize=80

prompt 'Using <<-END'
cat <<END
If you indent your string with tabs (i.e., '\t'), the indentation
will be stripped out. If you indent with spaces, the indentation 
will be left in.
END
draw_line '.'

USAGE=$(cat <<-END
	This is line one.
    This is line two.
    This is line three.
END
)
echo "$USAGE"
draw_line

prompt "Using <<END"
USAGE=$(cat <<END
	This is line one.
    This is line two.
    This is line three.
END
)
echo "$USAGE"
draw_line
