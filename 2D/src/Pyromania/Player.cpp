#include "Sprite.h"
#include "World.h"
#include "Bomb.h"

Charakter::Charakter(int width, int height, float in_speed) : Sprite(width, height){
	setDirection(DOWN);
	setMoving(false);

	speed = in_speed;

	w = 30;
	h = 30;

	alive = true;
}

#ifndef Server
void Charakter::Draw(){
	masked_blit(bmpFrames, dest, 0, direction*frame_h, (int) x, (int) y, frame_w, frame_h);
}

#endif

void Charakter::setDirection(int dir){
	direction = dir;
} 

void Charakter::setMoving(bool mov){
	moving = mov;
}

void Charakter::setWorld(World* pworld){ //sets map to pointer to a Map
	world = pworld;
}

void Charakter::update(){
	float step = (speed * (gameTime-oldTime)); //Calculates how far Sprite has gone since last update

	if ( step > 1.0){
		if (moving){
			/* Save old Position in case of
			 * world collision
			 */
			float old_x = x;
			float old_y = y;

			/* move Sprite */
			switch(direction){
				case UP:    y -= step; break;
				case DOWN:  y += step; break;
				case RIGHT: x += step; break;
				case LEFT:  x -= step; break;
				case DEAD:  break;
				default: 	allegro_message("Application caused mixup in RAM\n or \"direction\" hasn\'t been initialized!");
						exit(1);
						break;
			}

			Map* map = world->getMap();

			if (!map->isWalkable((int) x, (int) y) || !map->isWalkable((int) x+w, (int) y+h) 
				|| !map->isWalkable((int) x+w, (int) y) || !map->isWalkable((int) x, (int) y+h)){
				x = old_x;			
				y = old_y;
			}
		} // ( if moving)
		oldTime = gameTime;
	}
}

bool Charakter::collision(Sprite* sprite) {
	if (checkCollision(sprite)){
		return true;
	} else {
		return false;
	}
}

Player::Player(int width, int height) : Charakter(width, height, 1.0){
	x = 0;
	y = 0;

	lives = 3;
	alive = true;
}

void Player::update(){
	float step = (speed * (gameTime-oldTime)); //Calculates how far Sprite has gone since last update

	if ( step > 1.0 && alive){
		if (moving){
			/* Save old Position in case of
			 * world collision
			 */
			float old_x = x;
			float old_y = y;

			/* move Sprite */
			switch(direction){
				case UP:    y -= step; break;
				case DOWN:  y += step; break;
				case RIGHT: x += step; break;
				case LEFT:  x -= step; break;
				case DEAD:  break;
				default: 	allegro_message("Application caused mixup in RAM\n or \"direction\" hasn\'t been initialized!");
						exit(1);
						break;
			}

			Map* map = world->getMap();

			if (!map->isWalkable((int) x, (int) y) || !map->isWalkable((int) x+w, (int) y+h) 
				|| !map->isWalkable((int) x+w, (int) y) || !map->isWalkable((int) x, (int) y+h)){
				x = old_x;			
				y = old_y;
			}
		} // ( if moving)
		oldTime = gameTime;
	}

	if (lives <= 0){
		alive = false;
		direction = DEAD;
	}
}

void Player::setBomb(Bomb* b){
	bomb = b;
}

bool Player::dropBomb(){
	if (!alive) return false;

	if (true){ //later bombs count
		Bomb* boom = new Bomb(bomb); //make copy of Bomb

		boom->setPosition(x, y);
		world->addBomb(boom); //add the copy to world
	} else {
		return false;
	}
	return true;
}

bool Player::collision(Sprite* sprite){
	if (!alive) return false;

	if ( sprite->collision(this) && sprite->getType() == EXPLOSION){
		lives--;
		return true;
	}

	return false;
}
