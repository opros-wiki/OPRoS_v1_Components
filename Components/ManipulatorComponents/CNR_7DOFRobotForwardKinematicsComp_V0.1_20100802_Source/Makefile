CC	= g++
AR	= ar

CFLAGS	= -Wall -O2 -fomit-frame-pointer -fpermissive -fPIC -D_REENTRANT -D_OPROS_LINUX_
CFLAGS	+= -I../../../CommonLibrary/OPRoS_CDL/src
CFLAGS	+= -I../../Lib/DeviceAPI/include
CFLAGS	+= -I../../../CommonLibrary/BoostLinux/include
CFLAGS	+= -I../InverseKinematicsComp

SRCS	= CNR_7DOFRobotForwardKinematicsComp.cpp
SRCS	+= matrix.cpp
SRCS	+= vector.cpp

OBJS	= $(SRCS:.cpp=.o)

TARGET	= CNR_7DOFRobotForwardKinematicsComp.so

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
