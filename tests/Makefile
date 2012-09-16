CFLAGS+= -I ../include
CXXFLAGS+= -I ../include
#LDFLAGS+=-static

TARGET1=socket_server_test
TARGET2=socket_client_test

TARGETS:=$(TARGET1)
TARGETS+=$(TARGET2)
all:compile $(TARGETS)

SOURCES := ../src/wrapper/socket.o
SOURCES += ../src/wrapper/select.o
SOURCES += ../src/wrapper/poll.o
SOURCES += ../src/wrapper/epoll.o

$(TARGETS):$(SOURCES)

TARGETSOBJ:=$(TARGET1).o
TARGETSOBJ+=$(TARGET2).o
compile:$(TARGETSOBJ)

clean:
	rm $(TARGETSOBJ) $(TARGETS)
