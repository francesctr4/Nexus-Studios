#include "FadeToBlack.h"

#include "Log.h"
#include "Window.h"
#include "App.h"
#include "Render.h"

#include "SDL/include/SDL_render.h"

#define FADEOUT_TRANSITION_SPEED	2.0f
#define FADEIN_TRANSITION_SPEED		2.0f

FadeToBlack::FadeToBlack(bool startEnabled) : Module(startEnabled)
{
	current = nullptr;
	next = nullptr;

	onTransition = false;
	fadeOutCompleted = false;
	transitionAlpha = 0;

	transitionRequired = false;
}
FadeToBlack::~FadeToBlack()
{

}

bool FadeToBlack::Awake(pugi::xml_node& config)
{

	return true;
}


bool FadeToBlack::Start()
{
	LOG("Preparing Fade Screen");

	return true;
}

bool FadeToBlack::Update(float dt)
{
	OPTICK_EVENT();

	dt = dt / 1000;

	LOG("Updating Current Scene");
	bool ret = true;

	if (onTransition)
	{
		if (!fadeOutCompleted)
		{
			transitionAlpha += (FADEOUT_TRANSITION_SPEED * dt);

			// NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
			// For that reason we compare against 1.01f, to avoid last frame loading stop
			if (transitionAlpha > 1.01f)
			{
				transitionAlpha = 1.0f;

				current->Disable();	// Unload current screen
				next->Enable();	// Load next screen

				delete current;	// Free current pointer
				current = next;	// Assign next pointer
				next = nullptr;

				// Activate fade out effect to next loaded screen
				fadeOutCompleted = true;
			}
		}
		else  // Transition fade out logic
		{
			transitionAlpha -= (FADEIN_TRANSITION_SPEED * dt);

			if (transitionAlpha < -0.01f)
			{
				transitionAlpha = 0.0f;
				fadeOutCompleted = false;
				onTransition = false;
			}
		}
	}

	// Draw full screen rectangle in front of everything
	if (onTransition)
	{
		app->render->DrawRectangle({ 0, 0, 1280, 720 }, 0, 0, 0, (unsigned char)(255.0f * transitionAlpha));
	}

	if (transitionRequired)
	{
		onTransition = true;
		fadeOutCompleted = false;
		transitionAlpha = 0.0f;

		transitionRequired = false;

	}

	return ret;
}

bool FadeToBlack::PostUpdate()
{
	OPTICK_EVENT();


	return true;
}

bool FadeToBlack::Fade(Module* moduleToDisable, Module* moduleToEnable)
{
	OPTICK_EVENT();
	bool ret = true;

	current = moduleToDisable;
	next = moduleToEnable;

	transitionRequired = true;

	return ret;
}