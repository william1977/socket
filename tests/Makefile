CFLAGS+= -I ../include
CXXFLAGS+= -I ../include
#LDFLAGS+=-static

SOURCES := ../src/wrapper/socket.o
SOURCES += ../src/wrapper/select.o
SOURCES += ../src/wrapper/poll.o
SOURCES += ../src/wrapper/epoll.o

TARGET1=socket_server_test
TARGET2=socket_client_test

TARGETS:=$(TARGET1)
TARGETS+=$(TARGET2)
TARGETOBJS=`echo "$(TARGETS) " | sed 's/ /.o /g'`

all:prep $(TARGETS)
$(TARGET1):$(TARGET1).o $(SOURCES)
$(TARGET2):$(TARGET2).o $(SOURCES)

clean:
	rm $(TARGETS)
	echo $(TARGETOBJS) | xargs rm

prep:
	echo $(TARGETS)
	echo $(TARGETOBJS)
	echo $(SOURCES)
	echo "begin make ......"

