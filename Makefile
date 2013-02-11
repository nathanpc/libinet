CXX = clang++
CXXFLAGS = -Wall -pthread
OBJ = src/sockets.o examples/example-socket.o
#OBJ = src/http.o examples/example-http.o

all: test-http

test-http: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

debug: CXXFLAGS += -g3 -DDEBUG
debug: test-http

%.o: %.c
	$(CXX) $(CXXFLAGS) $<

clean:
	rm -rf src/*.o
	rm -rf test-http
