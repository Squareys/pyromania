#ifndef SPRITE_H
#define SPRITE_H

#include <allegro.h>
#include <string>

class Sprite {
	public:
		int x;
		int y;
		int w; //Width 
		int h; //Heigth

		int framew, frameh; //Width\Height of a tile
		int frames; //Number of Frames per Anim
		int animations; //Number of Anims in Frames-Bitmap
		int curAnim; //currently playing animation

		float speed; //pixels per GameTime (10 millis)

		int oldTime; //GameTime last updatet
		
		int direction;
		
		enum {
			UP, 
			DOWN, 
			RIGHT, 
			LEFT
		};

		void update();

		#ifndef SERVER
		//Graphics functions 

		int load_frames(char* filename);

		BITMAP* dest; //Desteny of drawing routine
		BITMAP* Frames;//The Frame-Graphics

		void Draw();
		void SetDest(BITMAP* DEST);
		
		#endif

		Sprite();
};	

class Player : public Sprite {
	public:
		int bombs; //etc

};	

#endif
