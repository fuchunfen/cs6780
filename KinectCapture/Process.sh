#!/bin/bash

mkdir images
mkdir converted
rm -rf converted/*
rm -rf images/*
./ConvertCaptures
ls converted > converted.txt
./MakePairs
cp RunBundler.sh images
cd images
./RunBundler.sh
