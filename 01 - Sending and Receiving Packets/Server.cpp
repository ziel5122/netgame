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

	// read in addresses.txt to get the set of addresses we will send packets to
	vector<Address> addresses;
	string line;
	ifstream file;
	file.open("addresses.txt");
	if (file.fail()) {
		printf("failed to open 'addresses.txt'\n");
		return 1;
	}

	while (!file.eof()){
		getline(file, line);
		int a,b,c,d,port;
		if (sscanf(line.c_str(), "%d.%d.%d.%d:%d", &a, &b, &c, &d, &port) == 5) {
			addresses.push_back(Address(a,b,c,d,port));
		}
	}
	file.close();

	// send and receive packets until the user ctrl-breaks...
	while (true) {
		const char data[] = "hello from the laptop";
		for (int i = 0; i < (int)addresses.size(); ++i) {
			socket.Send(addresses[i], data, sizeof(data));
		}

		wait_seconds( 1.0f );
	}

	// shutdown socket layer
	ShutdownSockets();
	return 0;
}
