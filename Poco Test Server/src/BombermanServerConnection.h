/*
 * BombermanServerConnection.h
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#ifndef BOMBERMANSERVERCONNECTION_H_
#define BOMBERMANSERVERCONNECTION_H_

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/SocketStream.h"

class BombermanServerConnection : public Poco::Net::TCPServerConnection {
private:
	Poco::Net::SocketStream socketStream;
public:
	BombermanServerConnection(const Poco::Net::StreamSocket& s);
	virtual ~BombermanServerConnection();

	void run();
};

#endif /* BOMBERMANSERVERCONNECTION_H_ */
