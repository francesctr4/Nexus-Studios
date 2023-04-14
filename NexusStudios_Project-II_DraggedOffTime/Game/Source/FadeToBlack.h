#pragma once

#include "Module.h"
#include "SDL\include\SDL_rect.h"

class FadeToBlack : public Module
{
public:
	//Constructor
	FadeToBlack(bool startEnabled);

	//Destructor
	~FadeToBlack();

	bool Awake(pugi::xml_node& config);

	// Called when the module is activated
	// Enables the blending mode for transparency
	bool Start();

	// Called at the middle of the application loop
	// Updates the fade logic
	bool Update(float dt);

	// Called at the end of the application loop
	// Performs the render call of a black rectangle with transparency
	bool PostUpdate();

	// Called from another module
	// Starts the fade process which has two steps, fade_out and fade_in
	// After the first step, the modules should be switched
	bool Fade(Module* toDisable, Module* toEnable);

private:

	// The modules that should be switched after the first step
	Module* current;
	Module* next;

	bool onTransition;
	bool fadeOutCompleted;
	float transitionAlpha;

	bool transitionRequired;
};