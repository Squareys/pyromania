#ifndef GAME_H
#define GAME_H

#include <allegro.h>
#include "Util.h"
#include "FrameCounter.h"
#include "World.h"

class Game {
	public:
		void play();

		World* world;
		Player* player;
		
		#ifndef SERVER

		int fps; //Frames per second;
		
		void Draw();
		void update();
	
		void load_images();

		#endif

		Game();
};

#endif
