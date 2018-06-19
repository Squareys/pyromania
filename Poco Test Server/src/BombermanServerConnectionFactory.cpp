/*
 * BombermanServerConnectionFactory.cpp
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#include "BombermanServerConnectionFactory.h"

BombermanServerConnectionFactory::BombermanServerConnectionFactory() {

}

BombermanServerConnectionFactory::~BombermanServerConnectionFactory() {
}

Poco::Net::TCPServerConnection *BombermanServerConnectionFactory::createConnection(const Poco::Net::StreamSocket & socket)
{
	return new BombermanServerConnection(socket);
}
