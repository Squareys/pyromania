/*
 * ResourceManager.cpp
 *
 *  Created on: 06.08.2013
 *      Author: The Master
 */

#include "ResourceManager.h"

using namespace irr;


ResourceManager::ResourceManager(IrrlichtDevice* dev) {
	device = dev;
	driver = dev->getVideoDriver();
	sceneManager = dev->getSceneManager();
}

ResourceManager::~ResourceManager() {

}

//-----------------------------------------------
// Public Member Functions of ResourceManager
//-----------------------------------------------
int ResourceManager::load() {
	//load models
	mesh_box 	= sceneManager->getMesh("models/Tile_Box.obj");
	mesh_corner = sceneManager->getMesh("models/Tile_Corner.obj");
	mesh_mid 	= sceneManager->getMesh("models/Tile_Mid.obj");
	mesh_wall_corner = sceneManager->getMesh("models/Tile_Wall_Corner.obj");
	mesh_edge 	= sceneManager->getMesh("models/Tile_Edge.obj");
	mesh_wall 	= sceneManager->getMesh("models/Tile_Wall.obj");

	mesh_guy    = sceneManager->getMesh("models/Little_Guy.obj");

	if(!mesh_guy || !mesh_box || !mesh_corner || !mesh_mid || !mesh_wall_corner || !mesh_edge || !mesh_wall){
		return false;
	}

	texture_tiles = driver->getTexture("textures/texture.png");

	if (!texture_tiles){
		return false;
	}

	return true;
}
