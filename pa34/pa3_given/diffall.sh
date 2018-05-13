#!/usr/bin/env bash
allimgs="outHalf.png
outCopy.png
outRotated.png
outPruned.png
outEtc.png"

make -q
if [ $? -ne 0 ]
then
	make all
	if [ $? -ne 0 ]
	then
		exit -1
	fi
fi

./pa3 > pa3.out
diff pa3.out soln_pa3.out

for image in $allimgs
do
	diff $image soln_$image
done

