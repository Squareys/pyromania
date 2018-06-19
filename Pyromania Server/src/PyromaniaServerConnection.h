/*
 * PyromaniaServerConnection.h
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#ifndef PYROMANIASERVERCONNECTION_H_
#define PYROMANIASERVERCONNECTION_H_

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/SocketStream.h"
#include "GameLogic/Player.h"
#include "GameLogic/World.h"

class PyromaniaServerConnection : public Poco::Net::TCPServerConnection {
protected:
	Poco::Net::SocketInputStream sockIn;
	Poco::Net::SocketOutputStream sockOut;

	World* world;
	Player* player;
public:
	PyromaniaServerConnection(const Poco::Net::StreamSocket& s, World* w);
	virtual ~PyromaniaServerConnection();

	void run();

	Player* getPlayer();
};

#endif /* PYROMANIASERVERCONNECTION_H_ */
