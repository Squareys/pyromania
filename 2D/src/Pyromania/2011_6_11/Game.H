#ifndef GAME_H
#define GAME_H

#include <allegro.h>
#include "Util.h"
#include "Map.h"

class Game {
	public:
		void play();

		Map* map;
		
		#ifndef SERVER

		int fps; //Frames per second;
		
		void Draw();
		void Update();
	
		void load_images();

		#endif

		Game();
};

#endif
