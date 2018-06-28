#include "Sprite.h"

Sprite::Sprite(int width, int height){
	frame_h = height;
	frame_w = width;

	oldTime = gameTime;	

	alive = true;
}

void Sprite::update(){
	return;
}

void Sprite::setPosition(float X, float Y){
	x = X;
	y = Y;
}

bool Sprite::checkCollision (Sprite* sprite){
	
	if (x+w < sprite->getX()) return false; 			//Off to the left
	if (x > sprite->getX() + sprite->getWidth()) return false; 	//off to the right

	if (y+h < sprite->getY()) return false; 			//off to the top
	if (y > sprite->getY() + sprite->getHeight()) return false; 	//off to the bottom

	return true; //Sprites are intersecting
}

#ifndef Server

void Sprite::Draw(){
	masked_blit(bmpFrames, dest, 0, frame_h, (int) x, (int) y, frame_w, frame_h);
}

void Sprite::setDest(BITMAP* DEST){
	dest = DEST;
}

void Sprite::setFrames(BITMAP* FRAMES){
	bmpFrames = FRAMES;
}

#endif

int Sprite::getHeight(){
	return h;
}

int Sprite::getWidth(){
	return w;
}

int Sprite::getX(){
	return (int) x;
}

int Sprite::getY(){
	return (int) y;
}

bool Sprite::isAlive(){
	return alive;
}

int Sprite::getType(){
	return type;
}

int Sprite::setType(int typ){
	type = typ;
}



