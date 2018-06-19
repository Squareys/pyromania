/*
 * Player.h
 *
 *  Created on: 08.05.2013
 *      Author: The Master
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Entity.h"

class Player: public Entity {
public:
	Player(float p_x, float p_y, Sprite* sprite);
	virtual ~Player();

	void update();

	void setTarget(float p_x, float p_y);
};

#endif /* PLAYER_H_ */
