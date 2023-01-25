#!/bin/bash
<<DOCUMENT
NAME
    test_rsync 
SYNTAX
    test_rsync
    test_rsync <no>
TOUR
    0.   see the initially simulated files
    1.   rsync -a /dir1/  /dir2/           # both forms are correct 
         rsync -a /dir1/  /dir2
    2.   rsync -a /file1/ /file2/          # first form error, second ok
         rsync -a /file1/ /file2
    3.   rsync -au /dir1/  /dir2                  # update add
         rsync -a  /dir1/  /dir2                  # cover  add
    4.   rsync -au --existing        /dir1/ /dir  # update
         rsync -a  --ignore-existing /dir1/ /dir  # cover
    5.   rsync -a -f"+ */" -f"- *" dir1/ dir2     # Copy Directory Structure but Skip Files
    6.   rsync -navi  /dir1/ /dir2
   -9.   rsync -a --include '*/' --include '*202208*' --exclude '*'  /dir1/ /dir2
REFERENCE
    https://phoenixnap.com/kb/rsync-command-linux-examples
NOTICE
    this program must run in a tmp directory, such as '/tmp' or '/d/tmp'
DOCUMENT
source shtour_common.sh
try_help

function prepare_ {
	[[ $# -ne 2 ]] && exit 1		
	local name1=$1
	local name2=$2
	[[ $name1 =~ ^[[:alnum:]][[:alnum:]/]*$ ]] || abort "name of file must be ':alnum:[/]': $name1"
	[[ $name2 =~ ^[[:alnum:]][[:alnum:]/]*$ ]] || abort "name of file must be ':alnum:[/]': $name2"
	[[ -e $name1 ]] && { rm -rf $name1 || abort "cannot delete $name1" ; }
	[[ -e $name2 ]] && { rm -rf $name2 || abort "cannot delete $name2" ; }
	mkdir -p $name1 || abort "cannot create $name1"
	mkdir -p $name2 || abort "cannot create $name2"
	date +'[[%Y-%m-%d %H:%M:%S]] file1 - 0' > $name1/f1 ; touch -d "10 hours ago" $name1/f1
	date +'[[%Y-%m-%d %H:%M:%S]] file2 - 1' > $name1/f2 ; touch -d "8 hours ago"  $name1/f2
	date +'[[%Y-%m-%d %H:%M:%S]] file3 - 1' > $name1/f3 ; touch -d "6 hours ago"  $name1/f3
	date +'[[%Y-%m-%d %H:%M:%S]] x1    - 1' > $name1/x1 ; touch -d "24 hours ago" $name1/x1
	date +'[[%Y-%m-%d %H:%M:%S]] x2    - 1' > $name1/x2 ; touch -d "48 hours ago" $name1/x2

	#date +'[[%Y-%m-%d %H:%M:%S]] file1 - 0' > $name2/f1
	cp -p $name1/f1 $name2
	date +'[[%Y-%m-%d %H:%M:%S]] file2 - 2' > $name2/f2 ; touch -d "6 hours ago" $name2/f2
	date +'[[%Y-%m-%d %H:%M:%S]] file3 - 2' > $name2/f3 ; touch -d "8 hours ago" $name2/f3
	date +'[[%Y-%m-%d %H:%M:%S]] y1    - 2' > $name2/y1 ; touch -d "240 hours ago" $name2/y1
	date +'[[%Y-%m-%d %H:%M:%S]] y2    - 2' > $name2/y2 ; touch -d "480 hours ago" $name2/y2
}
function test_0_ {
	prepare_ testd1 testd2	
	draw_line; sync_cmp testd1/ testd2
	draw_line
}
function test_1_ {
	prepare_ testd1 testd2	
	prepare_ testd3 testd4	
	
	rsync -a testd1/ testd2/	
	rsync -a testd3/ testd4	
	draw_line ; sync_cmp testd1/ testd2
	draw_line3; sync_cmp testd3/ testd4
	draw_line
	explain "Conclusion:"
	explain "    'rsync dir1/ dir2/' == 'rsync dir1/ dir2'"
	draw_line
}
function test_2_ {
	prepare_ testd1 testd2	
	
	rsync -a testd1/f2/ testd2/g2/	
	rsync -a testd1/f3/ testd2/g3
	draw_line; sync_cmp testd1/ testd2
	draw_line
	explain "Conclusion:"
	explain "    not support 'rsync file1/ file2/' and will generate directory 'file2/'"
	explain "    not support 'rsync file1/ file2'"
	draw_line
}

function test_3_ {
	prepare_ testd1 testd2	
	prepare_ testd3 testd4	
	
	rsync -au testd1/ testd2/	
	rsync -a  testd3/ testd4	
	draw_line ; sync_cmp testd1/ testd2
	draw_line3; sync_cmp testd3/ testd4
	draw_line
	explain "Conclusion:                                "
	explain "    1. 'rsync -au ... != 'rsync -a'        "
	explain "     - 'rsync -au' will NOT copy old files "
	explain "     - 'rsync -a'  will     COPY old files " 
	explain "Practice:                                  "
	explain "    1. always use option '-u'              "
	draw_line
}
function run_cmp_ {
	prompt_t3 ${@}
	sync_cmp ${@}
}
function echo_run_ {
	prompt_t3 ${@}
	"$@"
}
function test_4_ {
	prepare_ testd1 testd2	
	prepare_ testd3 testd4	
	draw_line;  run_cmp_ testd1/ testd2

	rsync -au --existing        testd1/ testd2
	rsync -a  --ignore-existing testd3/ testd4
	draw_line3; run_cmp_ testd1/ testd2
	draw_line3; run_cmp_ testd3/ testd4
	draw_line ;
}
function test_5_ {
	prepare_ testd1 testd2	
	prepare_ testd1/level2 testd2/level2
	prepare_ testd1/level2/level3 testd2/level2/level3
	rm -rf testd3
	rm -rf testd4
	rsync -av -f"+ */" -f"- *" testd1/ testd3
	rsync -av -f"+ */" -f"- *" testd2/ testd4
	draw_line ; run_cmp_ testd1/ testd2
	draw_line3; run_cmp_ testd1/ testd3
	draw_line3; run_cmp_ testd2/ testd4
	draw_line ;
}
function test_6_ {
	prepare_ testd1 testd2	
	prepare_ testd1/level2 testd2/level2	
	draw_line; echo_run_ rsync -navi testd1/ testd2
	draw_line
}

[[ $PWD =~ ^.*/tmp$ ]] || abort "this program must run in a tmp directory: such as '/tmp' or '/d/tmp'"

[[ -z $1 ]] && { test_0_; exit 0; }
case $1 in
0) test_0_ ;;
1) test_1_ ;;
2) test_2_ ;;
3) test_3_ ;;
4) test_4_ ;;
5) test_5_ ;;
5) test_6_ ;;
*) abort "unsupport option: $1" ;;
esac

