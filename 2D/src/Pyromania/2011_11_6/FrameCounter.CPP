#include "FrameCounter.h"

FrameCounter::FrameCounter(){
	frames_done 	= 0;
	old_time 	= 0;
	frame_index 	= 0;

	//After trying memset and caused major problems
	//with allegro, I returned to the simple way :)
	//Initialize the frames_array with 0
	for (int i = 0; i < 10; i++){
		frames_array[i] = 0;
	}
}

void FrameCounter::setFPSvar(int *in_fps){
	fps = in_fps;
}

void FrameCounter::didFrame(){
	frames_done++;
}

void FrameCounter::update(){
	if(gameTime >= old_time + 10) { //Update Framerate every 0.1 seconds		
		*fps        -= frames_array[frame_index]; //decrement the fps by the frames done a second ago
		frames_array[frame_index] = frames_done; //store the number of frames done this 0.1 second
		*fps        += frames_done;               //increment the fps by the newly done frames
 	
		frame_index = (frame_index + 1) % 10;//increment the frame index and snap it to 10

		frames_done = 0;
		old_time   += 10;
	}
}
