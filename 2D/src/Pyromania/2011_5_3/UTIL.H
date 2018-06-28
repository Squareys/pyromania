#ifndef UTIL_HEADER
#define UTIL_HEADER

#include <allegro.h>
#include <string>
#include <iostream>

extern volatile int timerCounter;

extern BITMAP   *doubleBuffer;

void fatalError(char *str);
int  setGfxMode(int mode, int width, int height);
void show();
void init(int w, int h, int fps, bool fullscreen = true);
void done();
int  rnd(int max);
void syncTimer(volatile int *timer);
void playSound(SAMPLE *sample, int vol);

void secure_destroy_bitmap(BITMAP* BMP);

#endif
