CPPFLAGS := -I ../include

all : socket_test

clean : 
	find ../ -name "*.o" | xargs rm
	rm socket_test

SOURCES := ../src/wrapper/socket.o 

socket_test : socket_test.o $(SOURCES)
	g++ -o $@ $< $(SOURCES)