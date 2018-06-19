/*
 * Entity.h
 *
 *  Created on: 06.05.2013
 *      Author: The Master
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "sprite.h"

class Entity {
public:
	Entity(float p_x, float p_y, Sprite* p_sprite);
	virtual ~Entity();

	void setDirection(float p_dirX, float p_dirY);

	float getPosX();
	float getPosY();
	void update();

	void setSprite(Sprite* sprite);
protected:
	float m_x;
	float m_y;

	float m_dirX;
	float m_dirY;

	Sprite* m_sprite;
};

#endif /* ENTITY_H_ */
