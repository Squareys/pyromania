#include "Map.h"

Map::Map(char* filename, int tw, int th){
	load_map(filename);

	tilew = tw;
	tileh = th;
}

int Map::load_map(char* filename){
	if (!exists(filename)) {
		allegro_message("Map doesn't exist!");
		return 1;
	}
	PACKFILE* mapfile = pack_fopen(filename, F_READ);
	
	if (!mapfile) {
		allegro_message("Couldn't read map-file!");
		return 1;
	}

	//Start reading file...
	w = pack_igetl(mapfile); //Width
	h = pack_igetl(mapfile); //Height

	length = w*h;

	walknum  = pack_igetl(mapfile);
	walkable = new int[walknum];
	pack_fread(walkable, walknum*4, mapfile);

	BG = new int[length];
	MG = new int[length];
	FG = new int[length];

	pack_fread(BG, length*4, mapfile); //4 is sizeof(int)
	pack_fread(MG, length*4, mapfile);
	pack_fread(FG, length*4, mapfile);
	//finished reading file

	pack_fclose(mapfile);

	return 0;
}

/*********************************************************\
 * 	Tiles related Guardian functions		 *
 * 							 *
\*********************************************************/

int Map::tileAt(int tx, int ty){
	int index = (ty*w)+tx;
	return MG[index];
}

bool Map::TileWalkable(int tx, int ty){
	int tile = tileAt(tx, ty);

	if (tile == -1) return true;

	for ( int i = 0; i < walknum; i++){
		if (walkable[i] == tile){
			return true;
		}
	} 
	return false;
}

bool Map::isWalkable(int x, int y){
	return (TileWalkable(x/tilew, y/tileh));
}

void Map::setTile(int tx, int ty, int type){
	int index = (ty*w)+tx;
	MG[index] = type;
}

void Map::setTileFG(int tx, int ty, int type){
	int index = (ty*w)+tx;
	FG[index] = type;
}

void Map::setTileAt(int x, int y, int type){
	int tx = x/tilew;
	int ty = y/tileh;
	
	setTile(tx, ty, type);
}

/*********************************************************\
 * 	Destructor					 *
 * 	- releases BG/MG/FG/walkable			 *
\*********************************************************/

Map::~Map(){
	delete BG;
	delete FG;
	delete MG;
	delete walkable;
}
