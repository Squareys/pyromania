/*
 * PyromaniaServerConnectionFactory.cpp
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#include "PyromaniaServerConnectionFactory.h"

PyromaniaServerConnectionFactory::PyromaniaServerConnectionFactory(World* w) {
	world = w;
}

PyromaniaServerConnectionFactory::~PyromaniaServerConnectionFactory() {
}

Poco::Net::TCPServerConnection *PyromaniaServerConnectionFactory::createConnection(const Poco::Net::StreamSocket & socket)
{
	return new PyromaniaServerConnection(socket, world);
}
