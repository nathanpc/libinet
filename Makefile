CXX = clang++
CXXFLAGS = -Wall -pthread
OBJ = src/sockets.o examples/example-socket.o
#OBJ = src/http.o examples/example-http.o

all: example-socket

example-socket: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

debug: CXXFLAGS += -g3 -DDEBUG
debug: example-socket

%.o: %.c
	$(CXX) $(CXXFLAGS) $<

clean:
	rm -rf src/*.o
	rm -rf example-*
