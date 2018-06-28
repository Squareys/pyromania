#ifndef MAP_H
#define MAP_H

#include <allegro.h>
#include <string>

class World;

class Map {
	private:
		int w; //Width 
		int h; //Heigth

		int tilew, tileh; //Width\Height of a tile

		int length; //Legth of the map (w*h)

		int walknum; //Number of walkable tiles
		int destrnum; //number of destructable tiles

		int load_map(char* filename); //Function to load a Map-File

		int* BG; //Background
		int* MG; //Midground
		int* FG; //Foreground
		int* walkable; //Walkable Tiles
		int* destructable; //Destructable Tiles

	public:	
		
		enum Type {
			WALL, 
			SPAWNER = 16, 
			BOX = 15
		};

		int  tileAt	 	 (int tx, int ty);
		bool isSolidTile (int tx, int ty);
		bool isSolid	 (int x , int y );

		bool tileDestructable(int tx, int ty);
		bool isDestructable  (int x , int y );

		void setTile(int tx, int ty, int type);
		void setTileFG(int tx, int ty, int type);
		void setTileAt(int x, int y, int type);

		Map(char* filename, int tw, int th);
		~Map();

		friend class World;
};		

#endif
