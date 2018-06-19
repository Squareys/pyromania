/*
 * Sprite.cpp
 *
 *  Created on: 06.05.2013
 *      Author: The Master
 */

#include "Sprite.h"
#include "main.h"

//Contructor
Sprite::Sprite(int p_x, int p_y, int p_w, int p_h) : m_x(p_x), m_y(p_y), m_w(p_w), m_h(p_h){
	m_visible = true;
	m_color = SDL_MapRGB(screen->format, 255, 255, 255);
}

//Destructor
Sprite::~Sprite() {
}

void Sprite::draw(SDL_Surface* p_dest){
	SDL_Rect rect = {m_x, m_y, m_w, m_h};
	SDL_FillRect(p_dest, &rect, m_color);
}

void Sprite::update(int p_x, int p_y){
	m_x = p_x;
	m_y = p_y;
}

void Sprite::setVisible(bool p_flag){
	m_visible = p_flag;
}

bool Sprite::getVisible(){
	return m_visible;
}
