#ifndef VIRT_JOYPAD_HEADER
#define VIRT_JOYPAD_HEADER

#include <allegro.h>

class JoystickInfo {
public:    
    enum { 
        INVALID = -1 
    };
    int device, stick, axis, button;
    
    JoystickInfo() {        
        set(INVALID, INVALID,INVALID,INVALID);
    }
    JoystickInfo(int device, int button) {        
        set(device, button);
    }
    JoystickInfo(int device, int stick, int axis, int button) {        
        set(device, stick, axis, button);
    }
    
    void set(int device, int button) {        
        this->device = device;
        this->stick  = INVALID;
        this->axis   = INVALID;
        this->button = button;
    }
    void set(int device, int stick, int axis, int button) {        
        this->device = device;
        this->stick  = stick;
        this->axis   = axis;
        this->button = button;
    }
};

class Joypad {

public:
    // Das Steuerkreuz
    enum { 
        UP    	 = 0, 
        DOWN  	 = 1, 
        RIGHT 	 = 2, 
        LEFT  	 = 3,
	DROP	 = 4,
	MOVER    = 5,
	MOVEUP	 = 6, 
	MOVEDOWN = 7,
	MOVEL    = 8,
        SELECT	 = 9,
        QUIT  	 = 10
    };

    //Key State enum
    enum {
	KS_NONE    = 0, //Not Pressed
	KS_DOWN    = 2, //recently Pressed
	KS_PRESSED = 1, //Pressed
	KS_UP	   = -1 //Just "Unpressed"
    };
     
    // Die anzahl der knöpfe (inklusive steuerkreuz)
    enum {
        FIRST_ACTION_BUTTON = SELECT,
        ACTION_BUTTON_COUNT = 1,
        BUTTON_COUNT = 11
    };
    // die eigentlichen werte
    int button[BUTTON_COUNT];
    int keys[BUTTON_COUNT]; //The Key Values (Ex: KEY_ESC)

    // Der Constructor
    Joypad();
    // Die poll Methode füllt das button array mit
    // gültigen Werten.
    void poll();

private:
    
    JoystickInfo joy[BUTTON_COUNT];
    int* joyState[BUTTON_COUNT];

};
extern Joypad *joypad;
#endif
