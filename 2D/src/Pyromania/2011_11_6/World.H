#ifndef WORLD_H
#define WORLD_H

#include <allegro.h>
#include <string>
#include <list>

#include "Sprite.h"
#include "Bomb.h"
#include "Explosion.h"
#include "Map.h"

using namespace std;

typedef list<Sprite*> SpriteList;
typedef SpriteList::iterator  SpriteItor;

class World {
	private:
		Map* map;
		SpriteList* entities;
		SpriteList* players;

		int addEntity(Sprite* s);
		int addPlayer(Sprite* s);

		#ifndef SERVER

		BITMAP* dest; //Desteny of drawing routine
		BITMAP* Tiles;//The Tile-Graphics
		BITMAP* BMP_EXPLOSION;

		int tilew, tileh; //Dimensions of a tile		

		#endif
	public:
		Map* getMap();

		int spawnCharakter(Charakter* charakter);
		int spawnPlayer (Charakter* Charakter);

		int addExplosion(Explosion* expl);
		int addBomb(Bomb* b);

		void update();

		#ifndef SERVER
		//Graphics functions 

		int load_tiles(char* filename);

		void DrawTile(int tx, int ty, int type);
		void Draw();
		void setDest(BITMAP* DEST);

		~World(); //only releases Tiles (Bitmap)
		
		#endif

		World(char* filename);
		
};		

#endif
