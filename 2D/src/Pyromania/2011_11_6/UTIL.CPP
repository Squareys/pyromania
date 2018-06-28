#include "util.h"

#include <cstring>

// Double Buffer
BITMAP   *screenAlias  = NULL;
BITMAP   *doubleBuffer = NULL;

// Die Timer Variablen und FUnktionen
// -------------------------------------------------------
volatile int ticks = 0;
volatile int gameTime = 0;

static void tick() {
    ticks++;    
}
END_OF_STATIC_FUNCTION(tick);

static void gameTimer() {
    gameTime++;    
}
END_OF_STATIC_FUNCTION(gameTimer);
// -------------------------------------------------------
void fatalError(char *str) {
    allegro_message(str);
    exit(0);
}
// -------------------------------------------------------
int setGfxMode(int mode, int width, int height) {
    static int colorDepths[] = { 32, 16, 24, 15, 32};
    int a;  
    
    for (a=0; a < 4; a++) {
        set_color_depth(colorDepths[a]);
        if (set_gfx_mode(mode, width, height, 0, 0) >= 0) {
            return TRUE;
        }
    }
    return FALSE;
}
// -------------------------------------------------------
void playSound(SAMPLE *sample, int vol) {
    if (!sample) return;
    play_sample(sample, vol, 128, rnd(400) + 900, 0);
}
// -------------------------------------------------------
void secure_destroy_bitmap(BITMAP* BMP){
	if (BMP != NULL){
		destroy_bitmap(BMP);
	}
}
// -------------------------------------------------------
void show() {
    blit(doubleBuffer, screen, 0, 0, 0, 0, doubleBuffer->w, doubleBuffer->h);
}
// -------------------------------------------------------
int rnd( int n ){
    return (int)( n * ( (double)rand() / (double)(RAND_MAX + 1.0 ) ) );
}
// -------------------------------------------------------
void init(int w, int h, int fps, bool fullscreen) {
    srand(time(NULL));
    
    // Allegro und Grafik, Timer, Sound und Eingabemedien
    // initilaisieren
    allegro_init();

    if (!fullscreen || !setGfxMode(GFX_AUTODETECT_FULLSCREEN, w, h)) {
        if (!setGfxMode(GFX_AUTODETECT_WINDOWED, w, h)) {
            fatalError("Unable to set a graphics mode");
        }
	set_display_switch_mode(SWITCH_BACKGROUND);
    } else {
	set_display_switch_mode(SWITCH_BACKAMNESIA);
    }
    install_timer();
    
    /* Den DoubleBuffer erstellen */
    screenAlias  = create_video_bitmap(SCREEN_W, SCREEN_H);
    doubleBuffer = create_video_bitmap(SCREEN_W, SCREEN_H);

    if (!doubleBuffer) {
        if (screenAlias != NULL) {
            destroy_bitmap(screenAlias);            
        }
        doubleBuffer = create_system_bitmap(SCREEN_W, SCREEN_H);
        if (!doubleBuffer) {
            fatalError("Unable to create double buffer");
        }
    }
    
    vsync();
    /* Timer Funktionen und Variablen locken */
    LOCK_FUNCTION(tick);
    LOCK_VARIABLE(ticks);
	
    LOCK_FUNCTION(gameTimer);
    LOCK_VARIABLE(gameTime);
	
    /* Die logische Framerate setzen */    
    install_int_ex(tick, BPS_TO_TIMER(fps));
    install_int(gameTimer, 10); 
    
    DATAFILE* Logo_dat = load_datafile("Images\\Images00.dat");
    BITMAP* Logo       = (BITMAP*) Logo_dat[0].dat;
    BITMAP* Logo_glanz = (BITMAP*) Logo_dat[1].dat;
    BITMAP* allegro_logo = (BITMAP*) Logo_dat[2].dat;

    int x = 0;
    bool needsRefresh = false;

    while (x < Logo->w) {
        if (ticks) {
               do {
		x+= 6;
                --ticks;
               } while (ticks);
            needsRefresh = true;
        }
        if (needsRefresh) {
	    blit(Logo,doubleBuffer, 0,0, 0,0,Logo->w, Logo->h);
	    blit(Logo_glanz, doubleBuffer, x, 0, x, 0, 30, Logo->h);
            show();
            needsRefresh = false;
        }
    }

    install_keyboard();
    install_joystick(JOY_TYPE_AUTODETECT);
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    
    // ASCII Zeichen benutzen
    set_uformat(U_ASCII);
    
    // Allegro Logo anzeigen
    if (allegro_logo) {
        blit(allegro_logo, screen, 0, 0, 0, 0, allegro_logo->w, allegro_logo->h);
    }

    unload_datafile(Logo_dat);
    
}
// -------------------------------------------------------
// Gibt die in init() angelegten Resourcen
// wieder frei
void done() {
    destroy_bitmap(doubleBuffer);
    secure_destroy_bitmap(screenAlias);
}
// -------------------------------------------------------
void syncTimer(volatile int * timer) {
    int value = *timer;
    while (*timer == value);
}
