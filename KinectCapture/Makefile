all: KinectCapture ConvertCaptures MakePairs InjectDepth

KinectCapture: libfreenect.a capture.o
	g++ capture.o -L. -lfreenect -lusb-1.0 -lcv -lhighgui -o KinectCapture

capture.o: libfreenect.h capture.cpp
	g++ -I. -I/usr/include/libusb-1.0 capture.cpp -c -o capture.o

ConvertCaptures: convert_captures.o
	g++ convert_captures.o -lcv -lhighgui -o ConvertCaptures

convert_captures.o: convert_captures.cpp 
	g++ convert_captures.cpp -c -o convert_captures.o -g

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
