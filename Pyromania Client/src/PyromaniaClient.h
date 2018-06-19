/*
 * PyromaniaClient.h
 *
 *  Created on: 06.08.2013
 *      Author: The Master
 */

#ifndef PYROMANIACLIENT_H_
#define PYROMANIACLIENT_H_

#include <irrlicht.h>
#include <iostream>

#include "ResourceManager.h"
#include "Scenes/Scene.h"

class PyromaniaClient {
protected:
	irr::IrrlichtDevice *device;
	irr::video::IVideoDriver *driver;
	irr::scene::ISceneManager *sceneManager;
	irr::gui::IGUIEnvironment *guiEnv;

	ResourceManager* resourceManager;
	Scene* curScene;

	void renderScene();
public:
	PyromaniaClient();
	virtual ~PyromaniaClient();

	void run();
};

#endif /* PYROMANIACLIENT_H_ */
