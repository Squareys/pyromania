/*
 * ResourceManager.h
 *
 *  Created on: 06.08.2013
 *      Author: The Master
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <irrlicht.h>


class ResourceManager {
protected:
	irr::IrrlichtDevice* device;
	irr::video::IVideoDriver* driver;
	irr::scene::ISceneManager* sceneManager;

public:
	ResourceManager(irr::IrrlichtDevice* dev);
	virtual ~ResourceManager();

	irr::scene::IMesh* mesh_box;
	irr::scene::IMesh* mesh_corner;
	irr::scene::IMesh* mesh_mid;
	irr::scene::IMesh* mesh_wall_corner;
	irr::scene::IMesh* mesh_edge;
	irr::scene::IMesh* mesh_wall;
	irr::scene::IMesh* mesh_guy;

	irr::video::ITexture* texture_tiles;

	int load();
};

#endif /* RESOURCEMANAGER_H_ */
