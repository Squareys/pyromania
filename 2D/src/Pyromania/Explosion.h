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

	int type; //Different typed: Horiz, Vertical, Middle...

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

		TileExplosionList* Tiles;

		int tx, ty; //tile positions of epicentrum

		bool checkTileCollision(TileExplosion te, Sprite* sprite);

		int expanding;

		enum {
			UP 	= 1,
			DOWN 	= 2,
			RIGHT 	= 4,
			LEFT 	= 8
		};

	public:

		void   update();
		void   setWorld(World* w);
		World* getWorld();	
		void   setStrength(int s);

		bool collision(Sprite* sprite);
		bool checkCollision(Sprite* sprite);

		#ifndef SERVER
		//Graphics functions

		virtual void Draw();
		
		#endif

		Explosion();
		Explosion(Bomb* bomb);
		virtual ~Explosion();
};	


#endif
