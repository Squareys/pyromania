#include "World.h"

World::World(char* filename){
	tilew = 32;
	tileh = 32;

	entities = new SpriteList();
	players  = new SpriteList();

	map = new Map(filename, tilew, tileh);

	BMP_EXPLOSION = load_bitmap("Images\\Explosion.bmp", NULL);

	if (BMP_EXPLOSION == NULL) allegro_message("Couldn't load Explosion.bmp");
}

int World::addEntity(Sprite* s){
	if (s == NULL) return false;

	entities->push_back(s);
	return true;
}


int World::addPlayer(Sprite* s){
	if (s == NULL) return false;

	players->push_back(s);
	return true;
}

int World::spawnCharakter(Charakter* charakter){
	charakter->setWorld(this);
	addPlayer(charakter);

	return true;
}

int World::spawnPlayer(Charakter* charakter){
	int* fg = map->FG;

	for (int ty = 0; ty < map->h; ty++){
		for (int tx = 0; tx < map->w; tx++){
			if (*fg == Map::SPAWNER){
				charakter->setPosition(tx*tilew, ty*tileh);
				*fg = -1;
				return spawnCharakter(charakter);
			}
			fg++;
		}	
	}
	return false; //no spawners anywhere!?
}

int World::addExplosion(Explosion* expl){
	expl->setFrames(BMP_EXPLOSION);
	expl->setDest(dest);
	return addEntity(expl);
}

int World::addBomb(Bomb* b){
	int x = b->getX();
	int y = b->getY();

	int tx = 0;
	int ty = 0;
	
	//Now calculate distance to tiles and 
	//set Position on nearest tile

	int distX = x % tilew;
	int distY = y % tileh;

	if (distX == 0){
		tx = x / tilew;
	} else if (distX > (tilew / 2)){
		tx = (x + distX) / tilew;
	} else {
		tx = (x - distX) / tilew;
	}

	if (distY == 0){
		ty = y / tileh;
	}else if (distY > (tileh / 2)){
		ty = (y + distY) / tileh;
	} else {
		ty = (y - distY) / tileh;
	}

	b->setPosition(tx*tilew, ty*tileh);

	b->setWorld(this);
	return addEntity(b);
}

Map* World::getMap(){
	return map;
}

void World::update(){
	//update entities
	SpriteItor itor = entities->begin();
	SpriteItor end  = entities->end();

	for(; itor != end; itor++){
		Sprite* s = *itor;

		if (s->isAlive()){
			s->update();
		} else {
			entities->remove(s);
			itor--;
		}
	}

	//check Collisions for Players
	itor = players->begin();
	end  = players->end();

	for(; itor != end; itor++){
		Sprite* player = *itor;

		SpriteItor sitor = entities->begin();
		SpriteItor send  = entities->end();

		for(; sitor != send; sitor++){
			Sprite* s = *sitor;
			player->collision(s);
		}
	}	
}

int World::getTileH(){
	return tileh;
}

int World::getTileW(){
	return tilew;
}

bool World::destructTile(int tx, int ty){
	if (map->tileDestructable(tx, ty)){
		map->setTile(tx, ty, -1);
		return true;
	}
	return false;
}

#ifndef SERVER

int World::load_tiles(char* filename){
	Tiles = load_bitmap(filename, NULL);

	if (Tiles == NULL) return 1;
	return 0;
}

void World::setDest(BITMAP* DEST) {
	dest = DEST;
}

void World::DrawTile(int tx, int ty, int type){
	if (type == -1) return;
	masked_blit(Tiles, dest, tilew * type, 0, tx * tilew, ty * tileh, tilew, tileh);
}

void World::Draw(){
	int* bg = map->BG;
	int* mg = map->MG;	
	int* fg = map->FG;

	for (int ty = 0; ty < map->h; ty++){
		for (int tx = 0; tx < map->w; tx++){
			//DrawTile(tx, ty, *bg); //nothing !
			DrawTile(tx, ty, *mg); //Map and destructables
			//DrawTile(tx, ty, *fg); //Spawns

			bg++; mg++; fg++;
		}
	}

	//draw Sprites
	SpriteItor itor = entities->begin();
	SpriteItor end  = entities->end();

	for(; itor != end; itor++){
		Sprite* s = *itor;
		s->Draw();
	}

}


World::~World(){
	if (Tiles != NULL){
		destroy_bitmap(Tiles);
	}
}

#endif
