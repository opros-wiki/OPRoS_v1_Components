CC	= g++
AR	= ar

CFLAGS	= -Wall -O2 -fomit-frame-pointer -fpermissive -fPIC -D_REENTRANT -D_OPROS_LINUX_
CFLAGS	+= -I../../Lib/DeviceAPI/include
CFLAGS	+= -I../../../CommonLibrary/OPRoS_CDL/src
CFLAGS	+= -I../../../CommonLibrary/BoostLinux/include
CFLAGS	+= -I../GlobalMapComp

LDFLAGS	= -shared -W1

LIBS	= ../../../CommonLibrary/OPRoS_CDL/release/libOPRoSCDL.a

SRCS	= bmp256.cpp
SRCS	+= GridBasedGlobalMap.cpp
SRCS	+= KITECH_GridBasedGlobalMapComp.cpp

OBJS	= $(SRCS:.cpp=.o)

TARGET	= KITECH_GridBasedGlobalMapComp.so

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
