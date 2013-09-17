CC	= g++
AR	= ar

CFLAGS	= -Wall -O2 -fomit-frame-pointer -fpermissive -fPIC -D_REENTRANT -D_OPROS_LINUX_
CFLAGS	+= -I../../../Lib/DeviceAPI/include
CFLAGS	+= -I../../../../CommonLibrary/OPRoS_CDL/src
CFLAGS	+= -I../../../../CommonLibrary/BoostLinux/include

LDFLAGS	= -shared -W1

LIBS	= 

SRCS	= Robotis_DynamixelCAN.cpp
SRCS	+= DynamixelCAN.cpp

OBJS	= $(SRCS:.cpp=.o)

TARGET	= Robotis_DynamixelCAN.so

all : $(TARGET)

$(TARGET) : $(OBJS) 
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o : %.cpp
	@echo "C++ Compiling $< ..."
	$(CC) -c $(CFLAGS) -o $@ $<

clean :
	rm -f $(TARGET) *.o

install:
	cp $(TARGET) /lib