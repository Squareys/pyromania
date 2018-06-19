/*
 * Joypad.cpp
 *
 *  Created on: 08.08.2013
 *      Author: The Master
 */

#include "Joypad.h"

Joypad::Joypad() {
	for (int i = 0; i < KEY_KEY_CODES_COUNT; i++){
		keys[i] = KS_NONE;
	}
}

Joypad::~Joypad() {
	;
}

KeyState Joypad::state(EKEY_CODE keyCode) const{
	return keys[keyCode];
}

bool Joypad::OnEvent(const SEvent& event){
	if ( event.EventType == irr::EET_KEY_INPUT_EVENT){
		KeyState prev = state(event.KeyInput.Key);
		if (event.KeyInput.PressedDown) {
			if (prev > 0){
				keys[event.KeyInput.Key] = KS_PRESSED;
			} else {
				keys[event.KeyInput.Key] = KS_DOWN;
			}
		} else {
			if (prev < 1){
				keys[event.KeyInput.Key] = KS_NONE;
			} else {
				keys[event.KeyInput.Key] = KS_UP;
			}
		}
	}

	return false;
}
