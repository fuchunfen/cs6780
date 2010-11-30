all: KinectCapture ConvertCaptures MakePairs InjectDepth ConvertDepths

KinectCapture: libfreenect.a capture.o glview.o
	g++ -g capture.o glview.o -L. -lfreenect -lGL -lGLU -lglut -lusb-1.0 -lcv -lhighgui -o KinectCapture

glview.o: glview.c capture.h libfreenect.h
	g++ -g -Wall -Werror glview.c -I/usr/include/libusb-1.0 -c -o glview.o

capture.o: libfreenect.h capture.cpp
	g++ -g -Wall -Werror -I. -I/usr/include/libusb-1.0 capture.cpp -c -o capture.o

ConvertCaptures: convert_captures.o
	g++ convert_captures.o -lcv -lhighgui -o ConvertCaptures

convert_captures.o: convert_captures.cpp 
	g++ convert_captures.cpp -c -o convert_captures.o -g

ConvertDepths: convert_depths.o
	g++ convert_depths.o -lcv -lhighgui -o ConvertDepths

convert_depths.o: convert_depths.cpp
	g++ convert_depths.cpp -c -o convert_depths.o -g

MakePairs: make_pairs.o
	g++ make_pairs.o -o MakePairs

make_pairs.o: make_pairs.cpp
	g++ make_pairs.cpp -c -o make_pairs.o -g

InjectDepth: inject_depth.o
	g++ inject_depth.o -o InjectDepth

inject_depth.o: inject_depth.cpp
	g++ inject_depth.cpp -c -o inject_depth.o -g

clean:
	rm -rf *.o KinectCapture ConvertCaptures MakePairs InjectDepth
