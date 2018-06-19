/*
 * Sprite.h
 *
 *  Created on: 06.05.2013
 *      Author: The Master
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL/SDL.h>

class Sprite {
public:
	Sprite(int p_x, int p_y, int p_w, int p_h);
	virtual ~Sprite();

	void draw(SDL_Surface* p_dest);
	void update(int p_x, int p_y);

	void setVisible(bool flag);
	bool getVisible();

protected:
	int m_x;
	int m_y;
	int m_w;
	int m_h;

	bool m_visible;

	int m_color;

};

#endif /* SPRITE_H_ */
