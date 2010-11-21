#!/bin/bash

mkdir captures
rm -rf captures/*
sudo ./KinectCapture
ls captures > files.txt
