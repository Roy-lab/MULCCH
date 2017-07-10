#!/bin/bash
mkdir output
fileList=clusterAssignList.txt
numGene=7185

for i in `seq 5`
do
echo input/clusterassign${i}.txt >> $fileList
done

./Eigen -l ${fileList} -d ${numGene} -n 0 -t 0 -b 0 -o output/result

