/*
 * BombermanServerConnectionFactory.h
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#ifndef BOMBERMANSERVERCONNECTIONFACTORY_H_
#define BOMBERMANSERVERCONNECTIONFACTORY_H_

#include "BombermanServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"

class BombermanServerConnectionFactory : public Poco::Net::TCPServerConnectionFactory {
public:
	Poco::Net::TCPServerConnection * createConnection(const Poco::Net::StreamSocket & socket);


	BombermanServerConnectionFactory();
	virtual ~BombermanServerConnectionFactory();
};

#endif /* BOMBERMANSERVERCONNECTIONFACTORY_H_ */
