/*
 * PyromaniaGameScene.h
 *
 *  Created on: 06.08.2013
 *      Author: The Master
 */

#ifndef PYROMANIAGAMESCENE_H_
#define PYROMANIAGAMESCENE_H_

#include "Scene.h"

#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"

#include "Joypad.h"

#include "GameLogic/World.h"

class PyromaniaGameScene: public Scene {
protected:
	Poco::Net::SocketAddress socketAddress;
	Poco::Net::StreamSocket socket;
	Poco::Net::SocketOutputStream sockOut;
	Poco::Net::SocketInputStream sockIn;

	int lastSendTime;
	int amount;
	int amountSent;

	World* world;
	Joypad* joypad;
	Player* player;

	void handleInput();
public:
	PyromaniaGameScene(irr::scene::ISceneManager *sm, irr::gui::IGUIEnvironment* ge, Joypad* jp, ResourceManager* rm, Poco::Net::SocketAddress sa);
	virtual ~PyromaniaGameScene();

	void prepare();
	void update(int time);
};

#endif /* PYROMANIAGAMESCENE_H_ */
