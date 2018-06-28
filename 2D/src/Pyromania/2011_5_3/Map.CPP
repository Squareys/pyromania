#include "Map.h"

Map::Map(char* filename){
	load_map(filename);

	tilew = 32;
	tileh = 32;
}

int Map::load_map(char* filename){
	if (!exists(filename)) {
		allegro_message("Map doesn't exist!");
		return 1;
	}
	PACKFILE* map = pack_fopen(filename, F_READ);
	
	if (!map) {
		allegro_message("Couldn't read map-file!");
		return 1;
	}

	//Start reading file...
	width = pack_igetl(map);
	heigth= pack_igetl(map);

	walktiles = pack_igetl(map);

	walkable = new int[walktiles];

	pack_fread(walkable, sizeof(walkable), map);

	mapdata = new int[width*heigth];

	pack_fread(mapdata, sizeof(mapdata), map);

	//finished reading file

	pack_fclose(map);

	length = width*heigth;

	return 0;
}

#ifndef SERVER

void Map::SetDest(BITMAP* DEST) {
	dest = DEST;
}

void Map::DrawTile(int tx, int ty, int type){
	masked_blit(Tiles, dest, tilew*type, tileh, tx*tilew, tx*tileh, tilew, tileh);
}

void Map::Draw(){
	for (int i = 0; i < length; i++){
		int tx = i % width;
		int ty = (i-tx)/width;
		DrawTile(tx, ty, mapdata[i]);
	}
}


#endif
