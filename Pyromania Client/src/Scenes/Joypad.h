/*
 * Joypad.h
 *
 *  Created on: 08.08.2013
 *      Author: The Master
 */

#ifndef JOYPAD_H_
#define JOYPAD_H_

#include <irrlicht.h>

using namespace irr;

enum KeyState {
	KS_UP = -1,
	KS_NONE = 0,
	KS_DOWN = 1,
	KS_PRESSED = 2
};

class Joypad: public IEventReceiver {
private:
	KeyState keys[KEY_KEY_CODES_COUNT];
public:

	virtual bool OnEvent(const SEvent& event);
	virtual KeyState state(EKEY_CODE keyCode) const;

	Joypad();
	virtual ~Joypad();
};

#endif /* JOYPAD_H_ */
