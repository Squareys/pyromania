/*
 * Scene.h
 *
 *  Created on: 06.08.2013
 *      Author: The Master
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <irrlicht.h>
#include "../ResourceManager.h"

class Scene {
protected:
	irr::scene::ISceneManager *sceneManager;
	irr::gui::IGUIEnvironment *guiEnv;
	ResourceManager *resourceManager;

public:
	Scene(irr::scene::ISceneManager *sm, irr::gui::IGUIEnvironment* ge, ResourceManager* rm);
	virtual ~Scene();

	virtual void prepare()=0;
	virtual void update(int time)=0;
};

#endif /* SCENE_H_ */
