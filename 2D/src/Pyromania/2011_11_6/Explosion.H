#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <allegro.h>
#include <string>
#include <list>

#include "Sprite.h"
#include "Bomb.h"

class World;

struct TileExplosion {
	int tx;
	int ty;

	int type; //Different typed: Horiz, Vertical, Normal...

	int curframe;
};

using namespace std;
typedef list<TileExplosion> TileExplosionList;

class Explosion : public Sprite {
	protected:
		int startTime;
		int countdown; //How long till Explosion disappears

		int oldTime; //GameTime last updatet

		int strength;

		World* world;

		int expl_moved;

		TileExplosionList Tiles;

		int tx, ty; //tile positions of epicentrum

	public:

		void   update();
		void   setWorld(World* w);
		World* getWorld();	
		void   setStrength(int s);

		#ifndef SERVER
		//Graphics functions

		virtual void Draw();
		
		#endif

		Explosion();
		Explosion(Bomb* bomb);
		virtual ~Explosion();
};	


#endif
