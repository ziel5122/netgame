/*
	Sending and Receiving Packets Example
	From "Networking for Game Programmers" - http://www.gafferongames.com/networking-for-game-programmers
	Author: Glenn Fiedler <gaffer@gaffer.org>
*/

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Net.h"

using namespace std;
using namespace net;

int main(int argc, char * argv[]) {
	// initialize socket layer
	if (!InitializeSockets()) {
		printf("failed to initialize sockets\n");
		return 1;
	}

	// create socket
	int port = argc == 2 ? atoi(argv[1]) : 30000;
	printf("creating socket on port %d\n", port);

	Socket socket;
	if (!socket.Open(port)) {
		printf("failed to create socket!\n");
		return 1;
	}

	// send and receive packets until the user ctrl-breaks...
	char server_address[] = "10.0.0.8:30000";
	Address address;
	int a,b,c,d;
	if (sscanf(server_address, "%d.%d.%d.%d:%d", &a, &b, &c, &d, &port) == 5) {
		address = Address(a,b,c,d,port);
	}

	//const char data[] = "hello from the laptop";
	while (true) {
		//socket.Send(address, data, sizeof(data));

		while (true) {
			Address sender;
			unsigned char buffer[256];
			int bytes_read = socket.Receive(sender, buffer, sizeof(buffer));
			if (!bytes_read) break;
			printf("received packet from %d.%d.%d.%d:%d (%d bytes)\n",
						 sender.GetA(), sender.GetB(), sender.GetC(), sender.GetD(),
						 sender.GetPort(), bytes_read);
			printf("%s\n", buffer);
		}

		wait_seconds( 1.0f );
	}

	// shutdown socket layer
	ShutdownSockets();
	return 0;
}
