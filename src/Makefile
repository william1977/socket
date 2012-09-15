CFLAGS+= -I ../include
CXXFLAGS+= -I ../include
#LDFLAGS+=-static

TARGET=libsocket

all:$(TARGET) 

SOURCES := wrapper/socket.o
SOURCES += wrapper/select.o
SOURCES += wrapper/poll.o
SOURCES += wrapper/epoll.o

$(TARGET):$(SOURCES)
	ar rcs $@.a $(SOURCES)
	ranlib $@.a

clean:
	rm $(SOURCES) $(TARGET).a
