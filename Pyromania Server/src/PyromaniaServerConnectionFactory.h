/*
 * PyromaniaServerConnectionFactory.h
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#ifndef PYROMANIASERVERCONNECTIONFACTORY_H_
#define PYROMANIASERVERCONNECTIONFACTORY_H_

#include "PyromaniaServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"

#include "GameLogic/World.h"

class PyromaniaServerConnectionFactory : public Poco::Net::TCPServerConnectionFactory {
protected:
	World* world;

public:
	Poco::Net::TCPServerConnection *createConnection(const Poco::Net::StreamSocket & socket);


	PyromaniaServerConnectionFactory(World* w);
	virtual ~PyromaniaServerConnectionFactory();
};

#endif /* PYROMANIASERVERCONNECTIONFACTORY_H_ */
