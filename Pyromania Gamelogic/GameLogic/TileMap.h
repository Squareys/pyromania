/*
 * TileMap.h
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <vector>

enum TileIDs {
	TILE_AIR = -1,
	TILE_WALL_MID = 0,
	TILE_CUL = 1, //Corner upper left
	TILE_CUR = 2, //Corner upper right
	TILE_CLR = 3, //Corner lower right
	TILE_CLL = 4, //Corner lower left
	TILE_EDD = 5, //Edge down
	TILE_EDU = 6, //Edge up
	TILE_WALL_H = 7, //Wall horizontal
	TILE_WALL_V = 14, //Wall vertical
	TILE_EDL = 8, //Edge left
	TILE_EDR = 9, //Edge right
	TILE_WALL_CLL = 13, //Wall Corner lower left
	TILE_WALL_CUL = 10, //Wall Corner upper left
	TILE_WALL_CUR = 11, //Wall Corner upper right
	TILE_WALL_CLR = 12, //Wall Corner lower right
	TILE_BOX = 15,
	TILE_PLAYER_SPAWN = 16
};

struct TileType{
	short id;

	bool solid;
	bool destructable;
};

struct Tile {
	TileType* type;

	int x, y;
};

typedef std::vector<Tile> TileVector;

class World;

class TileMap {
	protected:
		int w; //Width
		int h; //Heigth

		int tilew, tileh; //Width\Height of a tile

		int length; //Legth of the map (w*h)

		int load_map(char* filename); //Function to load a Map-File

		short* BG; //Background
		short* MG; //Midground
		short* FG; //Foreground

		int numTileTypes;

		TileType* tiles; // List of TileTypes
		TileVector* spawnTiles;

		int getTileID (int x, int y);
		int findSpawnTiles();

	public:

		int		getWidth();
		int 	getHeight();
		int 	getLength();

		Tile  getTileAt	 (float x, float y);
		Tile  getTile 	 (int tx, int ty);

		bool isSolidTile (int tx, int ty);
		bool isSolid	 (float x, float y);

		Tile getSpawnTile(int nr);

		bool isDestructableTile	(int tx, int ty);
		bool isDestructable  	(float x , float y );

		void setTile(int tx, int ty, int type);
		void setTileFG(int tx, int ty, int type);
		void setTileAt(int x, int y, int type);

		char* serialize(int* size);
		void  deserialize(char* s);

		TileMap();
		TileMap(char* filename);
		~TileMap();

		friend class World;
};

#endif /* TILEMAP_H_ */
