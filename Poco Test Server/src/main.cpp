/*
 * main.cpp
 *
 *  Created on: 29.07.2013
 *      Author: Squareys
 */

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/TCPServer.h"

#include "BombermanServerConnectionFactory.h"
#include <iostream>

using Poco::Net::ServerSocket;
using Poco::Net::TCPServer;

int main(int argc, char** argv) {
	// get parameters from configuration file
	unsigned short port = 12345;

	// set-up a server socket
	ServerSocket svs(port);
	// set-up a TCPServer instance
	TCPServer srv(new BombermanServerConnectionFactory(), svs);
	// start the TCPServer
	srv.start();
	// wait for CTRL-C or kill
	for(;;){

	}
	// Stop the TCPServer
	srv.stop();

	return 0;
}


