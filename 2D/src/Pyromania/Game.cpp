#include "Game.h"

#include "Joypad.h"

//-----------------------------------------------------

Game::Game(){
	world = new World("Maps\\Map9.map");
	world->setDest(doubleBuffer);
}

Game::~Game(){

}

//-----------------------------------------------------

ClientGame::ClientGame() : Game(){
	loadImages();

	fps = 0;
}

ClientGame::~ClientGame(){
	unloadImages();
}

void ClientGame::play(){
	FrameCounter *Fcounter = new FrameCounter();
	Fcounter->setFPSvar(&fps);

	bool running = true;

	ticks = 0;
	syncTimer(&ticks);

	player = new Player(32, 32);
	player->setDest(doubleBuffer);
	player->setFrames(BMP_CHARACTER);

	if (!world->spawnPlayer(player)){
		allegro_message("Couldn't find a spawner for you :/ ");
		return;
	}

	Bomb* bomb = new Bomb();
	bomb->setDest(doubleBuffer);
	bomb->setFrames(BMP_BOMB);

	player->setBomb(bomb);
	
	while(running){
		while (ticks == 0){
			joypad->poll();

			if (joypad->button[Joypad::QUIT]){
				running = false;
			}
			if (joypad->button[Joypad::MOVEDOWN]) {
				player->setDirection(Player::DOWN);
				player->setMoving(true);
			} else if (joypad->button[Joypad::MOVEUP]){
				player->setDirection(Player::UP);
				player->setMoving(true);
			} else if (joypad->button[Joypad::MOVER]) {
				player->setDirection(Player::RIGHT);
				player->setMoving(true);
			} else if (joypad->button[Joypad::MOVEL]) {
				player->setDirection(Player::LEFT);
				player->setMoving(true);
			} else {
				player->setMoving(false);
			}

			if (joypad->button[Joypad::DROP] == Joypad::KS_DOWN ){
				player->dropBomb();
			}

			rest(1);
		}

		while (ticks > 0){
			int old_ticks = ticks;
			
			if (key[KEY_ESC]) running = false;

			update();

			ticks--;
			if (old_ticks <= ticks) { //logic taking too long
				textprintf_ex(doubleBuffer, font, 0, 10, makecol(255, 0, 0), -1,  "Taking too long!");
				break;
			}
		}

		Fcounter->update();
		draw();
		Fcounter->didFrame();
	}
	
}

void Game::update(){
	player->update();
	world->update();
}

void ClientGame::draw(){
	rectfill(doubleBuffer, 0, 0, doubleBuffer->w, doubleBuffer->h, makecol(190, 190, 190));
	world->Draw();
	player->Draw();
	textprintf_ex(doubleBuffer, font,  0, 0, makecol(255,255,255), -1,  "FPS: %i", fps);
	textprintf_ex(doubleBuffer, font, 80, 0, makecol(255,255,255), -1,  "Time: %i", gameTime);
	show();
}

void ClientGame::loadImages(){
	BMP_CHARACTER = load_bitmap("Images\\Charakter.bmp", NULL);
	BMP_BOMB   	  = load_bitmap("Images\\Bomb.bmp", NULL);

	world->load_tiles("Images\\Tiles.bmp");
}

void ClientGame::unloadImages(){
	secure_destroy_bitmap(BMP_CHARACTER);
	secure_destroy_bitmap(BMP_BOMB);
}

//-----------------------------------------------------
