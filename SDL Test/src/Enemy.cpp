/*
 * Enemy.cpp
 *
 *  Created on: 06.05.2013
 *      Author: The Master
 */

#include "Enemy.h"

#include <iostream>
#include <math.h>

Enemy::Enemy(float p_x, float p_y, Sprite* p_sprite) : Entity (p_x, p_y, p_sprite){
	m_target = NULL;
}

Enemy::~Enemy() {
	;
}

void Enemy::setTarget(Entity* entity) {
	m_target = entity;
}

void Enemy::update(){

	if (m_target == NULL) return;

	float diffX = m_target->getPosX() - getPosX();
	float diffY = m_target->getPosY() - getPosY();

	//normalize:
	float length = sqrt(diffX*diffX + diffY*diffY);

	setDirection(diffX / length, diffY / length);

	Entity::update();
}

