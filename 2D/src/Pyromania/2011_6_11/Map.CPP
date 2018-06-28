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

#ifndef SERVER

int Map::load_tiles(char* filename){
	//Tiles = new BITMAP();
	Tiles = load_bitmap(filename, NULL);
	if (Tiles == NULL) return 1;
	return 0;
}

void Map::SetDest(BITMAP* DEST) {
	dest = DEST;
}

void Map::DrawTile(int tx, int ty, int type){
	if (type == -1) return;
	masked_blit(Tiles, dest, tilew*type, 0, tx*tilew, ty*tileh, tilew, tileh);
}

void Map::Draw(){
	int* bg = BG;
	int* mg = MG;	
	int* fg = FG;

	for (int ty = 0; ty < h; ty++){
		for (int tx = 0; tx < w; tx++){
			DrawTile(tx, ty, *bg);
			DrawTile(tx, ty, *mg);

			bg++; mg++; fg++;
		}
	}
}


#endif
