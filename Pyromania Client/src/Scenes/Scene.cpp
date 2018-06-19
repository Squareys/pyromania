/*
 * Scene.cpp
 *
 *  Created on: 06.08.2013
 *      Author: The Master
 */

#include "Scene.h"

//--------------------------------------
// Constructors of Scene
//--------------------------------------

Scene::Scene(irr::scene::ISceneManager *sm, irr::gui::IGUIEnvironment* ge, ResourceManager* rm) {
	sceneManager = sm;
	guiEnv = ge;
	resourceManager = rm;
}

Scene::~Scene() {
}

//--------------------------------------
// Public Member functions of Scene
//--------------------------------------
