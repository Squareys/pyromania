#ifndef MAP_H
#define MAP_H

#include <allegro.h>
#include <string>

class Map {
	public:
		int width;
		int heigth;

		int tilew, tileh;

		int length;

		int walktiles;

		int* mapdata;
		int* walkable;
		
		enum Type {
			WALL, 
			SPAWNER, 
			BOX
		};

		int load_map(char* filename);

		#ifndef SERVER

		BITMAP* dest; //Desteny of drawing routine
		BITMAP* Tiles;

		void DrawTile(int tx, int ty, int type);
		void Draw();
		void SetDest(BITMAP* DEST);

		
		#endif

		Map(char* filename);
};

#endif
