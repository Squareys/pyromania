/*
 * MovingEntity.cpp
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#include "MovingEntity.h"

#include <cstdlib>
#include <string.h>

#include "TileMap.h"
#include "World.h"

//--------------------------------------------------
// Contors of MovingEntity
//--------------------------------------------------

MovingEntity::MovingEntity() : Entity(), direction(STOP), speed(1.0), collides(true) {
}

MovingEntity::~MovingEntity() {

}

//--------------------------------------------------
// Public Methods of MovingEntity
//--------------------------------------------------

void MovingEntity::update(int ticks){
	float new_x = x;
	float new_y = y;

	float factor = ticks * 0.00001;

	if ( direction == DOWN ) {
		new_y += speed * factor;
	} else if ( direction == UP ) {
		new_y -= speed * factor;
	} else if ( direction == RIGHT ) {
		new_x += speed * factor;
	} else if ( direction == LEFT ) {
		new_x -= speed * factor;
	}

	if (collides) {
		//do collision stuff

		if (getWorld()->getMap()->isSolid(new_x, new_y) == true) {
			x = new_x;
			y = new_y;
		}

	} else {
		x = new_x;
		y = new_y;
	}
}

void MovingEntity::setDirection(int dir){
	direction = dir;
}

void MovingEntity::setSpeed(float s){
	speed = s;
}

void MovingEntity::setCollides(bool c){
	collides = c;
}

void MovingEntity::setPosition(float px, float py) {
	x = px;
	y = py;
}

bool MovingEntity::getCollides() {
	return collides;
}

int MovingEntity::getDirection(){
	return direction;
}

float MovingEntity::getSpeed(){
	return speed;
}

char* MovingEntity::serialize(int* size) {
	int old_s = 0;

	char* result = Entity::serialize(&old_s);
	int s = old_s + sizeof(int) + sizeof(float);

	realloc(result, s);

	char* pointer = result;
	pointer += old_s;

	memcpy(pointer, &direction, 4);
	pointer += 4; //sizeof(int)
	memcpy(pointer, &speed, sizeof(float));

	*size = s;
	return result;
}

char* MovingEntity::deserialize(char* s) {
	char* pointer = Entity::deserialize(s);

	direction = *((int*) pointer);
	pointer += 4; //sizeof(int)
	speed =*((float*) pointer);
	pointer += sizeof(float);

	return pointer;
}
