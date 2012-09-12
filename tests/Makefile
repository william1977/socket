CPPFLAGS := -I ../include -v

all : socket_server_test socket_client_test

clean : 
	find ../ -name "*.o" | xargs rm
	rm socket_server_test socket_client_test

SOURCES := ../src/wrapper/socket.o 
SOURCES += ../src/wrapper/select.o 
SOURCES += ../src/wrapper/poll.o 
SOURCES += ../src/wrapper/epoll.o 

socket_server_test : socket_server_test.o $(SOURCES)
	$(CXX) -static -v -o $@ $< $(SOURCES)

socket_client_test : socket_client_test.o $(SOURCES)
	$(CXX)  -static -v -o $@ $< $(SOURCES)
