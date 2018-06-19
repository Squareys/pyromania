/*
 * BombermanServerConnection.cpp
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#include "BombermanServerConnection.h"
#include "Poco/StreamCopier.h"

using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnection;
using Poco::Net::SocketStream;

#include <iostream>

using namespace std;

BombermanServerConnection::BombermanServerConnection(const StreamSocket& s) : TCPServerConnection(s), socketStream(s)
{

}

BombermanServerConnection::~BombermanServerConnection()
{
}

void BombermanServerConnection::run()
{
	cout << "Request from " + this->socket().peerAddress().toString() << ": " << endl;

	int size = socket().getReceiveBufferSize();

	char buffer[size];

	socket().receiveBytes(&buffer, size);

	cout << buffer << endl;

	if (strcmp(buffer, "UPDATE\r\n") == 0) {
		std::string dt("Squareys AT 4,5");
						dt.append("\r\n");
			socket().sendBytes(dt.data(), (int) dt.length());
	} else {
		std::string dt("Changed Direction");
						dt.append("\r\n");
			socket().sendBytes(dt.data(), (int) dt.length());
	}


}
