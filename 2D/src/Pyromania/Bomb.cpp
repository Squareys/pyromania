#include "Bomb.h"

Bomb::Bomb() : Sprite(32, 32) {
	curFrame = 0;

	countdown = 300;
	startTime = gameTime;

	exploded = false;

	alive = true;

	strength = 5;

	setType(BOMB);
}

Bomb::Bomb(Bomb* b) : Sprite(32, 32){
	dest = b->dest;
	bmpFrames = b->bmpFrames;

	strength = b->strength;

	Bomb();

	countdown = 300;
	startTime = gameTime;

	alive = true;
	exploded = false;
}

void Bomb::Draw(){
	if (exploded) return;	
	masked_blit(bmpFrames, dest, 0, 0, (int) x, (int) y, bmpFrames->w, bmpFrames->h);
}

void Bomb::update(){
	if (gameTime > (startTime + countdown) && !exploded) {
		explode();
	}
}

#include "World.h"
#include "Explosion.h" //for explode()

void Bomb::explode(){
	Explosion* expl = new Explosion(this);

	world->addExplosion(expl);

	exploded = true;
	alive = false;
}

void Bomb::setWorld(World* w){
	world = w;
}

World* Bomb::getWorld(){
	return world;
}

int Bomb::getStrength(){
	return strength;
}

bool Bomb::collision(Sprite* sprite) {
	return false; //don't collide
}
