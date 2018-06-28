#include <allegro.h>

#include "Game.h"
#include "Util.h"

void debug(char* msg){
	allegro_message(msg);
}

void main (int, char**){
	int w = 800, h = 600;
	bool fullscreen = false;
	init (w, h, 60, fullscreen);

	Game* game = new Game();
	game->play();

	debug("Hello");
	
} END_OF_MAIN()
