/*
 * MovingEntity.h
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#ifndef MOVINGENTITY_H_
#define MOVINGENTITY_H_

#include "Entity.h"

enum Direction {
	UP = 0,
	DOWN = 1,
	RIGHT = 2,
	LEFT = 3,
	STOP = 4
};

class MovingEntity : public Entity {
protected:
	int 	direction;
	float 	speed;
	bool	collides;

public:
	MovingEntity();
	virtual ~MovingEntity();

	void 	update(int ticks);

	void 	setDirection(int dir);
	void 	setSpeed(float s);
	void 	setCollides(bool c);
	void 	setPosition(float x, float y);

	bool    getCollides();
	int 	getDirection();
	float 	getSpeed();

	virtual char* serialize(int* size);
	virtual char* deserialize(char* s);

};

#endif /* MOVINGENTITY_H_ */
