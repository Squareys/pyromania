/*
 * Entity.h
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <list>

class World;

class Entity {
protected:
	float x,y;

	World* world;

	void setWorld(World* w);

public:
	Entity();
	virtual ~Entity();

	virtual void update(int ticks) = 0;

	float 	getX();
	float 	getY();

	World*  getWorld();

	virtual char* serialize(int* size);
	virtual char* deserialize(char* s); //returns pointer to next unread data

	friend class World;
};

// EntityList definition //
typedef std::list<Entity*> EntityList;

#endif /* ENTITY_H_ */
