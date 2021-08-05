CC = g++

CFLAGS = -g -Wall
OPENCV = $(shell pkg-config --cflags --libs opencv)

TARGET = 3D_constructor

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(OPENCV) $(CFLAGS) -o $(TARGET) main.cpp

clean:
	$(RM) $(TARGET) 
	$(RM) -r $(TARGET).dSYM