#ifndef FRAMECOUNTER_HEADER
#define FRAMECOUNTER_HEADER

#include <allegro.h>
#include "Util.h"

// Framecounter: responsible for managing the fps.
class FrameCounter {
   public:
	int* fps;

	void setFPSvar	(int * in_fps); //sets the FPS Pointer
	void didFrame 	();
	void update	();

	FrameCounter();
	
   private:
	int frames_done;
	int old_time;
 
	int frames_array[10];//an array to store the number of frames we did during the last 10 tenths of a second
	int frame_index;//used to store the index of the last updated value in the array
	
};

#endif
