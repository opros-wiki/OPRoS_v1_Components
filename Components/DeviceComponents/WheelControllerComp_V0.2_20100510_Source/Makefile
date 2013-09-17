CC	= g++
AR	= ar

CFLAGS	= -Wall -O2 -fomit-frame-pointer -fpermissive -fPIC -D_REENTRANT -D_OPROS_LINUX_
CFLAGS	+= -I../../Lib/DeviceAPI/include
CFLAGS	+= -I../../../CommonLibrary/OPRoS_CDL/src
CFLAGS	+= -I../../../CommonLibrary/BoostLinux/include

SRCS	= WheelControllerComp.cpp

OBJS	= $(SRCS:.cpp=.o)

TARGET	= WheelControllerComp.so

all : $(TARGET)

$(TARGET) : $(OBJS) 
	$(CC) -shared -W1 -o $(TARGET) $(OBJS)

#$(OBJS) : $(SRCS)
#	$(CC) $(CFLAGS) -c $(SRCS)

%.o : %.cpp
	@echo "C++ Compiling $< ..."
	$(CC) -c $(CFLAGS) -o $@ $<

clean :
	rm -f $(TARGET) *.o

install:
	cp $(TARGET) /lib
