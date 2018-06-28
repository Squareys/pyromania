#ifndef GAME_H
#define GAME_H

#include <allegro.h>
#include "Util.h"
#include "FrameCounter.h"
#include "World.h"

class Game {
protected:
	BITMAP*	BMP_CHARACTER;
	BITMAP* BMP_BOMB;
public:
	virtual void play()=0;

	World* world;
	Player* player;

	virtual void draw()=0;
	void update();

	Game();
	virtual ~Game();
};

class ClientGame : public Game {
private:
	int fps; //Frames per second;
public:
	virtual void draw();
	virtual void play();

	void loadImages();
	void unloadImages();

	ClientGame();
	~ClientGame();
};

class ServerGame : Game {
private:
public:
	virtual void play();
	virtual void draw();

	ServerGame();
	~ServerGame();
};

#endif
