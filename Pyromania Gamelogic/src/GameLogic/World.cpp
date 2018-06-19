/*
 * World.cpp
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#include "World.h"

#define NULL 0

//-----------------------------------------------
// Constructors of World
//-----------------------------------------------

World::World() : entities(), players(), map() {
}

World::~World() {
}

//-----------------------------------------------
// Public Member Funktions of World
//-----------------------------------------------

int World::spawnEntity(Entity* e, float x, float y){
	e->x = x;
	e->y = y;

	entities.push_back(e);

	return 0;
}

int World::spawnTileEntity(TileEntity* e, int x, int y){
	return spawnEntity(e, (float) x, (float) y);
}

int World::spawnPlayer(Player* e, float x, float y){
	int r = spawnEntity(e, x, y);

	if (r == 0) {
		players.push_back(e);
		return 0;
	} else {
		return r;
	}
}

int World::spawnPlayer(Player* e){
	Tile t = map.getSpawnTile(players.size());

	int r = spawnEntity(e, (float) t.x, (float) t.y);

	if (r == 0) {
		players.push_back(e);
		return 0;
	} else {
		return r;
	}
}

void World::update(int ticks){
	for (EntityList::iterator itor = entities.begin();
			itor != entities.end(); itor++){
		Entity* e = (Entity*) *itor;

		e->update(ticks);
	}
}

TileMap* World::getMap(){
	return &map;
}

EntityList World::getPlayers() {
	return players;
}

void World::setMap(TileMap p_map){
	map = p_map;
}

void World::setMap(char* filename){
	map = TileMap(filename);
}

