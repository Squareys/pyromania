#include "Explosion.h"
#include "Bomb.h"
#include "World.h"

Explosion::Explosion (Bomb* bomb) : Sprite(32, 32) {
	curFrame = 0;

	startTime = gameTime;

	setWorld(bomb->getWorld());
	setStrength(bomb->getStrength());
	setPosition(bomb->GetX(), bomb->GetY());

	expl_moved = 0;

	tx = (int) x/32;
	ty = (int) y/32;

	w = 32;
	h = 32;

	alive = true;
}

Explosion::~Explosion(){

}

void Explosion::Draw(){
	masked_blit(bmpFrames, dest, 0, 0, (int) x, (int) y, w, h);
}

void Explosion::update(){
	if (expl_moved < strength){
		if (expl_moved != 0){
			Map* map = world->getMap();

			if (map->isWalkable(tx+expl_moved, ty)){
				
			}

		}
		expl_moved++;
	} else {
		if (startTime + 1000 < gameTime) {
			alive = false;
		}
	}
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

