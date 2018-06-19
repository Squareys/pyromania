/*
 * Enemy.h
 *
 *  Created on: 06.05.2013
 *      Author: The Master
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "Entity.h"

class Enemy: public Entity {
public:
	Enemy(float p_x, float p_y, Sprite* sprite);
	virtual ~Enemy();

	void setTarget(Entity* entity);
	void update();

protected:
	Entity* m_target;
};

#endif /* ENEMY_H_ */
