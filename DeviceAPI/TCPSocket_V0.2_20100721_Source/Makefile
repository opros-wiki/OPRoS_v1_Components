CC	= g++

SOLUTION_DIR	= ../../../..

CFLAGS	= -Wall -g -O2 -fomit-frame-pointer -D_REENTRANT -D_OPROS_LINUX_ -fPIC
CFLAGS	+= -I../../../Lib/DeviceAPI/include
CFLAGS	+= -I../../../../CommonLibrary/OPRoS_CDL/src
CFLAGS	+= -I../../../../CommonLibrary/BoostLinux/include

LDFLAGS	= -shared -W1

SRCS	= TCPSocket.cpp
SRCS	+= TCPSocketLinux.cpp

OBJS	= $(SRCS:.cpp=.o)

TARGET	= TCPSocket.so

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