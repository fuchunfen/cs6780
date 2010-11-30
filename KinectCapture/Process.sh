#!/bin/bash

mkdir images
mkdir converted
rm -rf converted/*
rm -rf images/*
./ConvertCaptures
ls converted > converted.txt
./MakePairs
cp RunBundler.sh images
#matlab -glnx86 -nodisplay -r segment_image 
rm -rf pairs.txt
images=`find images/*.jpg`
for i in ${images[@]}
do
  base=`echo $i | sed 's/.jpg//'`
  echo $i $base'.txt' >> pairs.txt
done
./ReprojectDepth/ReprojectDepth ReprojectDepth/calib.txt pairs.txt auto
cd images
./RunBundler.sh
