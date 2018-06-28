#ifndef GAME_H
#define GAME_H

#include <allegro.h>
#include "Map.h"
#include "UTil.h"

class Game {
	public:
		void play();

		Map* map;
		
		#ifndef SERVER
		
		void Draw();
		void Update();
	
		void load_images();

		#endif

		Game();
};

#endif
