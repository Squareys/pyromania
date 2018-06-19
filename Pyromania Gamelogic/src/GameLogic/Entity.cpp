/*
 * Entity.cpp
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#include "Entity.h"

#include <cstdlib>
#include <string.h>

//--------------------------------------------------
// Contructors of Entity
//--------------------------------------------------

Entity::Entity() : x(0.0), y(0.0), world(NULL){

}

Entity::~Entity(){

}

//--------------------------------------------------
// Private Methods of Entity
//--------------------------------------------------

void Entity::setWorld(World* w){
	world = w;
}

//--------------------------------------------------
// Public Methods of Entity
//--------------------------------------------------

float Entity::getX(){
	return x;
}

float Entity::getY(){
	return y;
}

char* Entity::serialize(int* size){
	int s = sizeof(float) * 2;

	char* result = new char[s];
	char* pointer = result;

	memcpy(pointer, &x, sizeof(float));
	pointer += sizeof(float);
	memcpy(pointer, &y, sizeof(float));

	*size = s;

	return result;
}

char* Entity::deserialize(char* s){
	float* pointer = (float*) s;

	x = *pointer;
	pointer++;
	y = *pointer;
	pointer++;

	return (char*) pointer;
}

World* Entity::getWorld(){
	return world;
}
