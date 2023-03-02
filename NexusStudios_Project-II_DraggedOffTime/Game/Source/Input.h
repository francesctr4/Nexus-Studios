#ifndef __INPUT_H__
#define __INPUT_H__

#include "Module.h"
#include "SDL/include/SDL_gamecontroller.h"
#include <math.h>

//#define NUM_KEYS 352
#define NUM_MOUSE_BUTTONS 5
//#define LAST_KEYS_PRESSED_BUFFER 50

#define SDL_MAX_SINT16 32767
#define MAX_CONTROLLERS 1

struct SDL_Rect;

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct GameController {

	float j1_x, j1_y, j2_x, j2_y, LT, RT;
	KeyState buttons[SDL_CONTROLLER_BUTTON_MAX];

};

class Input : public Module
{

public:

	Input(bool startEnabled);

	// Destructor
	virtual ~Input();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called before quitting
	bool CleanUp();

	// Check key states (includes mouse and joy buttons)
	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	KeyState GetMouseButtonDown(int id) const
	{
		return mouseButtons[id - 1];
	}

	// Check if a certain window event happened
	bool GetWindowEvent(EventWindow ev);

	// Get mouse / axis position
	void GetMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);

	SDL_GameController* sdl_controllers[MAX_CONTROLLERS];
	GameController controllers[MAX_CONTROLLERS];
	int num_controllers;

	float reduce_val(bool controllerON, float v1, float min, float clamp_to) {

		if (controllerON) {

			float sign = v1 / fabs(v1);

			float reduced = v1 - ((fabs(v1) > min) ? sign * min : v1);

			float to_1 = reduced / (float)(SDL_MAX_SINT16);
			
			float reclamped = to_1 * clamp_to;

			return reclamped;

		}
		else {

			return 0;
		}
	}

private:

	bool windowEvents[WE_COUNT];
	KeyState*	keyboard;
	KeyState mouseButtons[NUM_MOUSE_BUTTONS];
	int	mouseMotionX;
	int mouseMotionY;
	int mouseX;
	int mouseY;

};

#endif // __INPUT_H__