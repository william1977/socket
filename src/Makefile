CPPFLAGS := -I ../include

all : libsocket

clean : 
	find . -name "*.o" | xargs rm
	rm libsocket.a

SOURCES := wrapper/socket.o 

libsocket : $(SOURCES)
	ar rcs $@.a $<
	ranlib $@.a