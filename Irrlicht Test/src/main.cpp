/*
 * main.cpp
 *
 *  Created on: 08.07.2013
 *      Author: Squareys
 */


#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace video;
using namespace scene;
using namespace gui;

int main() {

	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16, false, false, false, 0);

	if (!device){
		return 1;
	}

	device->setWindowCaption(L"Lego Minifig!");

	IVideoDriver* vidDriver = device->getVideoDriver();
	ISceneManager* scnMngr = device->getSceneManager();
	IGUIEnvironment* guiEnv = device->getGUIEnvironment();

	guiEnv->addStaticText(L"Hello World :)", rect<s32>(10, 10, 260, 50), false);


	//Load our Object
	IMesh* mesh = scnMngr->getMesh("models/LegoMinifig.obj");

	if(!mesh){
		device->drop();
		return 1;
	}

	IMeshSceneNode* node = scnMngr->addMeshSceneNode(mesh);

	if (node) {
        node->setMaterialFlag(EMF_LIGHTING, true);
    }

	scnMngr->addCameraSceneNode(0, vector3df(0,1,-4), vector3df(0,5,0));
	scnMngr->addLightSceneNode(0, vector3df(0.0, 1, -4));

	int lastFPS = 0;

	while(device->run()){
		vidDriver->beginScene(true, true, SColor(123, 123, 123, 123));

		scnMngr->drawAll();
		guiEnv->drawAll();

		node->setRotation(node->getRotation() + vector3df(0.0, 0.5, 0.0));
		vidDriver->endScene();

		 int fps = vidDriver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw tmp(L"It's a Legoman! [");
			tmp += vidDriver->getName();
			tmp += L"] fps: ";
			tmp += fps;

			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}
	}

	device->drop();

	return 0;
}
