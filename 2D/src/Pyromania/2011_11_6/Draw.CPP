#include "Game.h"

void Game::Draw(){
	rectfill(doubleBuffer, 0, 0, doubleBuffer->w, doubleBuffer->h, makecol(90, 90, 90));
	map->Draw();
	Player->Draw();
        show();
}
