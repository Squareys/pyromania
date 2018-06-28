#include "joypad.h"

Joypad *joypad = new Joypad();

Joypad::Joypad() {
    int defaultValues[BUTTON_COUNT] = { 
        KEY_UP, 
        KEY_DOWN,
        KEY_RIGHT,
        KEY_LEFT,
	KEY_SPACE,
	KEY_RIGHT,
        KEY_UP, 
	KEY_DOWN,
	KEY_LEFT,
	KEY_ENTER,
        KEY_ESC
    };

    for (int a = 0; a < BUTTON_COUNT; a++) {
        button[a] = KS_NONE;
    }

    JoystickInfo defJoy[] = {
        // Richtungen
        JoystickInfo(0,0,1,0), 
        JoystickInfo(0,0,1,1), 
        JoystickInfo(0,0,0,0), 
        JoystickInfo(0,0,0,1), 
        // Knöpfe
        JoystickInfo(0,0), 
        JoystickInfo(0,1), 
        JoystickInfo(0,2), 
        JoystickInfo(0,3), 
        JoystickInfo(0,4), 
    };
    for (int a = 0; a < BUTTON_COUNT; a++) {
        keys[a] = defaultValues[a];
        joy[a].stick = JoystickInfo::INVALID;
        joyState[a]  = NULL;
        if (num_joysticks > defJoy[a].device) {
            if (defJoy[a].stick != JoystickInfo::INVALID) {
                if (defJoy[a].stick < ::joy[defJoy[a].device].num_sticks) {
                    if (defJoy[a].axis < ::joy[defJoy[a].device].stick[defJoy[a].stick].num_axis) {
                        switch (defJoy[a].button) {
                            case 0: 
                            case 1: 
                                joy[a].device = defJoy[a].device;
                                joy[a].stick  = defJoy[a].stick;
                                joy[a].axis   = defJoy[a].axis;
                                joy[a].button = defJoy[a].button;
                                
                                if (joy[a].button == 0) {
                                    joyState[a] = &(::joy[joy[a].device].stick[joy[a].stick].axis[joy[a].axis].d1);
                                } else {
                                    joyState[a] = &(::joy[joy[a].device].stick[joy[a].stick].axis[joy[a].axis].d2);
                                }
                            break;
                        }
                    } 
                }
            } else if (::joy[defJoy[a].device].num_buttons > defJoy[a].button) {                
                joy[a].device = defJoy[a].device;
                joy[a].button = defJoy[a].button;
                joy[a].stick  = JoystickInfo::INVALID;
                joy[a].axis   = JoystickInfo::INVALID;
                
                joyState[a] = &(::joy[joy[a].device].button[joy[a].button].b);
            }
        }
    }
}
void Joypad::poll() {
    poll_joystick();

    for (int a = 0; a < BUTTON_COUNT; a++) {
        if (key[keys[a]]) {
	    if (button[a] == KS_NONE){
            	button[a] = KS_DOWN;
	    } else {
		button[a] = KS_PRESSED;
	    }
        } else {
            if (joyState[a] != NULL) {
                button[a] = *joyState[a];
            } else {
		if (button[a] > 0) {
                	button[a] = KS_UP;
		} else {
			button[a] = KS_NONE;
		}
            }
        }
    }
}
