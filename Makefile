CC = g++

CFLAGS = -g -Wall
OPENCV = $(shell pkg-config --cflags --libs opencv)

MAIN = main_exec
ARUCO = aruco_exec

all:$(MAIN)

$(MAIN): main.cpp
	$(CC) $(OPENCV) $(CFLAGS) -o $(MAIN) main.cpp

$(ARUCO): aruco_marker_detection.cpp
	$(CC) $(OPENCV) $(CFLAGS) -o $(ARUCO) aruco_marker_detection.cpp

clean:
	$(RM) $(MAIN) 
	$(RM) -r $(MAIN).dSYM