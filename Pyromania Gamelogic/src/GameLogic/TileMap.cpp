/*
 * TileMap.cpp
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#include "TileMap.h"

#include <math.h>
#include <string.h>

//--------------------------------------------------------
// Constructors of TileMap
//--------------------------------------------------------

TileMap::TileMap() : spawnTiles() {
	MG = 0;
	FG = 0;
	BG = 0;

	tiles = 0;
	h = 0;
	w = 0;
	length = 0;

	numTileTypes = 0;

	tileh = 2;
	tilew = 2;
}

TileMap::TileMap(char* filename) {
	load_map(filename);
}

TileMap::~TileMap() {
}

//--------------------------------------------------------
// Public Member Functions of TileMap
//--------------------------------------------------------

int TileMap::getWidth() {
	return w;
}

int TileMap::getHeight() {
	return h;
}

int TileMap::getLength(){
	return length;
}

Tile TileMap::getSpawnTile(int nr){
	return spawnTiles->at(nr);
}

Tile TileMap::getTileAt(float x, float y){
	return getTile(floor(x), floor(y));
}

Tile TileMap::getTile (int x, int y) {
	int id = getTileID(x, y);

	if ( id == -1){
		Tile t = {NULL, x, y};
		return t;
	} else {
		Tile t = {&tiles[id], x, y};
		return t;
	}
}

bool TileMap::isSolid(float x, float y){
	return isSolidTile(floor(x), floor(y));
}

bool TileMap::isSolidTile(int tx, int ty){
	return getTile(tx, ty).type->solid;
}

bool TileMap::isDestructable (float x, float y){
	return isDestructableTile(floor(x), floor(y));
}

bool TileMap::isDestructableTile(int tx, int ty){
	return getTile(tx, ty).type->destructable;
}

char* TileMap::serialize(int* size){
	int numNonSolid = 0;
	int numDestruct = 0;

	short destructables[numTileTypes];
	short nonSolidTiles[numTileTypes];

	for ( int i = 0; i < numTileTypes; i++){
		TileType t = tiles[i];

		if (!t.solid){
			nonSolidTiles[numNonSolid++] = i;
		}

		if (t.destructable){
			destructables[numDestruct++] = i;
		}
	}

	int s = 5 + 2 * (numNonSolid + numDestruct + length*3);
	char* result = new char[s];

	result[0] = (char) w;
	result[1] = (char) h;
	result[2] = (char) numTileTypes;
	result[3] = (char) numNonSolid;
	result[4] = (char) numDestruct;

	char* pointer = result;
	pointer += 5;

	memcpy(pointer, nonSolidTiles, 2*numNonSolid);
	pointer += 2*numNonSolid;
	memcpy(pointer, destructables, 2*numDestruct);
	pointer += 2*numDestruct;

	memcpy(pointer, BG, 2*length);
	pointer += 2 * length;
	memcpy(pointer, MG, 2*length);
	pointer += 2 * length;
	memcpy(pointer, FG, 2*length);
	pointer += 2 * length;

	*size = s;

	return result;
}

void TileMap::deserialize(char* s){
	w = (int) s[0];
	h = (int) s[1];

	numTileTypes = (int) s[2];
	int numNonSolid = (int) s[3];
	int numDestruct = (int) s[4];

	length = w * h;

	short destructables[numDestruct];
	short nonSolidTiles[numNonSolid];

	char* pointer = s;
	pointer += 5;

	memcpy(nonSolidTiles, pointer, 2*numNonSolid);
	pointer += 2*numNonSolid;
	memcpy(destructables, pointer, 2*numDestruct);
	pointer += 2*numDestruct;

	//restore tile attributes
	tiles = new TileType[numTileTypes];

	for (int i = 0; i < numTileTypes; i++){
		tiles[i].solid = true;
		tiles[i].destructable = false;

		tiles[i].id = i;
	}

	//load solid attribute
	for ( int i = 0; i < numNonSolid; i++ ){
		tiles[nonSolidTiles[i]].solid = false;
	}

	//read destructable attribute
	for ( int i = 0; i < numDestruct; i++ ){
		tiles[destructables[i]].destructable = true;
	}

	BG = new short[length];
	MG = new short[length];
	FG = new short[length];

	//load mapdata
	memcpy(BG, pointer, 2*length);
	pointer += 2 * length;
	memcpy(MG, pointer, 2*length);
	pointer += 2 * length;
	memcpy(FG, pointer, 2*length);
	pointer += 2 * length;
}

//--------------------------------------------------------
// Private Member Funktions of TileMap
//--------------------------------------------------------

int TileMap::getTileID(int x, int y){
	int index = x*w+y;

	if (index > length) return 0;

	return MG[index];
}

int TileMap::findSpawnTiles() {
	if(spawnTiles != NULL) {
		delete spawnTiles;
	}

	spawnTiles = new TileVector();

	short* p = FG;

	for (int i = 0; i < length; ++i, ++p){
		if (*p == TILE_PLAYER_SPAWN){
			int x = i % w;
			int y = (i - x) / w;
			Tile t = getTile(x, y);
			spawnTiles->push_back(t);
		}
	}

	return spawnTiles->size();
}

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int TileMap::load_map(char* filename){
	FILE *file = fopen(filename, "rb");

	if (file == NULL) {
		cout << "Map \"" << filename << "\"doesn't exist!" << endl;
		return 1;
	}

	//Start reading file...
	w = fgetc(file); //Width
	h = fgetc(file); //Height

	length = w * h;

	//load Tiles
	numTileTypes = fgetc(file);

	tiles = new TileType[numTileTypes];

	for (int i = 0; i < numTileTypes; i++){
		tiles[i].solid = true;
		tiles[i].destructable = false;
		tiles[i].id = i;
	}

	//load solid attribute
	int numNonSolid = fgetc(file);

	short nonSolidTiles[numNonSolid];

	fread(&nonSolidTiles, 2, numNonSolid, file);

	for ( int i = 0; i < numNonSolid; ++i ){
		tiles[nonSolidTiles[i]].solid = false;
	}

	//read destructable attribute
	int numDestructable = fgetc(file);

	short destrTiles[numNonSolid];

	fread(&destrTiles, 2, numDestructable, file);

	for ( int i = 0; i < numDestructable; ++i ){
		tiles[destrTiles[i]].destructable = true;
	}

	//initialize tiles arrays
	BG = new short[length];
	MG = new short[length];
	FG = new short[length];

	//read tiles
	fread(BG, 2, length, file); //2 is sizeof(short)
	fread(MG, 2, length, file);
	fread(FG, 2, length, file);

	//finish reading file
	fclose(file);

	findSpawnTiles();

	return 0;
}


