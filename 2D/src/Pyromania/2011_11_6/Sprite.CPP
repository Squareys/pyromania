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

int Sprite::GetHeight(){
	return h;
}

int Sprite::GetWidth(){
	return w;
}

int Sprite::GetX(){
	return (int) x;
}

int Sprite::GetY(){
	return (int) y;
}

bool Sprite::isAlive(){
	return alive;
}



