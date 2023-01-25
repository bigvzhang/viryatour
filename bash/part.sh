#!/bin/bash
i=0
num=5
run_validate=0
for v in $*; do 
	a=${v##--}
	if [ "$a" == "$v" ]; then
		if [ $i == 0 ]; then
			file=$v
		elif [ $i == 1 ]; then	
			dest=$v
		fi
		i=$(($i+1))
	else
		if [ $a == "cksum" ]; then
			run_validate=1
		elif [[ $a =~ ^[0-9]+$ ]]; then
			num=$a
		else
			echo "Invalid Option($a)"
			exit -1
		fi
	fi
done

if [ -z "$file" -o -z "$dest" ]; then
	echo "$0 <filename> <destdest>"
	exit -1
fi

fname=`basename $file`


if [ ! -f $file ]; then
	echo "$file not exist!"
	exit -1
fi

if [ ! -d $dest ]; then
	if ! mkdir -p $dest; then	
		echo "Cannot Create dest $dest"
		exit -1
	fi
fi

size=`stat --format "%s" $file`
piece=$(($size / $num))
if [ $(($piece * 3 )) -ne $size ]; then
	piece=$((piece+1))
fi
printf "File size(%d), num(%d), piece(%d)\n" $size $num $piece
total=0
seq=1
error=0
while [ $total -lt $size ]
do
	if ! dd skip=$(($seq-1)) if=$file of=$dest/$seq count=1 bs=$piece 1>/dev/null 2>&1;  then
		error=1	
	fi
	total=$(($total+$piece))
	#echo $total $seq
	seq=$(($seq+1))
done
if [ $error -ne 0 ]; then
	echo "Found  error"
else
	seq=1
	while [ $seq -le $num ]
	do
		if [ $seq -eq 1 ]; then
			cat "$dest/$seq" > $dest/$fname
		else
			cat "$dest/$seq" >> $dest/$fname
		fi
		rm $dest/$seq
		seq=$(($seq+1))
	done
	if [ $run_validate -eq 1 ]; then
		cksum $file
		cksum $dest/$fname
	fi
fi

