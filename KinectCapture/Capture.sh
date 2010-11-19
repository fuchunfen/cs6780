#!/bin/bash

mkdir images
mkdir captures
mkdir converted
rm -rf captures/*
rm -rf converted/*
rm -rf images/*
sudo ./KinectCapture
ls captures > files.txt
./ConvertCaptures
ls converted > converted.txt
./MakePairs
cp RunBundler.sh images
cd images
./RunBunlder.sh
