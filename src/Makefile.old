CPPFLAGS := -I ../include

all : libsocket

clean : 
	find . -name "*.o" | xargs rm
	rm libsocket.a

SOURCES := wrapper/socket.o 
SOURCES += wrapper/select.o 
SOURCES += wrapper/poll.o 
SOURCES += wrapper/epoll.o 

libsocket : $(SOURCES)
	ar rcs $@.a $(SOURCES)
	ranlib $@.a
