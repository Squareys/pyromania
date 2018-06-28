#ifndef MAP_H
#define MAP_H

#include <allegro.h>
#include <string>

class Map {
	public:
		int w; //Width 
		int h; //Heigth

		int tilew, tileh; //Width\Height of a tile

		int length; //Legth of the map (w*h)

		int walknum; //Number of walkable tiles

		int* BG; //Background
		int* MG; //Midground
		int* FG; //Foreground
		int* walkable; //Walkable Tiles
		
		enum Type {
			WALL, 
			SPAWNER, 
			BOX
		};

		int load_map(char* filename); //Function to load a Map-File

		#ifndef SERVER
		//Graphics functions 

		int load_tiles(char* filename);

		BITMAP* dest; //Desteny of drawing routine
		BITMAP* Tiles;

		void DrawTile(int tx, int ty, int type);
		void Draw();
		void SetDest(BITMAP* DEST);
		
		#endif

		Map(char* filename);
};

#endif
