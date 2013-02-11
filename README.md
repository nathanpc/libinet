# libinet++

A networking library for **humans** that code in C++.


## Another?

Yes, this is another networking library, but I promise, this one is different. This library was created for **humans** to use. cURL is great, but there's one huge problem with it: It's a C library, which means it looks like a alien designed the API (just like everything that involves C).

This library was built using one of the worst library ever invented in the face of this planet: The [GNU Sockets Library](http://www.cs.utah.edu/dept/old/texinfo/glibc-manual-0.02/library_15.html). This means I tortured myself to carve this library so you'll never have to torture yourself dealing with C libraries for networking.


## What's inside the package?

This library comes with an implementation of Sockets (`sockets.h`) and a HTTP client (`http.h`), which means you can extend it to suit your needs (remember to submit a Pull Request).


## Some examples

You can check out the examples in the `examples/` directory, but I've pasted them here for your convenience.

```c++
#include <iostream>
#include <string>

#include "libinet/sockets.h"
using namespace std;

bool socket_data_callback(string data) {
	// If something went wrong while you were parsing return false!
	cout << data << endl;
	return true;
}

int main(int argc, char *argv[]) {
	// Setup the socket and connect.
	Socket socket("localhost", 80, &socket_data_callback);
	socket.connect();

	// Send some information.
	socket.send_data("GET / HTTP/1.1\r\n");
	socket.send_data("Host: localhost\r\n\r\n");

	// Get the response.
	socket.receive();

	return 0;
}
```

```c++
#include <iostream>
#include <string>
#include <vector>

#include "libinet/http.h"
using namespace std;

int main(int argc, char *argv[]) {
	// Setup the connection.
	HTTP http("localhost", 80);
	HTTP_Response response;

	http.add_header("User-Agent", "libinet++/0.1");
	response = http.request("POST", "/test.php", "Testing the POST body stuff.");

	// Print the raw response.
	//cout << response.raw << endl;

	// Print the response status (hope it's 200 OK).
	cout << response.status_code << " " << response.status_message << endl;

	// Print the headers.
	for (size_t i = 0; i < response.headers.size(); i++) {
		vector<string> header = response.headers.at(i);
		cout << header.at(0) << ": " << header.at(1) << endl;
	}

	// Print body.
	cout << endl << response.body << endl;

	return 0;
}
```


## Contribute!

You think this library suck? You can fix it by submitting a Pull Request or a Issue!
