#ifndef SPRITE_H
#define SPRITE_H

#include <allegro.h>
#include <string>

#include "Util.h"

class Sprite {
	protected:
		float x;
		float y;
		int w; //Width for collisions
		int h; //Heigth for collisions

		int frame_h; //h for drawing 
		int frame_w; //w for drawing
		int frames; //Number of Frames per Anim
		int animations; //Number of Anims in Frames-Bitmap
		int curAnim; //currently playing animation
		int curFrame;

		int oldTime; //GameTime last updatet

		bool alive;

	public:

		virtual void update()=0;

		int GetWidth();
		int GetHeight();

		int GetX();
		int GetY();

		void setPosition(float X, float Y);
		bool isAlive();

		#ifndef SERVER
		//Graphics functions 

		int load_frames(char* filename);

		BITMAP* dest; //Desteny of drawing routine
		BITMAP* bmpFrames;//The Frame-Graphics

		virtual void Draw();
		void setDest  (BITMAP* DEST);
		void setFrames(BITMAP* FRAMES);
		
		#endif

		Sprite(int width, int height);
};

class World; //Predeclaration. Declared in "World.h"	

class Charakter : public Sprite {
	protected:
		int  direction;
		bool moving;

		float speed; //pixels per GameTime (10 millis)

		World* world;
	public:
		//The Directions
		enum {
			UP    = 0, 
			DOWN  = 1, 
			RIGHT = 2, 
			LEFT  = 3
		};

		void setDirection(int dir); //set Direction of Sprite.
		void setMoving(bool mov);

		void setWorld(World* pworld);

		void update();

		#ifndef Server
		
		virtual void Draw();

		#endif

		Charakter(int width, int height, float in_speed);
};

class Bomb;

class Player : public Charakter {
	private:
		Bomb* bomb; //Bomb to duplicate to set
	public:
		int bombs; //Bombs left
		int lifes; //Lifes left

		void update();
		void setBomb(Bomb* b);
		bool dropBomb();

		Player(int width, int height);

};	

#endif
