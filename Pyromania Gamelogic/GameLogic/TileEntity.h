/*
 * TileEntity.h
 *
 *  Created on: 30.07.2013
 *      Author: The Master
 */

#ifndef TILEENTITY_H_
#define TILEENTITY_H_

#include "Entity.h"

class TileEntity : public Entity {
protected:
	int tileX, tileY;
public:
	TileEntity();
	virtual ~TileEntity();

	void 	update(int ticks);

	int 	getTileX();
	int 	getTileY();
};

#endif /* TILEENTITY_H_ */
