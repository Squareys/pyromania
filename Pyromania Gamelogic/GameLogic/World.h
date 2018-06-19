/*
 * World.h
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "TileMap.h"
#include "Entity.h"
#include "TileEntity.h"
#include "Player.h"

class World {
private:
	EntityList entities;
	EntityList players;

	TileMap map;
public:
	World();
	virtual ~World();

	int spawnEntity(Entity* e, float x, float y);
	int spawnTileEntity(TileEntity* e, int x, int y);
	int spawnPlayer(Player* e, float x, float y);
	int spawnPlayer(Player* e);

	void update(int ticks);

	EntityList 	getPlayers();
	TileMap*	getMap();

	void setMap(TileMap p_map);
	void setMap(char* filename);
};

#endif /* WORLD_H_ */
