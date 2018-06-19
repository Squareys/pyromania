/*
 * main.cpp
 *
 *  Created on: 29.07.2013
 *      Author: Squareys
 */


#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/StreamCopier.h"
#include <iostream>

int main(int argc, char** argv)
{
	Poco::Net::SocketAddress sa("localhost", 12345);
	Poco::Net::StreamSocket socket(sa);
	Poco::Net::SocketStream str(socket);

	str << "UPD" << "\r\n";
	str.flush();

	Poco::StreamCopier::copyStream(str, std::cout);

	return 0;
}


