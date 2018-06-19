/*
 * Player.h
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "MovingEntity.h"

class Player : public MovingEntity {
protected:
	char* 	name;
	int 	bombs;
	int 	bombPower;
	int		kills;

	int 	maxBombs;

	bool 	alive;
public:
	Player();
	virtual ~Player();

	void 	update(int ticks);

	void 	setName(char* nombre);
	void 	dropBomb();
	void 	setBombPower(int pow);

	char* 	getName();
	int 	getBombs();
	int		getBombPower();
	int 	getMaxBombs();
	int 	getKills();

	bool 	isAlive();

	virtual char* serialize(int* size);
	virtual char* deserialize(char* s);
};

#endif /* PLAYER_H_ */
