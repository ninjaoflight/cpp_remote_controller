#include <SDL2/SDL.h>
#include <controller.hpp>

Controller::Controller() { SDL_Init(SDL_INIT_JOYSTICK); }

bool Controller::setController(int id) {
	// check if the joystick is open
	resetController();
	if (id == -1) {
		// if the id is -1, then we want to use the first controller
		id = 0;
	}

	int num_joysticks = SDL_NumJoysticks();
	if (num_joysticks > 0) {
		// if there are joysticks connected, then we want to open the first one
		// and get its name
		joystick.reset(SDL_JoystickOpen(id));
		// check if the joystick is open
		if (!!joystick) {
			return true;
		}
	}
	return false;
}

std::string Controller::getControllerName() {
    if (!!joystick) {
        return SDL_JoystickName(joystick);
    }
    return "";
}

int Controller::getControllerId() { return id; }

void Controller::resetController() { joystick.reset(); }

std::vector<std::pair<std::string, int>> Controller::getControllers() {
	std::vector<std::pair<std::string, int>> controllers;

	int num_joysticks = SDL_NumJoysticks();

	// iterate through all the joysticks and add them to the list

	for (int i = 0; i < num_joysticks; i++) {
		controllers.push_back(std::make_pair(SDL_JoystickNameForIndex(i), i));
	}

	return controllers;
}

Controller::~Controller() {
	// check if the joystick is open
	resetController();
	SDL_Quit();
}
