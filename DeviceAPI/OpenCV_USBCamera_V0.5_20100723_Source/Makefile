CC	= g++

SOLUTION_DIR	= ../../../..

CFLAGS	= -Wall -g -O2 -fomit-frame-pointer -D_REENTRANT -D_OPROS_LINUX_ -fPIC
CFLAGS	+= -I$(SOLUTION_DIR)/Component/Lib/DeviceAPI/include -I$(SOLUTION_DIR)/CommonLibrary/BoostLinux/include
CFLAGS	+= -I$(SOLUTION_DIR)/CommonLibrary/OPRoS_CDL/src
CFLAGS	+= -I$(SOLUTION_DIR)/CommonLibrary/OpenCV/OpenCV2.0_Linux/include/opencv

SRCS	= OpenCV_USBCamera.cpp

OBJS	= $(SRCS:.cpp=.o)

TARGET	= OpenCV_USBCamera.so

all : $(TARGET)

$(TARGET) : $(OBJS) 
	$(CC) -shared -W1 -o $(TARGET) $(OBJS)

%.o : %.cpp
	@echo "C++ Compiling $< ..."
	$(CC) -c $(CFLAGS) -o $@ $<

clean :
	rm -f $(TARGET) *.o

install:
	cp $(TARGET) /lib