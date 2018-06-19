/*
 * Entity.cpp
 *
 *  Created on: 06.05.2013
 *      Author: The Master
 */

#include "Entity.h"
#include "main.h"

Entity::Entity(float p_x, float p_y, Sprite* p_sprite) : m_x(p_x), m_y(p_y) {
	m_dirY = 0.0f;
	m_dirX = 0.0f;

	m_sprite = p_sprite;
}

Entity::~Entity() {
}

void Entity::setDirection(float p_dirX, float p_dirY){
	m_dirX = p_dirX;
	m_dirY = p_dirY;
}

void Entity::setSprite(Sprite* sprite){
	m_sprite = sprite;
}

void Entity::update(){
	m_x += m_dirX;
	m_y += m_dirY;

	if (m_x < 0) {
		m_x += screen->w;
	}

	if (m_y < 0) {
		m_y += screen->h;
	}

	if ( m_x > screen->w) {
		m_x -= screen->w;
	}

	if ( m_y > screen->h) {
		m_y -= screen->h;
	}

	m_sprite->update((int) m_x, (int) m_y);
}

float Entity::getPosX(){
	return m_x;
}

float Entity::getPosY(){
	return m_y;
}
