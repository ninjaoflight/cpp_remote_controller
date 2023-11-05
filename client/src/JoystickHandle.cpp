#include "SDL_joystick.h"
#include <SDL2/SDL.h>
#include <controller.hpp>

void Controller::JoystickHandle::reset(SDL_Joystick *joystick) {
	if (this->joystick) {
		SDL_JoystickClose(this->joystick);
	}
	this->joystick = joystick;
}

Controller::JoystickHandle::operator SDL_Joystick *() const { return joystick; }

bool Controller::JoystickHandle::operator!() const { return !joystick; }

Controller::JoystickHandle::~JoystickHandle() { reset(); }
