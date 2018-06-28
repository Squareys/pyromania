#include "Explosion.h"
#include "Bomb.h"
#include "World.h"

Explosion::Explosion (Bomb* bomb)  
   : Sprite(bomb->getWorld()->getTileW(), bomb->getWorld()->getTileH()) 
{

	curFrame = 0;

	startTime = gameTime;

	setWorld(bomb->getWorld());
	setStrength(bomb->getStrength());
	setPosition(bomb->getX(), bomb->getY());

	expl_moved = 0;

	tx = (int) x/world->getTileW();
	ty = (int) y/world->getTileH();

	w = 32;
	h = 32;

	alive = true;

	Tiles = new TileExplosionList();

	expanding = 0 | RIGHT | DOWN | UP | LEFT;

	setType(EXPLOSION);
}

Explosion::~Explosion(){

}

void Explosion::Draw(){
	TileExplosionList::iterator itor = Tiles->begin();

	for(; itor != Tiles->end(); itor++){
		TileExplosion te = *itor;
		masked_blit(bmpFrames, dest, 0, 0, te.tx * w, te.ty * h, w, h);
	}
}

void Explosion::update(){
	if (expl_moved < strength){
		if (expl_moved == 0) {
			TileExplosion texpl = {
				tx, ty, 0, 0
			};

			Tiles->push_back(texpl);
		} else {
			Map* map = world->getMap();

			if (expanding & RIGHT){
				TileExplosion texpl = {
					tx+expl_moved, ty, 0, 0
				};

				if (map->tileWalkable(tx+expl_moved, ty)) {
					Tiles->push_back(texpl);
				} else {
					if (world->destructTile(tx+expl_moved, ty)) {
						Tiles->push_back(texpl);
					}
					expanding ^= RIGHT;					
				}
			}

			if (expanding & LEFT) {
				TileExplosion texpl = {
					tx-expl_moved, ty, 0, 0
				};

				if (map->tileWalkable(tx-expl_moved, ty)) {
					Tiles->push_back(texpl);
				} else {
					if (world->destructTile(tx-expl_moved, ty)) {
						Tiles->push_back(texpl);
					}
					expanding ^= LEFT;					
				}
			}

			if (expanding & DOWN) {
				TileExplosion texpl = {
					tx, ty+expl_moved, 0, 0
				};

				if (map->tileWalkable(tx, ty+expl_moved)) {
					Tiles->push_back(texpl);
				} else {
					if (world->destructTile(tx, ty+expl_moved)) {
						Tiles->push_back(texpl);
					}
					expanding ^= DOWN;					
				}
			}

			if (expanding & UP) {
				TileExplosion texpl = {
					tx, ty-expl_moved, 0, 0
				};

				if (map->tileWalkable(tx, ty-expl_moved)) {
					Tiles->push_back(texpl);
				} else {
					if (world->destructTile(tx, ty-expl_moved)) {
						Tiles->push_back(texpl);
					}
					expanding ^= UP;					
				}
			}
		}
		expl_moved++;
	} else {
		if (startTime + 200 < gameTime) {
			alive = false;
		}
	}
}

bool Explosion::checkTileCollision(TileExplosion te, Sprite* sprite){
	int w = world->getTileW();
	int h = world->getTileH();

	int x = te.tx * w;
	int y = te.ty * h;

	if (x+w < sprite->getX()) return false; 			//Off to the left
	if (x > sprite->getX() + sprite->getWidth()) return false; 	//off to the right

	if (y+h < sprite->getY()) return false; 			//off to the top
	if (y > sprite->getY() + sprite->getHeight()) return false; 	//off to the bottom

	return true; //Sprites are intersecting
}

bool Explosion::checkCollision(Sprite* sprite){
	
	h = world->getTileH();
	w = world->getTileW();

	TileExplosionList::iterator itor = Tiles->begin();

	for(; itor != Tiles->end(); itor++){
		TileExplosion te = *itor;

		if (checkTileCollision(te, sprite) == true) return true;
	}

	return false;
}

bool Explosion::collision(Sprite* sprite){
	return checkCollision(sprite);
}

void Explosion::setWorld(World* w){
	world = w;
}

World* Explosion::getWorld(){
	return world;
}

void Explosion::setStrength(int s){
	strength = s;
}

