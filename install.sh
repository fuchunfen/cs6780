#!/bin/bash

tar -zxvf 3rdparty/bundler-v0.4-source.tar.gz
unzip 3rdparty/siftDemoV4.zip
tar -zxvf 3rdparty/OpenKinect-libfreenect-67c0d07.tar.gz

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
