#ifndef BOMB_H
#define BOMB_H

#include <allegro.h>
#include <string>

#include "Sprite.h"

class Bomb : public Sprite {
	protected:
		int startTime;
		int countdown; //How long till Bomb Explodes

		int oldTime; //GameTime last updatet

		int strength;

		bool exploded;

		void explode();

		World* world;

	public:

		void   update();
		void   setWorld(World* w);
		World* getWorld();

		int getStrength();

		bool collision (Sprite* sprite);
		

		#ifndef SERVER
		//Graphics functions

		virtual void Draw();
		
		#endif

		Bomb();
		Bomb(Bomb* b);
};	


#endif
