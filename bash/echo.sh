#!/bin/bash
function test_ls {
	A=`ls .bash_profile 2>/dev/null`
	if [ $? -eq 0 ]; then
		echo $A
		return 0
	fi
}

X=`test_ls`
echo "X:"$X
