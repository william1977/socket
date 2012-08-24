CPPFLAGS := -I ../include

all : socket_server_test socket_client_test

clean : 
	find ../ -name "*.o" | xargs rm
	rm socket_server_test socket_client_test

SOURCES := ../src/wrapper/socket.o 

socket_server_test : socket_server_test.o $(SOURCES)
	g++ -o $@ $< $(SOURCES)

socket_client_test : socket_client_test.o $(SOURCES)
	g++ -o $@ $< $(SOURCES)