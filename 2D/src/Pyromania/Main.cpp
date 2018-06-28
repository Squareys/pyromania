#include <allegro.h>

#include "Game.h"
#include "Util.h"

#ifdef DEBUG
void debug(char* msg){
	allegro_message(msg);
}
#endif

void main (int, char**){
	int w = 800, h = 600;
	bool fullscreen = false;
	init (w, h, 60, fullscreen); //init Allegro -> UTIL.cpp

	ClientGame* game = new ClientGame();
	game->play();

#ifdef DEBUG
	debug("Bye!");
#endif

	done();
	
} END_OF_MAIN()
