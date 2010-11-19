#!/bin/bash

cd bundler-v0.4-source
sudo cp bin/libANN_char.so /usr/lib
make
cd ..

cd OpenKinect-libfreenect-67c0d07/c
mkdir build
cd build
cmake ..
make
cd ../../..

cp OpenKinect-libfreenect-67c0d07/c/include/libfreenect.h KinectCapture
cp OpenKinect-libfreenect-67c0d07/c/build/lib/libfreenect.a KinectCapture

cd KinectCapture
make
cp InjectDepth ../bundler-v0.4-source/bin/
cd ..
