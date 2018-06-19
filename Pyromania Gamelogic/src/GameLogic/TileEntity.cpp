/*
 * TileEntity.cpp
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#include "TileEntity.h"

//----------------------------------------
// Constructors of TileEntity
//----------------------------------------

TileEntity::TileEntity() : tileX(0), tileY(0) {

}

TileEntity::~TileEntity() {
}

//----------------------------------------
// Public Member Functions of TileEntity
//----------------------------------------

void TileEntity::update(int ticks){

}

int TileEntity::getTileX(){
	return tileX;
}

int TileEntity::getTileY(){
	return tileY;
}
