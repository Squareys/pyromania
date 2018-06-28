#include "Game.h"

Game::Game(){
	map = new Map("Maps\\Map6.map");
	map->SetDest(doubleBuffer);
	map->load_tiles("Images\\Tiles.bmp");

	fps = 0;
}

#ifndef Server

void Game::play(){
	FrameCounter *Fcounter = new FrameCounter();
	Fcounter->setFPSvar(&fps);

	bool running = true;

	ticks = 0;
	syncTimer(&ticks);

	
	while(running){
		while (ticks == 0){
			if (key[KEY_ESC]) running = false;
			rest(1);
		}

		while (ticks > 0){
			int old_ticks = ticks;
			
			if (key[KEY_ESC]) running = false;

			ticks--;
			if (old_ticks <= ticks) { //logic taking too long
				textprintf_ex(doubleBuffer, font, 0, 10, makecol(255, 0, 0), -1,  "Taking too long!");
				break;
			}
		}

		Fcounter->update();

		Draw();
		Fcounter->didFrame();
	}
	
}

#else
void Game::play(){

}
#endif

void Game::Draw(){
	map->Draw();
	textprintf_ex(doubleBuffer, font,  0, 0, makecol(255,255,255), -1,  "FPS: %i", fps);
	textprintf_ex(doubleBuffer, font, 80, 0, makecol(255,255,255), -1,  "Time: %i", gameTime);
	show();
}

