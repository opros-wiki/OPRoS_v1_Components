CC	= g++
AR	= ar

CFLAGS	= -Wall -O2 -fomit-frame-pointer -fpermissive -fPIC
CFLAGS	+= -I../../Lib/DeviceAPI/include
CFLAGS	+= -I../../../CommonLibrary/OPRoS_CDL/src
CFLAGS	+= -I../../../CommonLibrary/BoostLinux/include
CFLAGS	+= -I../GlobalMapComp
CFLAGS	+= -I../PathPlanningComp

LDFLAGS	= -shared -W1

LIBS	= ../../../CommonLibrary/OPRoS_CDL/release/libOPRoSCDL.a

SRCS	= KITECH_TopologicalPathPlanningComp.cpp

OBJS	= $(SRCS:.cpp=.o)

TARGET	= KITECH_TopologicalPathPlanningComp.so

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
