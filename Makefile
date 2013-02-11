CXX = clang++
CXXFLAGS = -Wall #-pthread
SOCKET_OBJ = src/sockets.o examples/example-socket.o
HTTP_OBJ = src/sockets.o src/http.o examples/example-http.o

all: example-socket example-http

example-socket: $(SOCKET_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

example-http: $(HTTP_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

debug: CXXFLAGS += -g3 -DDEBUG
debug: all

%.o: %.c
	$(CXX) $(CXXFLAGS) $<

clean:
	rm -rf src/*.o
	rm -rf examples/*.o
	rm -rf example-*
