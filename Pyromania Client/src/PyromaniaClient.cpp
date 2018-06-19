/*
 * PyromaniaClient.cpp
 *
 *  Created on: 06.08.2013
 *      Author: The Master
 */

#include "PyromaniaClient.h"
#include "Scenes/PyromaniaGameScene.h"

#include "Poco/Net/SocketAddress.h"
#include "Poco/Util/Util.h"

#include <iostream>

using namespace irr;

using namespace core;
using namespace video;
using namespace scene;
using namespace gui;

//---------------------------------------------------
// Constructors of PyromaniaClient
//---------------------------------------------------

PyromaniaClient::PyromaniaClient() {
	Joypad* joypad = new Joypad();

	device = createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16, false, false, false, joypad);

	if (!device){
		return;
	}

	device->setWindowCaption(L"Pyromania");

	driver 		= device->getVideoDriver();
	sceneManager= device->getSceneManager();
	guiEnv 		= device->getGUIEnvironment();

	resourceManager = new ResourceManager(device);

	curScene = new PyromaniaGameScene(sceneManager, guiEnv, joypad, resourceManager, Poco::Net::SocketAddress("localhost", 12345));
}

PyromaniaClient::~PyromaniaClient() {
	device->drop();
}

//---------------------------------------------------
// Public Member Functions of PyromaniaClient
//---------------------------------------------------
void PyromaniaClient::run(){
	if (!device){
		return;
	}

	resourceManager->load();
	curScene->prepare();

	int lastFPS = -1;

	Poco::Timestamp time = Poco::Timestamp();

	while(device->run()){
		renderScene();
		curScene->update(time.elapsed());
		time.update();

		int fps = driver->getFPS();

		if (fps != lastFPS){
			core::stringw caption = "Pyromania [FPS: ";
			caption += fps;
			caption += "]";
			device->setWindowCaption(caption.c_str());
			lastFPS = fps;
		}
	}
}

void PyromaniaClient::renderScene(){
	driver->beginScene(true, true, SColor(123, 123, 123, 123));

	sceneManager->drawAll();
	guiEnv->drawAll();

	driver->endScene();
}
