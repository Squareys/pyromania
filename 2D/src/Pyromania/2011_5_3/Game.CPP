#include "Game.h"

Game::Game(){
	map = new Map("Maps\\Map1.map");

	BITMAP* Tiles = load_bitmap("Images\\Tiles.bmp", NULL);
	map->SetDest(doubleBuffer);

	map->Tiles = Tiles;
}

void Game::play(){       
    bool needsRefresh = true;

    timerCounter = 0;
    syncTimer(&timerCounter);

    while (!key[KEY_ESC]) {

        if (timerCounter) {


           	do {
                	--timerCounter;
		}  while (timerCounter);

            needsRefresh = true;
        }

        if (needsRefresh) {
	    Draw();
            needsRefresh = 0;
        }
    }
        
}

