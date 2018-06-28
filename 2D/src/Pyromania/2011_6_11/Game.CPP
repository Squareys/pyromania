#include "Game.h"

Game::Game(){
	map = new Map("Maps\\Map6.map");
	map->SetDest(doubleBuffer);
	map->load_tiles("Images\\Tiles.bmp");

	fps = 0;
}

const int updates_per_sec = 60;

void Game::play(){
	bool running = true;
 
	int frames_done = 0;
	int old_time = 0;
 
	int frames_array[10];//an array to store the number of frames we did during the last 10 tenths of a second
	int frame_index = 0;//used to store the index of the last updated value in the array
	for(int ii = 0; ii < 10; ii++)
		frames_array[ii] = 0;//initialize the array to 0

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
				textprintf(doubleBuffer, font, 0, 10, makecol(255,255,255), "Taking too long!");
				break;
			}
		}

		if(gameTime >= old_time + 10)//i.e. a 0.1 second has passed since we last counted the frames
		{
			fps -= frames_array[frame_index];//decrement the fps by the frames done a second ago
			frames_array[frame_index] = frames_done;//store the number of frames done this 0.1 second
			fps += frames_done;//increment the fps by the newly done frames
 
			frame_index = (frame_index + 1) % 10;//increment the frame index and snap it to 10
 
			frames_done = 0;
			old_time += 10;
		}


		Draw();
		frames_done++;
	}
}

void Game::Draw(){
	map->Draw();
	textprintf(doubleBuffer, font, 0, 0, makecol(255,255,255), "FPS: %i", fps);
	textprintf(doubleBuffer, font, 80, 0, makecol(255,255,255), "Time: %i", gameTime);
	show();
}

