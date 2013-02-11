CXX = clang++
CXXFLAGS = -Wall -pthread
OBJ = src/sockets.o src/http.o src/test-http.o

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
