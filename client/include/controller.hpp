#pragma once
#include <string>
#include <utility>
#include <vector>

struct _SDL_Joystick;
typedef struct _SDL_Joystick SDL_Joystick;

class Controller {

	class JoystickHandle {
		// non copyable
		JoystickHandle(const JoystickHandle &) = delete;
		JoystickHandle &operator=(const JoystickHandle &) = delete;
		// non movable
		JoystickHandle(JoystickHandle &&) = delete;
		JoystickHandle &operator=(JoystickHandle &&) = delete;

		SDL_Joystick *joystick = nullptr;

	  public:
		JoystickHandle() = default;

		void reset(SDL_Joystick *joystick = nullptr);
        operator SDL_Joystick *() const;

		bool operator!() const;
		~JoystickHandle();
	};

	JoystickHandle joystick;

	int id = -1;

  public:
	Controller();

	std::string getControllerName();
	int getControllerId();
	bool setController(int id = -1);
	void resetController();

	~Controller();
	// returns the list and ID of all the available controllers
	std::vector<std::pair<std::string, int>> getControllers();
};